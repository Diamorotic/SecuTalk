#ifndef STTP_H
#define STTP_H


#include <windows.h>
#include <queue>
#include <stdlib.h>

#include "deklaracje.h"
#include "PrioritableRawData.h"


class STTP
{
	private:

	const int direction;	//DIR_TO_NET lub DIR_FROM_NET
	const int signFieldLen;	//d�ugo�� pola podpisu w ramce STTP, inicjowana warto�ci� zdefiniowanej sta�ej
	const int sttpFrameSize;	//d�ugo�� ramki STTP, inicjowana warto�ci� obliczon� na podstawie zdefiniowanych sta�ych
	std::queue<RawData>* netQueue;	//wska�nik na kolejk�, po�rednicz�c� w komunikacji z warstw� obs�uguj�c� sockety
	std::queue<RawData>* toControllerQueue;	//wska�nik na kolejk�, z kt�rej pobiera dane kontroler
	std::queue<PrioritableRawData>* fromControllerQueue; //wska�nik na kolejk�, do kt�rej wstawia dane kontroler
	unsigned char frameCtrlNr;	//numer kontrolny ramki - w nag��wku ka�dej ramki, umo�liwia kontrol� integralno�ci danych
	RawData buffer;		//bufor s�u��cy ��czeniu fragment�w ramek / dzieleniu danych na jednakowe porcje
	std::string sessionKey;	//uzgodniony w czasie autoryzacji klucz sesyjny

	void to_net(RawData data);	//umieszcza dane w kolejce ni�szej warstwy
	void to_controller(RawData data);	//umieszcza dane w kolejce wy�szej warstwy
	RawData from_net();			//pobiera dane z kolejki od ni�szej warstwy
	PrioritableRawData from_controller();	//pobiera dane z kolejki od wy�szej warstwy
	RawData prepare_sttp_frame(RawData dataField);	//opakowuje dane w ramk� STTP; zwr�ci puste RawData!!!, je�li dataField ma wi�cej bajt�w ni� STTP_DATA_FIELD_LEN
	RawData make_frame_disconnect(char whyDisconnecting); //tworzy ramk� protoko�u komunikacyjnego powoduj�c� roz��czenie, z informacj� o zagro�eniu bezpiecze�stwa transmisji
	int single_send();	//wys�anie pojedy�czej ramki protoko�u komunikacyjnego; zwraca ilo�� bajt�w wys�anych wewn�trz pola danych ramki STTP
	int single_receive(); //zwraca ilo�� bajt�w przekazanych do warstwy kontrolera


	public:

	STTP(std::string sesKey, int dir, std::queue<RawData>* nq, void* cq);	//konstruktor - z wyborem kierunku transmisji danych (dir = DIR_TO_NET lub DIR_FROM_NET)
	~STTP();	//destruktor - domyslny

	int single_transmit();	//single_send albo single_receive, w zale�no�ci od direction; zwraca przes�an� ilo�� bajt�w protoko�u komunikacyjnego
};


#endif