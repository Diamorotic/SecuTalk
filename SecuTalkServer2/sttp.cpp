#include "sttp.h"

void STTP::to_net(RawData data)
{
	//lock + jakaœ obrona przed pe³n¹ kolejk¹
	net_queue->push(data);
	//unlock + ew. jakiœ sygna³ o pustej kolejce
};

void STTP::to_controller(RawData data)
{
	//lock + jakaœ obrona przed pe³n¹ kolejk¹
	controller_queue->push(data);
	//unlock + ew. jakiœ sygna³ o pustej kolejce
};

RawData STTP::from_net()
{
	RawData data;
	
	//lock + jakaœ obrona przed pust¹ kolejk¹
	data = netQueue->pop();
	//unlock + ew. jakiœ sygna³ o pe³nej kolejce
	
	return data;
};

PrioritableRawData STTP::from_controller()
{
	PrioritableRawData data;
	
	//lock + jakaœ obrona przed pust¹ kolejk¹
	pData = controllerQueue->pop();
	//unlock + ew. jakiœ sygna³ o pe³nej kolejce
	
	return pData;
};

RawData STTP::prepare_sttp_frame(RawData dataField)
{
	unsigned char data_size = dataField.get_data_size();
	int fillLen = STTP_DATA_FIELD_LEN - data_size;
	
	if (fillLen < 0)
	{
		RawData empty;
		return empty;
	}
	else if (fillLen > 0)
	{
		char* zeros = new char[fillLen];
		memset(zeros, 0, fillLen);
		dataField.add_data(zeros,fillLen);		
	}
	
	
	RawData nrField((char*)(&frameCtrlNr),1);
	RawData lenField((char*)(&data_size),1);
	RawData signedContent = nrField + lenField + dataField;
	
		
	char* signature = new char[4];
	//signature = sign(signedContent.get_data_instance())
	
	RawData signField(signature, 4);
	
	RawData sttpFrame = signedContent + signField;
	
	return sttpFrame;
}

int STTP::single_send()
{
	PrioritableRawData pData = from_controller();
	data = pData.data;
	bool urgent = pData.urgent;
	
	buffer.add_data(data);

	RawData dataField;
	int minLen, actualLen;
	
	if (urgent)	//jeœli pilne, wyœlemy z bufora wszystko,
		minLen = 1;	// nawet jeœli w ostatniej iteracji zostanie pojedyñczy bajt
	else		//jeœli nie pilne, to bierzemy tylko ca³ymi d³ugoœciami
		minLen = STTP_DATA_FIELD_LEN;	//pola danych ramki STTP, najwy¿ej coœ zostanie w buforze

	int buffer_data_size = buffer.get_data_size();
	
	
	while(buffer_data_size >= minLen)
	{
		int buffer_data_size = buffer.get_data_size();
		
		if (urgent)	//jeœli pilne, wyœlemy z bufora wszystko,
		{			// nawet jeœli w ostatniej iteracji zostanie pojedyñczy bajt
			minLen = 1;	
			if (buffer_data_size) > STTP_DATA_FIELD_LEN)	//...ale za jednym razem 
				actualLen = STTP_DATA_FIELD_LEN;		//co najwy¿ej tyle,
			else										//ile siê mieœci
				actualLen = buffer_data_size;			//w polu danych ramki STTP
		}
		else		//jeœli nie pilne, to bierzemy tylko ca³ymi d³ugoœciami
		{			//pola danych ramki STTP, najwy¿ej coœ zostanie w buforze
			minLen = STTP_DATA_FIELD_LEN;	
			actualLen = STTP_DATA_FIELD_LEN;	
		}
		
		dataField = buffer.get_packed_data_piece(0, actualLen);
		buffer.del_data_piece(0, actualLen);
		
		prepare_sttp_frame(dataField);
		//sttpFrame = encrypt(sttpFrame.get_data_instance(),session_key.c_str());
		
		to_net(sttpFrame);
	}
	
	return actualLen;
};

void STTP::single_receive()
{
	RawData data, buffer;
	
	data = from_net();
	//przetwarzanie, w tym: wy³uskanie ramki, ewentualne zostawienie czegoœ w buforze i czekanie, jeœli mamy kawa³ek ramki na koñcu,
	//odszyfrowanie, wszelkie sprawdzenie poprawnoœci; jeœli coœ nie tak - chyba trzeba przes³aæ w górê odpowiedni¹ ramkê,
	//¿eby logika mog³a zakoñczyæ to po³¹czenie - tak, ta warstwa musi umieæ zrobiæ tak¹ ramkê, ale tylko tak¹ :)
	//a jeœli wszystko dobrze, wy³uskujemy z ramki STTP przenoszone przez ni¹ dane, po czym...
	to_controller(data);
};
	
	
STTP::STTP(queue<RawData>* nq, queue<RawData>* cq)
{
	//ten kostruktor pewnie bêdzie mia³ wiêcej parametrów i w ogóle jak¹œ treœæ
};

STTP::~STTP()
{
	//podobnie, jak powy¿ej
};

int STTP::single_transmit()
{
	if(direction == DIR_SENDING)
		single_send();
	else if(direction == DIR_RECEIVING)
		single_receive();
};

int STTP::get_data_field_len()
{
	return dataFieldLen;
};