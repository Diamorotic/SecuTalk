#include <cstdio>
#include <cstdlib>
#include <stdio.h>
#include <iostream>

#include <winsock2.h>
#include "deklaracje.hh"

using namespace std;

void data_copy2(char* dest, const char* src, int length)
{
    for( int i=0; i<length; ++i)
        dest[i] = src[i];
}


int runClient()
{
    WSADATA wsaData;

    int result = WSAStartup( MAKEWORD( 2, 2 ), & wsaData );
    if( result != NO_ERROR )
         printf( "C: Initialization error.\n" );

    SOCKET mainSocket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
    if( mainSocket == INVALID_SOCKET )
    {
        printf( "C: Error creating socket: %ld\n", WSAGetLastError() );
        WSACleanup();
        return 1;
    }

    sockaddr_in service;
    memset( & service, 0, sizeof( service ) );
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr( "127.0.0.1" );
    service.sin_port = htons( 5555 );

    if( connect( mainSocket,( SOCKADDR * ) & service, sizeof( service ) ) == SOCKET_ERROR )
    {
        printf( "C: Failed to connect.\n" );
        WSACleanup();
        return 1;
    }


    cout << "Wpisz r to register, albo l to log in. :)\n";
    char mode;
    while (mode != 'r' && mode != 'l')
        cin >> mode;

    string name, pwd;
    cout << "Login:\n";
    cin >> name;
    cout << "Haslo:\n";
    cin >> pwd;

    //obliczanie, haha, hasha hasla :P

    char frame[MAXLEN*2+2];

    for (int i = 0; i < MAXLEN*2+2; i++)
        frame[i] = ' ';

    frame[0] = mode;

    data_copy2(frame+1, name.c_str(), name.length());
    data_copy2(frame+1+MAXLEN, pwd.c_str(), pwd.length());
    frame[MAXLEN*2+1] = 0;

    cout << "C: Oto jest ramka: " << string(frame) << ".\n";


    int bytesSent;
    int bytesRecv = SOCKET_ERROR;

    bytesSent = send( mainSocket, frame, 2*MAXLEN+1, 0 );
    printf( "C: Bytes sent: %ld\n", bytesSent );


char recvbuf[ MAXLEN*2+2 ] = " ";

    while( true )
    {
        cout << "Wchodzi w petle...\n";
       // bytesRecv = recv( mainSocket, recvbuf, 64, 0 );
        while(bytesRecv<1)
            bytesRecv = recv( (mainSocket), recvbuf, MAXLEN*2+2, 0 )+bytesRecv;

        if( bytesRecv == 0 || bytesRecv == WSAECONNRESET )
        {
            printf( "C: Connection closed.\n" );
            break;
        }

        if( bytesRecv < 0 )
             return 1;

        printf( "C: Bytes received: %ld\n", bytesRecv );
        printf( "C: Received text: %s\n", recvbuf );
        bytesRecv=0;
    }
    system("pause");
}
