#include "sttp.h"

//umieszcza dane w kolejce ni¿szej warstwy
void STTP::to_net(RawData data)
{
	//lock + jakaœ obrona przed pe³n¹ kolejk¹
	netQueue->push(data);
	//unlock + ew. jakiœ sygna³ o pustej kolejce
};

//umieszcza dane w kolejce wy¿szej warstwy
void STTP::to_controller(RawData data)
{
	//lock + jakaœ obrona przed pe³n¹ kolejk¹
	toControllerQueue->push(data);
	//unlock + ew. jakiœ sygna³ o pustej kolejce
};

//pobiera dane z kolejki od ni¿szej warstwy
RawData STTP::from_net()
{
	RawData data;

	//lock + jakaœ obrona przed pust¹ kolejk¹
	data = netQueue->pull();
	//netQueue->pop();
	//unlock + ew. jakiœ sygna³ o pe³nej kolejce

	return data;
};

//pobiera dane z kolejki od wy¿szej warstwy
PrioritableRawData STTP::from_controller()
{
	PrioritableRawData pData;

	//lock + jakaœ obrona przed pust¹ kolejk¹
	pData = fromControllerQueue->pull();
	//fromControllerQueue->pop();
	//unlock + ew. jakiœ sygna³ o pe³nej kolejce

	return pData;
};

//opakowuje dane w ramkê STTP; !!! UWAGA!!! Zwróci puste RawData,
//jeœli dataField ma wiêcej bajtów ni¿ STTP_DATA_FIELD_LEN
RawData STTP::prepare_sttp_frame(RawData dataField)
{
	unsigned char dataSize = dataField.get_data_size();
	int fillLen = STTP_DATA_FIELD_LEN - dataSize;

	if (fillLen < 0)	//jeœli rozmiar danych dataField
	{					//jest wiêkszy od maksymalnego,
		RawData empty;	//zwracamy pusty obiekt RawData
		return empty;
	}
	else if (fillLen > 0)	//jeœli rozmiar danych dataField
	{						//jest wiêkszy od maksymalnego,
		char* zeros = new char[fillLen];	//resztê dope³niamy zerami
		memset(zeros, 0, fillLen);
		dataField.add_data(zeros,fillLen);
	}

	//kontruujemy paczkê nag³ówek+dane do podpisu...
	RawData nrField((char*)(&frameCtrlNr),1);
	RawData lenField((char*)(&dataSize),1);
	RawData signedContent = nrField + lenField + dataField;

	//...i podpisujemy
	char* signature = new char[STTP_SIGN_FIELD_LEN];
	char* signedContentDataPtr = signedContent.get_data_instance();
	//signature = sign(signedContentDataPtr, privateServerKey.c_str());
	delete signedContentDataPtr;

	RawData signField(signature, STTP_SIGN_FIELD_LEN);
	delete signature;

	RawData sttpFrame = signedContent + signField;
	return sttpFrame;
};

//tworzy ramkê protoko³u komunikacyjnego powoduj¹c¹ roz³¹czenie,
//z informacj¹ o zagro¿eniu bezpieczeñstwa transmisji
RawData STTP::make_frame_disconnect(char whyDisconnecting)
{
	char id = 0x1E;
	RawData disconnectFrame(&id,1);
	disconnectFrame.add_data(&whyDisconnecting, 1);

	return disconnectFrame;
};

