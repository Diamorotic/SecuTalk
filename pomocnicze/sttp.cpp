#ifndef STTP_CPP
#define STTP_CPP

#include "sttp.h"
/*
void STTP::to_net(RawData data)
{
	//lock + jaka� obrona przed pe�n� kolejk�
	net_queue->push(data);
	//unlock + ew. jaki� sygna� o pustej kolejce
};

void STTP::to_controller(RawData data)
{
	//lock + jaka� obrona przed pe�n� kolejk�
	controller_queue->push(data);
	//unlock + ew. jaki� sygna� o pustej kolejce
};

RawData STTP::from_net()
{
	RawData data;
	
	//lock + jaka� obrona przed pust� kolejk�
	data = netQueue->pop();
	//unlock + ew. jaki� sygna� o pe�nej kolejce
	
	return data;
};

PrioritableRawData STTP::from_controller()
{
	PrioritableRawData data;
	
	//lock + jaka� obrona przed pust� kolejk�
	pData = controllerQueue->pop();
	//unlock + ew. jaki� sygna� o pe�nej kolejce
	
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
	
	if (urgent)	//je�li pilne, wy�lemy z bufora wszystko,
		minLen = 1;	// nawet je�li w ostatniej iteracji zostanie pojedy�czy bajt
	else		//je�li nie pilne, to bierzemy tylko ca�ymi d�ugo�ciami
		minLen = STTP_DATA_FIELD_LEN;	//pola danych ramki STTP, najwy�ej co� zostanie w buforze

	int buffer_data_size = buffer.get_data_size();
	
	
	while(buffer_data_size >= minLen)
	{
		int buffer_data_size = buffer.get_data_size();
		
		if (urgent)	//je�li pilne, wy�lemy z bufora wszystko,
		{			// nawet je�li w ostatniej iteracji zostanie pojedy�czy bajt
			minLen = 1;	
			if (buffer_data_size) > STTP_DATA_FIELD_LEN)	//...ale za jednym razem 
				actualLen = STTP_DATA_FIELD_LEN;		//co najwy�ej tyle,
			else										//ile si� mie�ci
				actualLen = buffer_data_size;			//w polu danych ramki STTP
		}
		else		//je�li nie pilne, to bierzemy tylko ca�ymi d�ugo�ciami
		{			//pola danych ramki STTP, najwy�ej co� zostanie w buforze
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
	//przetwarzanie, w tym: wy�uskanie ramki, ewentualne zostawienie czego� w buforze i czekanie, je�li mamy kawa�ek ramki na ko�cu,
	//odszyfrowanie, wszelkie sprawdzenie poprawno�ci; je�li co� nie tak - chyba trzeba przes�a� w g�r� odpowiedni� ramk�,
	//�eby logika mog�a zako�czy� to po��czenie - tak, ta warstwa musi umie� zrobi� tak� ramk�, ale tylko tak� :)
	//a je�li wszystko dobrze, wy�uskujemy z ramki STTP przenoszone przez ni� dane, po czym...
	to_controller(data);
};
	
	
STTP::STTP(queue<RawData>* nq, queue<RawData>* cq)
{
	//ten kostruktor pewnie b�dzie mia� wi�cej parametr�w i w og�le jak�� tre��
};

STTP::~STTP()
{
	//podobnie, jak powy�ej
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
*/
#endif /*STTP_CPP*/
