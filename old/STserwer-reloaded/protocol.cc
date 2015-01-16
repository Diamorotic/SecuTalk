#include "protocol.hh"
#include <string>
#include "sendProtocol.hpp"
#include "readConnection.hpp"

using namespace std;
//=====================================================//

void Protocol::data_copy(char* dest, const char* src, int length)
{

    for( int i=0; i<length; ++i)
        dest[i+actual_pos] = src[i];
    actual_pos += length;
}

//=====================================================//

Protocol::Protocol()
{
    bufor = new char[1024];
    bufor_size = 1024;
    actual_pos = 0;
}

Protocol::~Protocol()
{
    delete bufor;
}


void Protocol::resize_bufor( unsigned int new_size )
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
void Protocol::packet_user_data( user_data* data,const SOCKET &sock  )
{
    unsigned int size;
    actual_pos = 0;     //zerujemy licznik

    unsigned char   msg_id = RAMKA_USER_DATA;
    unsigned short  user_id = data->numer;
    unsigned char   state = data->state;
    unsigned char   key_num = data->key_num;
    unsigned char   length = data->login.length() + 1;  //wysyłamy \0
    std::string login = data->login;

    size = 6 + length;
    if( size > bufor_size )
        resize_bufor( size );

    data_copy( bufor, (char*)&msg_id, 1 );
    data_copy( bufor, (char*)&user_id, 2 );
    data_copy( bufor, (char*)&state, 1 );
    data_copy( bufor, (char*)&key_num, 1 );
    data_copy( bufor, (char*)&length, 1 );
    data_copy( bufor, login.c_str(), length );

    send_package(bufor, size,sock);
}

void Protocol::packet_user_data_login( user_data* data,const SOCKET &sock  )
{
    unsigned int size;
    actual_pos = 0;     //zerujemy licznik

    unsigned char   msg_id = RAMKA_USER_DATA_LOGIN;
    unsigned short  user_id = data->numer;
    unsigned char   state = data->state;
    unsigned char   key_num = data->key_num;
    unsigned char   length = data->login.length() + 1;  //wysyłamy \0
    std::string login = data->login;

    size = 6 + length;
    if( size > bufor_size )
        resize_bufor( size );

    data_copy( bufor, (char*)&msg_id, 1 );
    data_copy( bufor, (char*)&user_id, 2 );
    data_copy( bufor, (char*)&state, 1 );
    data_copy( bufor, (char*)&key_num, 1 );
    data_copy( bufor, (char*)&length, 1 );
    data_copy( bufor, login.c_str(), length );

    send_package(bufor, size,sock);
}

//wysyłamy wiadomośc tekstową
void Protocol::packet_message( text_message* data,const SOCKET &sock  )
{
    unsigned int size;
    actual_pos = 0;     //zerujemy licznik

    unsigned char   msg_id = RAMKA_MESSAGE;
    unsigned short  sender_id = data->sender_id;
    unsigned short  receiver_id = data->receiver_id;
    unsigned short  msg_number = data->msg_number;
    unsigned char   key_num = data->key_num;
    unsigned short  length = data->text.length() + 1;  //wysyłamy \0
    std::string text = data->text;

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

    send_package(bufor, size,sock);
}

//pingujemy serwer
void Protocol::packet_ping( const SOCKET &sock  )
{
    unsigned int size;
    actual_pos = 0;     //zerujemy licznik
    unsigned char   msg_id = RAMKA_PING;
    size = 1;
    data_copy( bufor, (char*)&msg_id, 1 );

    send_package(bufor, size,sock);
}

//odpowiadamy na pinga (tak naprawdę to nie jest potrzebne, tylko dla zgodności)
void Protocol::packet_ping_ack( const SOCKET &sock  )
{
    unsigned int size;
    actual_pos = 0;     //zerujemy licznik
    unsigned char   msg_id = RAMKA_PING_ACK;
    size = 1;
    data_copy( bufor, (char*)&msg_id, 1 );

    send_package(bufor, size,sock);
}

//wysyłamy klientowi stan użytkownika
void Protocol::packet_user_state( user_state* data,const SOCKET &sock  )
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

    send_package(bufor, size,sock);
}

//prośba o dodanie użytkownika do znajomych
void Protocol::packet_user_add( unsigned short numer,const SOCKET &sock  )
{
    unsigned int size;
    actual_pos = 0;     //zerujemy licznik

    unsigned char   msg_id = RAMKA_USER_ADD;
    size = 3;

    data_copy( bufor, (char*)&msg_id, 1 );
    data_copy( bufor, (char*)&numer, 2 );

    send_package(bufor, size,sock);
}