//wys³anie pojedyñczej ramki protoko³u komunikacyjnego; zwraca iloœæ
//bajtów wys³anych wewn¹trz pola/pól danych ramki/ramek STTP
int STTP::single_send()
{
	PrioritableRawData pData = from_controller();	//pobranie kolejnej ramki z kolejki, do której wrzuca kontroler
	RawData data = pData.data;
	bool urgent = pData.urgent;

	buffer.add_data(data);	//wrzucamy pobran¹ ramkê protoko³u komunikacyjnego do wewnêtrzego bufora STTP
							//do wsysy³ki pójdzie ta ramka plus ewentualnie ostatni fragment poprzedniej,
							//jeœli nie by³a ona pilna <=> kawa³ek móg³ zostaæ w buforze

	RawData dataField;
	int minLen, actualLen, sumLen;

	sumLen = 0;

	if (urgent)	//jeœli pobrana ramka jest pilna, wyœlemy j¹ w ca³oœci, nawet jeœli
		minLen = 1;	//w ostatniej iteracji zostanie do wys³ania pojedyñczy bajt
	else		//jeœli nie pilne, to bierzemy tylko ca³ymi d³ugoœciami
		minLen = STTP_DATA_FIELD_LEN;	//pola danych ramki STTP, najwy¿ej coœ zostanie w buforze

	int buffer_data_size = buffer.get_data_size();


	while(buffer_data_size >= minLen)	//dopóki jest jeszcze coœ do wys³ania
	{
		int buffer_data_size = buffer.get_data_size();	//aktualna iloœæ danych w buforze

		if (urgent)	//jeœli pilne, wyœlemy z bufora wszystko,
		{			// nawet jeœli w ostatniej iteracji zostanie pojedyñczy bajt
			minLen = 1;
			if (buffer_data_size > STTP_DATA_FIELD_LEN)	//...ale za jednym razem
				actualLen = STTP_DATA_FIELD_LEN;		//co najwy¿ej tyle,
			else										//ile siê mieœci
				actualLen = buffer_data_size;			//w polu danych ramki STTP
		}
		else		//jeœli nie pilne, to bierzemy tylko ca³ymi d³ugoœciami
		{			//pola danych ramki STTP, najwy¿ej coœ zostanie w buforze
			minLen = STTP_DATA_FIELD_LEN;
			actualLen = STTP_DATA_FIELD_LEN;
		}

		//pobranie z bufora odpowiedniej iloœci danych
		dataField = buffer.get_packed_data_piece(0, actualLen);
		buffer.del_data_piece(0, actualLen);

		RawData sttpFrame = prepare_sttp_frame(dataField);	//opakowanie danych w ramkê STTP
		char* sttpFrameDataPtr = sttpFrame.get_data_instance();
		//char* sttpFrameDataPtr = encrypt(sttpFrameDataPtr, session_key.c_str);
		sttpFrame = RawData(sttpFrameDataPtr, STTP_DATA_FIELD_LEN + STTP_SIGN_FIELD_LEN + 2);

		delete sttpFrameDataPtr;

		sumLen += actualLen;
		frameCtrlNr = (frameCtrlNr + 1) % 256;
		to_net(sttpFrame);	//umieszczenie gotowej ramki w kolejce, z której pobiera warstwa obs³uguj¹ca sockety
	}

	return sumLen;	//zwracamy iloœæ bajtów przekazanych przez kontroler, które w tym wywo³aniu wys³aliœmy
};

