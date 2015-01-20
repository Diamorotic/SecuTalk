#include "deklaracje.h"
#include "SockNetSet.h"
#include "SockNet.h"
#include "SharedQueue.h"
#include "sttp.h"


class ThreadParams
{
	public:
	SharedQueue<RawData>* lowerQueuePtr;
	SharedQueue<RawData>* higherQueuePtr;
	std::string seskey;
};


DWORD WINAPI sn_sending(LPVOID lpParam)
{
	SockNet* Sn = (SockNet*)lpParam;

	while (true)
		Sn->transmit_data();

	return 0;
};

DWORD WINAPI sn_receiving(LPVOID lpParam)
{
	SockNet* Sn = (SockNet*)lpParam;

	while (true)
		Sn->transmit_data();

	return 0;
};

DWORD WINAPI sttp_sending(LPVOID lpParam)
{
	ThreadParams* params = (ThreadParams*)lpParam;
	SharedQueue<RawData>* nq = params->lowerQueuePtr;
	SharedQueue<RawData>* cq = params->higherQueuePtr;
	std::string seskey = params->seskey;

	STTP sttp(seskey, DIR_TO_NET, nq, cq);
	std::cout << "Jestem sttp_receiving, dostałem klucz " << seskey << ".\n";
	while (true)
		sttp.single_transmit();
};

DWORD WINAPI sttp_receiving(LPVOID lpParam)
{
	ThreadParams* params = (ThreadParams*)lpParam;
	SharedQueue<RawData>* nq = params->lowerQueuePtr;
	SharedQueue<RawData>* cq = params->higherQueuePtr;
	std::string seskey = params->seskey;

	STTP sttp(seskey, DIR_FROM_NET, nq, cq);

	std::cout << "Jestem sttp_receiving, dostałem klucz " << seskey << ".\n";
	while (true)
		sttp.single_transmit();
};

//funkcja uruchamiana w wątku głównego przetwarzania - odpowiada za całą logikę działania serwera
DWORD WINAPI main_processing(LPVOID lpParam)
{
	std::cout << "main processing działa\n";
    SockNetSet* SnS = (SockNetSet*)lpParam;

	SockNet* sNsending = SnS->sending;
	SockNet* sNreceiving = SnS->receiving;
	SharedQueue<RawData>* socknetToSttpQueue = SnS->receivingSttpQueue;
	SharedQueue<RawData>* sttpToSockNetQueue = SnS->sendingSttpQueue;

	SharedQueue<RawData>* sttpToControllerQueue = new SharedQueue < RawData >;
	SharedQueue<RawData>* controllerToSttpQueue = new SharedQueue < RawData >;
	std::string sk("seskeyseskey");

	ThreadParams sttpSendingParams;
	sttpSendingParams.higherQueuePtr = controllerToSttpQueue;
	sttpSendingParams.lowerQueuePtr = sttpToSockNetQueue;
	sttpSendingParams.seskey = sk;

	ThreadParams sttpReceivingParams;
	sttpSendingParams.higherQueuePtr = socknetToSttpQueue;
	sttpSendingParams.lowerQueuePtr = sttpToControllerQueue;
	sttpSendingParams.seskey = sk;

	HANDLE threads[4];

	//tutaj powstają wątki najniższej warstwy, wysyłający i odbierający,
	//i wątki kontrolera, wysyłający i odbierający
	threads[0] = CreateThread(NULL, 0, sn_sending, &sNsending, 0, NULL);
	threads[1] = CreateThread(NULL, 0, sn_receiving, &sNreceiving, 0, NULL);
	threads[2] = CreateThread(NULL, 0, sttp_sending, &sttpSendingParams, 0, NULL);
	threads[3] = CreateThread(NULL, 0, sttp_receiving, &sttpReceivingParams, 0, NULL);


	WaitForMultipleObjects(4, threads, true, INFINITE);
	return 0;
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
		SharedQueue<RawData>* tSq = new SharedQueue<RawData>;
		SharedQueue<RawData>* fSq = new SharedQueue<RawData>;

		SockNetSet connectedSnS = sn.timed_wait_for_incoming_connection(TIMEOUT, tSq, fSq);
		if (connectedSnS.sending != NULL  &&  connectedSnS.receiving != NULL)
		{
			connectedSnS.receivingSttpQueue = tSq;
			connectedSnS.sendingSttpQueue = fSq;

			tSq = new SharedQueue<RawData>;
			fSq = new SharedQueue<RawData>;
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
