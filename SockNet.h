#ifndef SOCKNET_H
#define SOCKNET_H

#include "SharedQueue.h"
#include "deklaracje.h"
#include "RawData.h"
#include "SockNetSet.h"

//Have you ever wonder if "socket" has something to do with a sock...?

class SockNet
{
	private:
	SOCKET sckt;
	const int direction;	//DIR_TO_NET, DIR_FROM_NET lub NO_DIR
	int state;				//ABLE_TO_CONNECT, CONNECTED, ERRORED
	SharedQueue<RawData>* sttpQueue;	//wska�nik na kolejk�, do kt�rej wrzuca / z kt�rej pobiera dane warstwa STTP

	int to_net(RawData data);	//wysy�a dane do sieci
	void to_sttp(RawData data);	//umieszcza dane w kolejce wy�szej warstwy (STTP)
	RawData from_net();		//pobiera dane z sieci
	RawData from_sttp();	//pobiera dane z kolejki od wy�szej warstwy (STTP)
	int send_data();	//przesy�a dane z kolejki kontrolera do sieci, zwraca ilo�� przes�anych bajt�w
	int receive_data();			//przesy�a dane z sieci do kolejki kontrolera, zwraca ilo�� przes�anych bajt�w


	SockNet(SOCKET s, int dir, int st, SharedQueue<RawData>* sttpQ);	//ten konstruktor s�u�y do przygotowania "kopii" obiektu SockNet,
	//kt�re b�d� s�u�y� ju� do obs�ugi transmisji danych przez socket (w obie strony - dwie kopie)

	public:
	//tym konstuktorem tworzymy obiekt na pocz�tku, po utworzeniu powinien by� w stanie ABLE_TO_CONNECT, czyli z socketem nas�uchuj�cym
	//potem u�ywamy kt�rej� z funkcji wait_for_incoming_connection / wait_for... itd., kt�ra zwraca zestaw dw�ch obiekt�w SockNet:
	//jeden w trybie odbierania danych, drugi w trybie wysy�ania, oba "po��czone" z tym samym socketem
	SockNet(std::string adress, short port);
	~SockNet();

	//obie poni�sze metody zwracaj� albo obiekt SockNetSet ze wska�nikami na dwa obiekty SockNet,
	//po��czone z w pe�ni zasocjowawanym socketem (patrz powy�ej opis konstruktora),
	//albo obiekt SockNetSet ze wska�nikami z warto�ci� NULL, je�li pierwotny SockNet nie by� w stanie ABLE_TO_CONNECT
	//lub przed up�ywem timeoutu nie nadesz�o �adne po��czenie

	SockNetSet wait_for_incoming_connection(SharedQueue<RawData>* tSttpQ, SharedQueue<RawData>* fSttpQ);	//funkcja blokuj�ca!!!
	SockNetSet timed_wait_for_incoming_connection(int timeout, SharedQueue<RawData>* tSttpQ, SharedQueue<RawData>* fSttpQ);
	int get_state();
	int transmit_data(); //send_data(RawData data) albo receive_data(), w zale�no�ci od direction; zwraca przes�an� ilo�� bajt�w
};


#endif