//przekazanie kontrolerowi danych z jednej ramki STTP;
//zwraca rozmiar przekazanych danych (w bajtach)
int STTP::single_receive()
{
	RawData data;

	data = from_net();	//pobranie danych z kolejki, do której wrzuca warstwa obs³uguj¹ca sockety

	buffer.add_data(data);	//dorzucenie powy¿szych danych do naszego bufora
	//tutaj ³¹czy siê ewentualna wczeœniejsza czêœæ ramki STTP z drug¹ czêœci¹,
	//pobran¹ dopiero teraz

	int sumLen = 0;

	while(buffer.get_data_size() >= sttpFrameSize)
	{

		//------------------------------------------------------------------------------
		//-----------------------  odszyfrowanie ramki STTP  ---------------------------

		RawData sttpFrame = buffer.get_packed_data_piece(0, sttpFrameSize);
		buffer.del_data_piece(0, sttpFrameSize);
		char* sttpFrameDataPtr = sttpFrame.get_data_instance();
		//sttpFrameDataPtr = decrypt(sttpFrameDataPtr, session_key.c_str());
        sttpFrame = RawData(sttpFrameDataPtr, STTP_DATA_FIELD_LEN + STTP_SIGN_FIELD_LEN + 2);

		delete sttpFrameDataPtr;

		//wydobycie z ramki poszczególnych pól
		char* frameNumberPtr = sttpFrame.get_data_piece_instance(0,1);
		char* dataLenPtr = sttpFrame.get_data_piece_instance(1,2);
		RawData dataField = sttpFrame.get_packed_data_piece(2,2+(*dataLenPtr));
		char* signPtr = sttpFrame.get_data_piece_instance(sttpFrameSize-signFieldLen,sttpFrameSize);


		//------------------------------------------------------------------------------
		//------------  odtworzenie podpisu nag³ówka+danych do porównania  -------------

		RawData signedContent(frameNumberPtr, 1);
		signedContent.add_data(dataLenPtr, 1);
		signedContent.add_data(dataField);

		char* signaturePtr = new char[STTP_SIGN_FIELD_LEN];
		char* signedContentDataPtr = signedContent.get_data_instance();
		//signaturePtr = sign(signedContentDataPtr,privateServerKey.c_str());
		delete signedContentDataPtr;

		RawData calculatedSignature(signaturePtr,STTP_SIGN_FIELD_LEN);
		delete signaturePtr;

		RawData receivedSignature(signPtr,STTP_SIGN_FIELD_LEN);

		//------------------------------------------------------------------------------
		//---------------------  sprawdzenie poprawnoœci ramki  ------------------------
		//-----------  i obs³uga sytuacji, gdy ramka oka¿e siê niepoprawna  ------------

		if(calculatedSignature != receivedSignature)
		{
			RawData frameDisconnect = make_frame_disconnect(TCP_ATTACK_WRONG_SIGNATURE);
			to_controller(frameDisconnect);
			return -1;
		}

		if((*frameNumberPtr) == (frameCtrlNr + 1) % 256)
			frameCtrlNr = (frameCtrlNr + 1) % 256;
		else if((*frameNumberPtr) > (frameCtrlNr + 1) % 256)
		{
			RawData frameDisconnect = make_frame_disconnect(TCP_ATTACK_MISSING_FRAMES);
			to_controller(frameDisconnect);
			return -2;
		}
		else if((*frameNumberPtr) < (frameCtrlNr + 1) % 256)
		{
			RawData frameDisconnect = make_frame_disconnect(TCP_ATTACK_FRAME_RETRANSMISSION);
			to_controller(frameDisconnect);
			return -3;
		}

		//----------------------------------------------------------------------------------

		sumLen += (*dataLenPtr);	//obliczamy sumaryczn¹ d³ugoœæ przekazanych kontrolerowi danych
		to_controller(dataField);	//wsadzenie gotowych danych do kolejki, z której pobiera warstwa kontrolera
	}

	return sumLen;
};

//konstruktor - z wyborem kierunku transmisji danych (dir = DIR_TO_NET lub DIR_FROM_NET)
STTP::STTP(std::string sesKey, int dir, SharedQueue<RawData>* nq, void* cq) :
	direction(dir), signFieldLen(STTP_SIGN_FIELD_LEN),
	sttpFrameSize(STTP_DATA_FIELD_LEN+STTP_SIGN_FIELD_LEN+2)
{
	if(dir == DIR_FROM_NET)
	{
		frameCtrlNr = 0;
		toControllerQueue = (SharedQueue<RawData>*)cq;
		fromControllerQueue = NULL;
	}
	else if(dir == DIR_TO_NET)
	{
		frameCtrlNr = 1;
		fromControllerQueue = (SharedQueue<PrioritableRawData>*)cq;
		toControllerQueue = NULL;
	}

	buffer = RawData();
	sessionKey = sesKey;
};

//wywo³uje single_send lub single_receive - odpowiednio do determinowanego
//przez wybór odpowiedniego konstruktora kierunku przep³ywu danych;
//zwraca przes³an¹ iloœæ bajtów protoko³u komunikacyjnego
int STTP::single_transmit()
{
	if(direction == DIR_TO_NET)
		 return single_send();
	else if(direction == DIR_FROM_NET)
		return single_receive();
    else
        return 0;
};
