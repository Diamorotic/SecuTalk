#include "deklaracje.h"
#include "SockNetSet.h"
#include "SockNet.h"


//funkcja uruchamiana w wątku głównego przetwarzania - odpowiada za całą logikę działania serwera
DWORD WINAPI main_processing(LPVOID lpParam)
{
    SockNetSet* SnS = (SockNetSet*)lpParam;

	SockNet* sNsending = SnS->sending;
	SockNet* sNreceiving = SnS->receiving;

	//tutaj powstają wątki najniższej warstwy, wysyłający i odbierający,
	//i wątki kontrolera, wysyłający i odbierający





};

//funkcja uruchamiana w wątku przyjmującym połączenia - tu ma początek wszystko inne
DWORD WINAPI connect_thread_func(LPVOID lpParam)
{

	SockNet sn(std::string("127.0.0.1"), 5555);
	std::cout << "socket sie zrobil, jego stan to " << sn.get_state() << '\n';
	if ( sn.get_state() == ERRORED )
		exit(-1);

	while(true)
	{
		std::queue<RawData>* tSq = new std::queue<RawData>;
		std::queue<RawData>* fSq = new std::queue<RawData>;

		SockNetSet connectedSnS = sn.timed_wait_for_incoming_connection(TIMEOUT, tSq, fSq);
		if (connectedSnS.sending != NULL  &&  connectedSnS.receiving != NULL)
		{
			connectedSnS.recevingSttpQueue = tSq;
			connectedSnS.sendingSttpQueue = fSq;

			tSq = new std::queue<RawData>;
            fSq = new std::queue<RawData>;
			//tworzony tu jest wątek głównego przetwarzania dla każdego łączącego się użytkownika,
			//który potem uruchamia wątki podlegających mu warstw

			CreateThread(NULL, 0, main_processing, &connectedSnS, 0, NULL);
		}
	}

};
/*

w¹tek main_processing:
CreateLayers(connectedSn)

CreateLayers(SockNetSet connectedSn)
{
	std::queue<RawData> netToSttpQueue;
	std::queue<RawData> SttpToCntrlrQueue;
	std::queue<RawData> netToSttpQueue;
	std::queue<RawData> netToSttpQueue;
	std::queue<RawData> netToSttpQueue;
	std::queue<RawData> netToSttpQueue;
	CreateThread( NULL, 0,sn_rcv, connectedSn.receiving, 0, NULL);
	CreateThread( NULL, 0,sn_snd connectedSn.sending, 0, NULL);
	CreateThread( NULL, 0,sttp_rcv, connectedSn.receiving, 0, NULL);
	CreateThread( NULL, 0,sttp_snd, connectedSn.sending, 0, NULL);
	CreateThread( NULL, 0,cntrlr_rcv, connectedSn.receiving, 0, NULL);
	CreateThread( NULL, 0,cntrlr_send, connectedSn, 0, NULL);
}
*/

//w wątku wysyłającym/odbierającym w pętli wywołujemy WSAWaitForMultipleEvents(), a po niej SockNet::transmit_data();
