#include "sttp.h"

//umieszcza dane w kolejce ni�szej warstwy
void STTP::to_net(RawData data)
{
	//lock + jaka� obrona przed pe�n� kolejk�
	netQueue->push(data);
	//unlock + ew. jaki� sygna� o pustej kolejce
};

//umieszcza dane w kolejce wy�szej warstwy
void STTP::to_controller(RawData data)
{
	//lock + jaka� obrona przed pe�n� kolejk�
	toControllerQueue->push(data);
	//unlock + ew. jaki� sygna� o pustej kolejce
};

//pobiera dane z kolejki od ni�szej warstwy
RawData STTP::from_net()
{
	RawData data;

	//lock + jaka� obrona przed pust� kolejk�
	data = netQueue->pull();
	//netQueue->pop();
	//unlock + ew. jaki� sygna� o pe�nej kolejce

	return data;
};

//pobiera dane z kolejki od wy�szej warstwy
PrioritableRawData STTP::from_controller()
{
	PrioritableRawData pData;

	//lock + jaka� obrona przed pust� kolejk�
	pData = fromControllerQueue->pull();
	//fromControllerQueue->pop();
	//unlock + ew. jaki� sygna� o pe�nej kolejce

	return pData;
};

//opakowuje dane w ramk� STTP; !!! UWAGA!!! Zwr�ci puste RawData,
//je�li dataField ma wi�cej bajt�w ni� STTP_DATA_FIELD_LEN
RawData STTP::prepare_sttp_frame(RawData dataField)
{
	unsigned char dataSize = dataField.get_data_size();
	int fillLen = STTP_DATA_FIELD_LEN - dataSize;

	if (fillLen < 0)	//je�li rozmiar danych dataField
	{					//jest wi�kszy od maksymalnego,
		RawData empty;	//zwracamy pusty obiekt RawData
		return empty;
	}
	else if (fillLen > 0)	//je�li rozmiar danych dataField
	{						//jest wi�kszy od maksymalnego,
		char* zeros = new char[fillLen];	//reszt� dope�niamy zerami
		memset(zeros, 0, fillLen);
		dataField.add_data(zeros,fillLen);
	}

	//kontruujemy paczk� nag��wek+dane do podpisu...
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

//tworzy ramk� protoko�u komunikacyjnego powoduj�c� roz��czenie,
//z informacj� o zagro�eniu bezpiecze�stwa transmisji
RawData STTP::make_frame_disconnect(char whyDisconnecting)
{
	char id = 0x1E;
	RawData disconnectFrame(&id,1);
	disconnectFrame.add_data(&whyDisconnecting, 1);

	return disconnectFrame;
};

//wys�anie pojedy�czej ramki protoko�u komunikacyjnego; zwraca ilo��
//bajt�w wys�anych wewn�trz pola/p�l danych ramki/ramek STTP
int STTP::single_send()
{
	PrioritableRawData pData = from_controller();	//pobranie kolejnej ramki z kolejki, do kt�rej wrzuca kontroler
	RawData data = pData.data;
	bool urgent = pData.urgent;

	buffer.add_data(data);	//wrzucamy pobran� ramk� protoko�u komunikacyjnego do wewn�trzego bufora STTP
							//do wsysy�ki p�jdzie ta ramka plus ewentualnie ostatni fragment poprzedniej,
							//je�li nie by�a ona pilna <=> kawa�ek m�g� zosta� w buforze

	RawData dataField;
	int minLen, actualLen, sumLen;

	sumLen = 0;

	if (urgent)	//je�li pobrana ramka jest pilna, wy�lemy j� w ca�o�ci, nawet je�li
		minLen = 1;	//w ostatniej iteracji zostanie do wys�ania pojedy�czy bajt
	else		//je�li nie pilne, to bierzemy tylko ca�ymi d�ugo�ciami
		minLen = STTP_DATA_FIELD_LEN;	//pola danych ramki STTP, najwy�ej co� zostanie w buforze

	int buffer_data_size = buffer.get_data_size();


	while(buffer_data_size >= minLen)	//dop�ki jest jeszcze co� do wys�ania
	{
		int buffer_data_size = buffer.get_data_size();	//aktualna ilo�� danych w buforze

		if (urgent)	//je�li pilne, wy�lemy z bufora wszystko,
		{			// nawet je�li w ostatniej iteracji zostanie pojedy�czy bajt
			minLen = 1;
			if (buffer_data_size > STTP_DATA_FIELD_LEN)	//...ale za jednym razem
				actualLen = STTP_DATA_FIELD_LEN;		//co najwy�ej tyle,
			else										//ile si� mie�ci
				actualLen = buffer_data_size;			//w polu danych ramki STTP
		}
		else		//je�li nie pilne, to bierzemy tylko ca�ymi d�ugo�ciami
		{			//pola danych ramki STTP, najwy�ej co� zostanie w buforze
			minLen = STTP_DATA_FIELD_LEN;
			actualLen = STTP_DATA_FIELD_LEN;
		}

		//pobranie z bufora odpowiedniej ilo�ci danych
		dataField = buffer.get_packed_data_piece(0, actualLen);
		buffer.del_data_piece(0, actualLen);

		RawData sttpFrame = prepare_sttp_frame(dataField);	//opakowanie danych w ramk� STTP
		char* sttpFrameDataPtr = sttpFrame.get_data_instance();
		//char* sttpFrameDataPtr = encrypt(sttpFrameDataPtr, session_key.c_str);
		sttpFrame = RawData(sttpFrameDataPtr, STTP_DATA_FIELD_LEN + STTP_SIGN_FIELD_LEN + 2);

		delete sttpFrameDataPtr;

		sumLen += actualLen;
		frameCtrlNr = (frameCtrlNr + 1) % 256;
		to_net(sttpFrame);	//umieszczenie gotowej ramki w kolejce, z kt�rej pobiera warstwa obs�uguj�ca sockety
	}

	return sumLen;	//zwracamy ilo�� bajt�w przekazanych przez kontroler, kt�re w tym wywo�aniu wys�ali�my
};

//przekazanie kontrolerowi danych z jednej ramki STTP;
//zwraca rozmiar przekazanych danych (w bajtach)
int STTP::single_receive()
{
	RawData data;

	data = from_net();	//pobranie danych z kolejki, do kt�rej wrzuca warstwa obs�uguj�ca sockety

	buffer.add_data(data);	//dorzucenie powy�szych danych do naszego bufora
	//tutaj ��czy si� ewentualna wcze�niejsza cz�� ramki STTP z drug� cz�ci�,
	//pobran� dopiero teraz

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

		//wydobycie z ramki poszczeg�lnych p�l
		char* frameNumberPtr = sttpFrame.get_data_piece_instance(0,1);
		char* dataLenPtr = sttpFrame.get_data_piece_instance(1,2);
		RawData dataField = sttpFrame.get_packed_data_piece(2,2+(*dataLenPtr));
		char* signPtr = sttpFrame.get_data_piece_instance(sttpFrameSize-signFieldLen,sttpFrameSize);


		//------------------------------------------------------------------------------
		//------------  odtworzenie podpisu nag��wka+danych do por�wnania  -------------

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
		//---------------------  sprawdzenie poprawno�ci ramki  ------------------------
		//-----------  i obs�uga sytuacji, gdy ramka oka�e si� niepoprawna  ------------

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

		sumLen += (*dataLenPtr);	//obliczamy sumaryczn� d�ugo�� przekazanych kontrolerowi danych
		to_controller(dataField);	//wsadzenie gotowych danych do kolejki, z kt�rej pobiera warstwa kontrolera
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

//wywo�uje single_send lub single_receive - odpowiednio do determinowanego
//przez wyb�r odpowiedniego konstruktora kierunku przep�ywu danych;
//zwraca przes�an� ilo�� bajt�w protoko�u komunikacyjnego
int STTP::single_transmit()
{
	if(direction == DIR_TO_NET)
		 return single_send();
	else if(direction == DIR_FROM_NET)
		return single_receive();
    else
        return 0;
};
