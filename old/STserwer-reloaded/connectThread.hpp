#include "serwer.hh"
using namespace std;

extern DWORD WINAPI authorization(LPVOID lpParam );

class ConnectThread : public ThreadBase
{
private:
public:
    ConnectThread() { }

    virtual void run()
    {
        ///ustawienie serwera w tryb odbierania polaczen///////////////////////////////////////////
        WSADATA wsaData;

        int result = WSAStartup( MAKEWORD( 2, 2 ), & wsaData );
        if( result != NO_ERROR )
            printf( "S: Initialization error.\n" );

        SOCKET mainSocket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
        if( mainSocket == INVALID_SOCKET )
        {
            printf( "S: Error creating socket: %d\n", WSAGetLastError() );
            WSACleanup();
        }

        sockaddr_in service;
        memset( & service, 0, sizeof( service ) );
        service.sin_family = AF_INET;
        service.sin_addr.s_addr = inet_addr( "127.0.0.1" );         ///adres i port///////////////
        service.sin_port = htons( 5555 );

        if( bind( mainSocket,( SOCKADDR * ) & service, sizeof( service ) ) == SOCKET_ERROR )
        {
            printf( "S: bind() failed.\n" );
            closesocket( mainSocket );
        }

        if( listen( mainSocket, 1 ) == SOCKET_ERROR )
            printf( "S: Error listening on socket.\n" );

        SOCKET acceptSocket = SOCKET_ERROR;
        printf( "S: Waiting for a client to connect...\n" );
        ///koniec inicjalizacji socketa/////////////////////////////////////////////////////////////////////////////////////////

        while(true)
        {
            acceptSocket = accept( mainSocket, NULL, NULL );
            if ( acceptSocket != SOCKET_ERROR ) //na MSDN pisza o INVALID_SOCKET, nie ma nic o SOCKET_ERROR (?)
            {
                CreateThread( NULL, 0,authorization, &acceptSocket, 0, NULL);
                //robi sie nowy watek, dla kazdego usera jeden
            }
        }
    }

};

