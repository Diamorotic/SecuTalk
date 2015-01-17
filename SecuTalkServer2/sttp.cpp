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

RawData STTP::from_controller()
{
	RawData data;
	
	//lock + jakaœ obrona przed pust¹ kolejk¹
	data = controllerQueue->pop();
	//unlock + ew. jakiœ sygna³ o pe³nej kolejce
	
	return data;
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
	buffer.add_data(from_controller());
	//powy¿ej OK
	RawData dataField;
	int minLen, actualLen;
	
	int buffer_data_size = buffer.get_data_size();
	
	if (force_sending)
	{
		minLen = 1;
		if (buffer_data_size > STTP_DATA_FIELD_LEN)
			actualLen = STTP_DATA_FIELD_LEN;
		else
			actualLen = buffer_data_size;
	}
	else
	{
		minLen = STTP_DATA_FIELD_LEN;
		actualLen = STTP_DATA_FIELD_LEN;
	}
	
	while(buffer_data_size >= minLen)
	{
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