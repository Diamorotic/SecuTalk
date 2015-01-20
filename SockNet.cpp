#include "SockNet.h"
#include "SockNetSet.h"

//wysy³a dane do sieci
int SockNet::to_net(RawData data)
{
	char* ptr = data.get_data_instance();
	int size = data.get_data_size();

	int ret = send(sckt, ptr, size, 0);

	delete ptr;

	return ret;
};

//umieszcza dane w kolejce wy¿szej warstwy (STTP)
void SockNet::to_sttp(RawData data)
{
	//lock + jakaœ obrona przed pe³n¹ kolejk¹
	sttpQueue->push(data);
	//unlock + ew. jakiœ sygna³ o pustej kolejce
};

//pobiera dane z sieci
RawData SockNet::from_net()
{
	char* buf_ptr = new char[RECV_BUFFER_LEN];
	int size = recv(sckt, buf_ptr, RECV_BUFFER_LEN, 0);

	RawData data(buf_ptr, size);

	delete buf_ptr;

	return data;
};

//pobiera dane z kolejki od wy¿szej warstwy (STTP)
RawData SockNet::from_sttp()
{
	RawData data;

	//lock + jakaœ obrona przed pust¹ kolejk¹
	data = sttpQueue->pull();
	//sttpQueue->pop();
	//unlock + ew. jakiœ sygna³ o pe³nej kolejce

	return data;
};

//przesy³a dane z kolejki warstwy STTP do sieci, zwraca iloœæ przes³anych bajtów
int SockNet::send_data()
{
	RawData data = from_sttp();
	int bytesSent = to_net(data);

	return bytesSent;
};

//przesy³a dane z sieci do kolejki warstwy STTP, zwraca iloœæ przes³anych bajtów
int SockNet::receive_data()
{
	RawData data = from_net();

	to_sttp(data);

	return data.get_data_size();
};

//konstruktor, s³u¿¹cy do budowania "transmisyjnych" kopii z inicjalizacyjnego orygina³u
SockNet::SockNet(SOCKET s, int dir, int st, SharedQueue<RawData>* sttpQ)
: direction(dir)
{
    sckt = s;
	state = st;

	sttpQueue = sttpQ;
};

//konstruktor tworz¹cy inicjalizacyjny obiekt SockNet
SockNet::SockNet(std::string adress, short port) : direction(NO_DIR)
{
    std::cout << "SockNet::SockNet(): 1.\n";

	sttpQueue = NULL;

	//przygotowanie do odbierania po³¹czeñ
	WSADATA wsaData;

	std::cout << "SockNet::SockNet(): 2.\n";
	
	int result = WSAStartup( MAKEWORD( 2, 2 ), & wsaData );

	if( result != NO_ERROR )
	{
		std::cout << "S: Initialization error.\n";
		state = ERRORED;
		return;
	}
	std::cout << "SockNet::SockNet(): 3.\n";

	sckt = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

	if( sckt == INVALID_SOCKET )
	{
		std::cout << "S: Error creating socket: " << WSAGetLastError() << '\n';
		WSACleanup();
		state = ERRORED;
		return;
	}

	sockaddr_in service;
	memset( & service, 0, sizeof( service ) );
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = inet_addr( adress.c_str() );
	service.sin_port = htons( port );

	if( bind( sckt,( SOCKADDR * ) & service, sizeof( service ) ) == SOCKET_ERROR )
	{
		std::cout << "S: bind() failed.\n";
		closesocket( sckt );
		state = ERRORED;
		return;
	}

	if( listen( sckt, 1 ) == SOCKET_ERROR )
	{
		std::cout << "S: Error listening on socket.\n";
		state = ERRORED;
	}

	state = ABLE_TO_CONNECT;

};

SockNet::~SockNet()
{
	closesocket(sckt);
};


SockNetSet SockNet::wait_for_incoming_connection(SharedQueue<RawData>* tSttpQ, SharedQueue<RawData>* fSttpQ)
{
	if (state != ABLE_TO_CONNECT)
		return SockNetSet(NULL, NULL);

	SOCKET acceptSocket = SOCKET_ERROR;

	do
	{
		acceptSocket = accept( sckt, NULL, NULL );
	}
    while (acceptSocket == SOCKET_ERROR);

	SockNet sendSN(acceptSocket, DIR_TO_NET, CONNECTED, fSttpQ);
	SockNet recvSN(acceptSocket, DIR_FROM_NET, CONNECTED, tSttpQ);

	return SockNetSet(&sendSN, &recvSN);
};


SockNetSet SockNet::timed_wait_for_incoming_connection(int timeout, SharedQueue<RawData>* tSttpQ, SharedQueue<RawData>* fSttpQ)
{
	if (state != ABLE_TO_CONNECT)
		return SockNetSet(NULL, NULL);


	time_t time0 = time(NULL);
	time_t time1;

	SOCKET acceptSocket = SOCKET_ERROR;

	do
	{
		acceptSocket = accept( sckt, NULL, NULL );

		time1 = time(NULL);
	}
    while ( acceptSocket == SOCKET_ERROR  &&  difftime(time1, time0) <= timeout );

	if (acceptSocket == SOCKET_ERROR)
		return SockNetSet(NULL, NULL);

	SockNet sendSN(acceptSocket, DIR_TO_NET, CONNECTED, fSttpQ);
	SockNet recvSN(acceptSocket, DIR_FROM_NET, CONNECTED, tSttpQ);

	return SockNetSet(&sendSN, &recvSN);
};

int SockNet::get_state()
{
	return state;
};

int SockNet::transmit_data()
{
	if (direction == DIR_TO_NET)
		return send_data();
	else if (direction == DIR_FROM_NET)
		return receive_data();
	else
		return 0;
};
