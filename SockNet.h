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
	SharedQueue<RawData>* sttpQueue;	//wskaŸnik na kolejkê, do której wrzuca / z której pobiera dane warstwa STTP

	int to_net(RawData data);	//wysy³a dane do sieci
	void to_sttp(RawData data);	//umieszcza dane w kolejce wy¿szej warstwy (STTP)
	RawData from_net();		//pobiera dane z sieci
	RawData from_sttp();	//pobiera dane z kolejki od wy¿szej warstwy (STTP)
	int send_data();	//przesy³a dane z kolejki kontrolera do sieci, zwraca iloœæ przes³anych bajtów
	int receive_data();			//przesy³a dane z sieci do kolejki kontrolera, zwraca iloœæ przes³anych bajtów


	SockNet(SOCKET s, int dir, int st, SharedQueue<RawData>* sttpQ);	//ten konstruktor s³u¿y do przygotowania "kopii" obiektu SockNet,
	//które bêd¹ s³u¿yæ ju¿ do obs³ugi transmisji danych przez socket (w obie strony - dwie kopie)

	public:
	//tym konstuktorem tworzymy obiekt na pocz¹tku, po utworzeniu powinien byæ w stanie ABLE_TO_CONNECT, czyli z socketem nas³uchuj¹cym
	//potem u¿ywamy którejœ z funkcji wait_for_incoming_connection / wait_for... itd., która zwraca zestaw dwóch obiektów SockNet:
	//jeden w trybie odbierania danych, drugi w trybie wysy³ania, oba "po³¹czone" z tym samym socketem
	SockNet(std::string adress, short port);
	~SockNet();

	//obie poni¿sze metody zwracaj¹ albo obiekt SockNetSet ze wskaŸnikami na dwa obiekty SockNet,
	//po³¹czone z w pe³ni zasocjowawanym socketem (patrz powy¿ej opis konstruktora),
	//albo obiekt SockNetSet ze wskaŸnikami z wartoœci¹ NULL, jeœli pierwotny SockNet nie by³ w stanie ABLE_TO_CONNECT
	//lub przed up³ywem timeoutu nie nadesz³o ¿adne po³¹czenie

	SockNetSet wait_for_incoming_connection(SharedQueue<RawData>* tSttpQ, SharedQueue<RawData>* fSttpQ);	//funkcja blokuj¹ca!!!
	SockNetSet timed_wait_for_incoming_connection(int timeout, SharedQueue<RawData>* tSttpQ, SharedQueue<RawData>* fSttpQ);
	int get_state();
	int transmit_data(); //send_data(RawData data) albo receive_data(), w zale¿noœci od direction; zwraca przes³an¹ iloœæ bajtów
};


#endif
