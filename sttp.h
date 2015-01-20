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
	const int signFieldLen;	//d³ugoœæ pola podpisu w ramce STTP, inicjowana wartoœci¹ zdefiniowanej sta³ej
	const int sttpFrameSize;	//d³ugoœæ ramki STTP, inicjowana wartoœci¹ obliczon¹ na podstawie zdefiniowanych sta³ych
	std::queue<RawData>* netQueue;	//wskaŸnik na kolejkê, poœrednicz¹c¹ w komunikacji z warstw¹ obs³uguj¹c¹ sockety
	std::queue<RawData>* toControllerQueue;	//wskaŸnik na kolejkê, z której pobiera dane kontroler
	std::queue<PrioritableRawData>* fromControllerQueue; //wskaŸnik na kolejkê, do której wstawia dane kontroler
	unsigned char frameCtrlNr;	//numer kontrolny ramki - w nag³ówku ka¿dej ramki, umo¿liwia kontrolê integralnoœci danych
	RawData buffer;		//bufor s³u¿¹cy ³¹czeniu fragmentów ramek / dzieleniu danych na jednakowe porcje
	std::string sessionKey;	//uzgodniony w czasie autoryzacji klucz sesyjny

	void to_net(RawData data);	//umieszcza dane w kolejce ni¿szej warstwy
	void to_controller(RawData data);	//umieszcza dane w kolejce wy¿szej warstwy
	RawData from_net();			//pobiera dane z kolejki od ni¿szej warstwy
	PrioritableRawData from_controller();	//pobiera dane z kolejki od wy¿szej warstwy
	RawData prepare_sttp_frame(RawData dataField);	//opakowuje dane w ramkê STTP; zwróci puste RawData!!!, jeœli dataField ma wiêcej bajtów ni¿ STTP_DATA_FIELD_LEN
	RawData make_frame_disconnect(char whyDisconnecting); //tworzy ramkê protoko³u komunikacyjnego powoduj¹c¹ roz³¹czenie, z informacj¹ o zagro¿eniu bezpieczeñstwa transmisji
	int single_send();	//wys³anie pojedyñczej ramki protoko³u komunikacyjnego; zwraca iloœæ bajtów wys³anych wewn¹trz pola danych ramki STTP
	int single_receive(); //zwraca iloœæ bajtów przekazanych do warstwy kontrolera


	public:

	STTP(std::string sesKey, int dir, std::queue<RawData>* nq, void* cq);	//konstruktor - z wyborem kierunku transmisji danych (dir = DIR_TO_NET lub DIR_FROM_NET)
	~STTP();	//destruktor - domyslny

	int single_transmit();	//single_send albo single_receive, w zale¿noœci od direction; zwraca przes³an¹ iloœæ bajtów protoko³u komunikacyjnego
};


#endif