//informacja dla klienta o skasowaniu użytkownika
void Protocol::packet_user_deleted( unsigned short numer,const SOCKET &sock  )
{
    unsigned int size;
    actual_pos = 0;     //zerujemy licznik

    unsigned char   msg_id = RAMKA_USER_DELETED;
    size = 3;

    data_copy( bufor, (char*)&msg_id, 1 );
    data_copy( bufor, (char*)&numer, 2 );

    send_package(bufor, size,sock);
}


//rejestracja /logowanie uzytkownika
void Protocol::packet_challenge_log_ack( challenge_log_ack* data,const SOCKET &sock  )//???
{
    unsigned int size;
    actual_pos = 0;     //zerujemy licznik

    unsigned char   msg_id = RAMKA_CHALLENGE_LOG_ACK;
    unsigned char   length = data->login.length() + 1;  //wysyłamy \0
    std::string login = data->login;

    size = 2 + length;
    if( size > bufor_size )
        resize_bufor( size );

    data_copy( bufor, (char*)&msg_id, 1 );
    data_copy( bufor, (char*)&length, 1 );
    data_copy( bufor, login.c_str(), length );
    send_package(bufor, size,sock);
}

void Protocol::packet_challenge_reg( challenge_reg* data,const SOCKET &sock  )//???
{
    unsigned int size;
    actual_pos = 0;     //zerujemy licznik

    unsigned char   msg_id = RAMKA_CHALLENGE_REG;
    int   length = data->encoded_random_string.length() + 1;  //wysyłamy \0
    std::string encoded_random_string = data->encoded_random_string;
    size = 5 + length;
    if( size > bufor_size )
        resize_bufor( size );

    data_copy( bufor, (char*)&msg_id, 1 );
    length=htonl(length);
    data_copy( bufor, (char*)&length, 4 );
    data_copy( bufor, encoded_random_string.c_str(), length );
    send_package(bufor, size,sock);
}

void Protocol::packet_challenge_reg_ack( challenge_reg* data,const SOCKET &sock  )//???
{
    unsigned int size;
    actual_pos = 0;     //zerujemy licznik

    unsigned char   msg_id = RAMKA_CHALLENGE_REG_ACK;
    unsigned short   length = data->encoded_random_string.length() + 1;  //wysyłamy \0
    std::string encoded_random_string = data->encoded_random_string;
    size = 3 + length;
    if( size > bufor_size )
        resize_bufor( size );

    data_copy( bufor, (char*)&msg_id, 1 );
    data_copy( bufor, (char*)&length, 2 );
    data_copy( bufor, encoded_random_string.c_str(), length );
    //CreateThread( NULL, 0,authorization, &acceptSocket, 0, NULL);
    send_package(bufor, size,sock);
    //return bufor;
}

void Protocol::send_package(char *bufor,unsigned int size, const SOCKET &sock  )
{
    SendProtocol sendProtocol(sock,bufor,size);
    sendProtocol.start();
    sendProtocol.join();///jakims cudem zdetachowac - zrobic
}

user_data Protocol::get_user_data(queued_frame queuedFrame)
{
    if(queuedFrame.packet_type!=RAMKA_USER_DATA)
        return user_data();

    user_data* user=new user_data();//(short unsigned int)

    unsigned short  user_id;
    memcpy((char*)&user_id,(queuedFrame.cur_packet+1), 2);
    user->numer=user_id;
    unsigned char   state;
    memcpy((char*)&state,(queuedFrame.cur_packet+3), 1);
    user->state=state;
    unsigned char   key_num;
    memcpy((char*)&key_num,(queuedFrame.cur_packet+4), 1);
    user->key_num=key_num;

    std::string login=string ((queuedFrame.cur_packet+6), queuedFrame.packet_size-6);
    user->login=login;
    return *user;
}

challenge_reg Protocol::get_challenge_reg(queued_frame queuedFrame)
{
    if(queuedFrame.packet_type!=RAMKA_CHALLENGE_REG)
        return challenge_reg();
    challenge_reg* reg = new challenge_reg();

    std::string encoded_random_string=string ((queuedFrame.cur_packet+5), queuedFrame.packet_size-6);
    reg->encoded_random_string=encoded_random_string;
    return *reg;
}
int Protocol::get_number(queued_frame queuedFrame)
{
    if(queuedFrame.packet_type!=RAMKA_MESSAGE)
        return 0;
    unsigned short  receiver_id;
    memcpy((char*)&receiver_id,(queuedFrame.cur_packet+3), 2);//POBRANIE NUMERU
    return receiver_id;
}

queued_frame Protocol::read_data(const SOCKET &sock)///tutaj read
{
    queued_frame qf;
    ReadConnection readConnection(sock);
    readConnection.start();
    if( readConnection.join_for())
    {
        qf.packet_type=0x00;
        return qf;
    }

    readConnection.join();///jakims cudem zdetachowac - zrobic

    qf.packet_size=readConnection.size;
    qf.cur_packet=readConnection.bufor;
    qf.packet_type=qf.cur_packet[0];
    return qf;
}
