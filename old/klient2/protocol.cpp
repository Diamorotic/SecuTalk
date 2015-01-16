#include "protocol.h"
#include <string>
#include <QtGui>
#include <iostream>
#include "read_write_socket.h"
#include "sendThread.h"
 #include <QTimer>
#include <windows.h>
#include "watcher.h"

//=====================================================//

void protocol::data_copy(char* dest, const char* src, int length)
{
    for( int i=0; i<length; ++i)
        dest[i+actual_pos] = src[i];
    actual_pos += length;
}

//=====================================================//


protocol::protocol()
{
    bufor = new char[1024];
    bufor_size = 1024;
    actual_pos = 0;


}

protocol::~protocol()
{
    delete bufor;
}


void protocol::resize_bufor( unsigned int new_size )
{
    char* new_buf = new char[new_size];
    data_copy( new_buf, bufor, bufor_size );
    bufor_size = new_size;
    delete[] bufor;
    bufor = new_buf;
    actual_pos = 0;		//w data_copy zmieniliśmy wartość
}


//pakiet danych o użytkowniku
//wysyłany przez serwer:
// - na początku, jako lista kontaktów
// - jako odpowiedź na wyszukiwanie użytkownika
void protocol::packet_user_data(read_write_socket* socket, user_data* data)
{
    unsigned int size;
    actual_pos = 0;     //zerujemy licznik

    unsigned char   msg_id = RAMKA_USER_DATA;
    unsigned short  user_id = data->numer;
    unsigned char   state = data->state;
    unsigned char   key_num = data->key_num;
    unsigned char   length = data->login.length() + 1;  //wysyłamy \0
    std::string login = data->login.toStdString();

    size = 6 + length;
    if( size > bufor_size )
        resize_bufor( size );

    data_copy( bufor, (char*)&msg_id, 1 );
    data_copy( bufor, (char*)&user_id, 2 );
    data_copy( bufor, (char*)&state, 1 );
    data_copy( bufor, (char*)&key_num, 1 );
    data_copy( bufor, (char*)&length, 1 );
    data_copy( bufor, login.c_str(), length );

    send_package(socket,bufor,size);
}


//wysyłamy wiadomośc tekstową
void protocol::packet_message(read_write_socket* socket, text_message* data)
{
    unsigned int size ;
    actual_pos = 0;     //zerujemy licznik

    unsigned char   msg_id = RAMKA_MESSAGE;
    unsigned short  sender_id = data->sender_id;
    unsigned short  receiver_id = data->receiver_id;
    unsigned short  msg_number = data->msg_number;
    unsigned char   key_num = data->key_num;
    unsigned short  length = data->text.length() + 1;  //wysyłamy \0
    std::string text = data->text.toStdString();

    size = 10 + length;
    if( size > bufor_size )
        resize_bufor( size );

    data_copy( bufor, (char*)&msg_id, 1 );
    data_copy( bufor, (char*)&sender_id, 2 );
    data_copy( bufor, (char*)&receiver_id, 2 );
    data_copy( bufor, (char*)&msg_number, 2 );
    data_copy( bufor, (char*)&key_num, 1 );
    data_copy( bufor, (char*)&length, 2 );
    data_copy( bufor, text.c_str(), length );

    send_package(socket,bufor,size);
}

//pingujemy serwer
void protocol::packet_ping(read_write_socket* socket)
{
    unsigned int size;
    actual_pos = 0;     //zerujemy licznik
    unsigned char   msg_id = RAMKA_PING;
    size = 1;
    data_copy( bufor, (char*)&msg_id, 1 );

    send_package(socket,bufor,size);
}

//odpowiadamy na pinga (tak naprawdę to nie jest potrzebne, tylko dla zgodności)
void protocol::packet_ping_ack(read_write_socket* socket)
{
    unsigned int size;
    actual_pos = 0;     //zerujemy licznik
    unsigned char   msg_id = RAMKA_PING_ACK;
    size = 1;
    data_copy( bufor, (char*)&msg_id, 1 );

    send_package(socket,bufor,size);
}

//wysyłamy klientowi stan użytkownika
void protocol::packet_user_state(read_write_socket* socket, user_state* data)
{
    unsigned int size;
    actual_pos = 0;     //zerujemy licznik

    unsigned char   msg_id = RAMKA_USER_STATE;
    unsigned short  numer = data->numer;
    unsigned char   state = data->state;

    size = 4;

    data_copy( bufor, (char*)&msg_id, 1 );
    data_copy( bufor, (char*)&state, 1 );
    data_copy( bufor, (char*)&numer, 2 );

    send_package(socket,bufor,size);
}

//prośba o dodanie użytkownika do znajomych
void protocol::packet_user_add(read_write_socket* socket, unsigned short numer)
{
    unsigned int size;
    actual_pos = 0;     //zerujemy licznik

    unsigned char   msg_id = RAMKA_USER_ADD;
    size = 3;

    data_copy( bufor, (char*)&msg_id, 1 );
    data_copy( bufor, (char*)&numer, 2 );

    send_package(socket,bufor,size);
}

//informacja dla klienta o skasowaniu użytkownika
void protocol::packet_user_deleted(read_write_socket* socket, unsigned short numer)
{
    unsigned int size;
    actual_pos = 0;     //zerujemy licznik

    unsigned char   msg_id = RAMKA_USER_DELETED;
    size = 3;

    data_copy( bufor, (char*)&msg_id, 1 );
    data_copy( bufor, (char*)&numer, 2 );

    send_package(socket,bufor,size);
}

void protocol::packet_challenge_log_ack(read_write_socket* socket, challenge_log_ack* data)//???
{
    unsigned int size;
    actual_pos = 0;     //zerujemy licznik

    unsigned char   msg_id = RAMKA_CHALLENGE_LOG_ACK;
    unsigned char   length = data->login.length() + 1;  //wysyłamy \0
    std::string login = data->login.toStdString();
    size = 2 + length;
    if( size > bufor_size )
        resize_bufor( size );

    data_copy( bufor, (char*)&msg_id, 1 );
    data_copy( bufor, (char*)&length, 1 );
    data_copy( bufor, login.c_str(), length );
    send_package(socket,bufor,size);
}

void protocol::packet_challenge_reg(read_write_socket* socket, challenge_reg* data)//???
{
    unsigned int size;
    actual_pos = 0;     //zerujemy licznik

    unsigned char   msg_id = RAMKA_CHALLENGE_REG;
    int length = data->encoded_random_string.length() + 1;  //wysyłamy \0
    std::string encoded_random_string = data->encoded_random_string;
    size = 5 + length;
    if( size > bufor_size )
        resize_bufor( size );

    data_copy( bufor, (char*)&msg_id, 1 );
    data_copy( bufor, (char*)&length, 4 );
    data_copy( bufor, encoded_random_string.c_str(), length );
    std::cout<<endl <<"encoded_random_string: "<<encoded_random_string<<"  "<<encoded_random_string.size();  
    send_package(socket,bufor,size);
}

void protocol::send_package(read_write_socket* socket, char *bufor,unsigned int size)
{
    sendThread* ss = new sendThread(socket,bufor,size);
    ss->start();
}



