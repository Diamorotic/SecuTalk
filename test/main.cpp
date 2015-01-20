#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

#define DATA "abcd4efghij1kl³mn9oprstuwyzzz"
#define DATA2 "e"

using namespace std;

int main(int argc, char *argv[])
{/*
    char tab[30];
    char* d = DATA;

    for(int i=0; i<30; i++)
        tab[i] = d[i];

    tab[4]=char(4);
    tab[11]=char(1);
    tab[17]=char(11);*/

    char offsets[] = {4, 2, 4};

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

	if( connect( mainSocket,( SOCKADDR * ) & service, sizeof( service ) ) == SOCKET_ERROR )
	{
		printf( "S: connect() failed.\n" );
		closesocket( mainSocket );
	}
    char c = 'f';
	if (send( mainSocket, tab, 26, 0 ) == -1)
		perror("writing on stream socket");/*
   	if (send( mainSocket, DATA2, sizeof DATA2, 0 ) == -1)
		perror("writing on stream socket");
    if (send( mainSocket, &c, 1, 0 ) == -1)
		perror("writing on stream socket");*/
/*
    ofstream plik;
    plik.open("result.txt",fstream::out);
    int sent;
    for (int i=0; i<2000000; i++)
    {
        if ((sent = send( mainSocket, &c, 1, 0 )) < 0)
            perror("writing on stream socket");
        else
        {
            cout << i << ' ' << sent << '\n';
            plik << i << ' ' << sent << '\n';
        }

    }
*/
	closesocket(mainSocket);
	//plik.close();
	exit(0);

}
