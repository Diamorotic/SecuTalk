#include <winsock2.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <time.h>
#include <string>
#include <queue>

//tryby wylogowania
#define SERVER_LOG_OUT  0x0     //dostalismy pakiet log_out  //////////nadpisane nad oryginalem
#define USER_LOG_OUT    0x1     //użytkownik wybrał wyloguj
#define SERVER_DISCONNECT   0x2     //serwer się rozłączył bez ramki
#define SERVER_ERROR    0x3                                   //////////nadpisane nad oryginalem

//tryb pracy klienta
#define NORMAL_LOG      0x1
#define DELETE_ACOUNT   0x2
#define CHANGE_KEY      0x3
#define BLOCK_ACOUNT    0x4
#define LOG_OUT         0x5//////////nadpisane nad oryginalem
#define INIT            0x6
#define ADMIN_LOG       0x7//////////nadpisane nad oryginalem

//stany użytkowników
#define ZALOGOWANY      0x1
#define WYLOGOWANY      0x2
#define ZABLOKOWANY     0x3
#define USUNIETY        0x4
#define NIE_ISTNIEJE    0x5
#define NIE_ZNANY       0x6             //przychodzi wiadomość od nieznajomego (tylko klient)

//funkcje odbierające
#define PACKET_ID       3
#define HEADER          0
//#define TEXT            1

//identyfiaktory ramek
#define RAMKA_PING              0x01
#define RAMKA_PING_ACK          0x02
#define RAMKA_USER_STATE        0x03
#define RAMKA_USER_ADD          0x04
#define RAMKA_FIND_USER         0x05
#define RAMKA_LOG_OUT           0x06
#define RAMKA_SEND_WAIT         0x07
#define RAMKA_SEND_CONTINUE     0x08
#define RAMKA_STOP_SEND         0x09
#define RAMKA_ACCEPT_FILE       0x0A
#define RAMKA_SEND_FILE         0x0B
#define RAMKA_SEND_DATA         0x0C
#define RAMKA_USER_DELETED      0x0D
#define RAMKA_MESSAGE_ACK       0x0E
#define RAMKA_MESSAGE           0x0F
#define RAMKA_USER_DATA         0x10
#define RAMKA_CHANGE_KEY        0x11
#define RAMKA_CHANGE_FAIL       0x12
#define RAMKA_CHANGE_CONFIRM    0x13
#define RAMKA_DELETE_USER       0x14
#define RAMKA_BLOCK_USER        0x15
#define RAMKA_CHALLENGE_REG     0x16
#define RAMKA_CHALLENGE_ACK     0x17
#define RAMKA_CHALLENGE_LOG     0x18
#define RAMKA_CHALLENGE_LOG_ACK 0x19
#define RAMKA_LOG_ME_IN         0x1A
#define RAMKA_LOG_CHANGE_KEY    0x1B
#define RAMKA_REG_DATA          0x1C
#define RAMKA_VERSION           0x1D
#define RAMKA_DISCONNECT        0x1E
#define RAMKA_USER_DATA_LOGIN   0x1F//nowe
#define RAMKA_CHALLENGE_REG_ACK  0x20

//logowanie
#define MAXLEN 1000//////////nadpisane nad oryginalem
#define MAX_USER_NUM 64//////////nadpisane nad oryginalem



//kopiuje zawartość jednego bufora do drugiego bajt po bajcie
//nie wstawia \0, wymaga podania poprawnej długości
void data_copy(char* dest, const char* src, int length);

struct queued_frame
{
    unsigned int    packet_size;        //wielkość aktualnie pobieranego pakietu
    unsigned char   packet_type;
    //unsigned short  header_size;    //wielkość nagłówka
    char*           cur_packet;     //tutaj przyczepiamy strukturę pakietu
};
//======================================================//
//      struktury odpowiadające wysyłanym ramkom        //
//======================================================//

struct user_state
{
    unsigned short  numer;
    unsigned char   state;
};

struct user_data
{
    std::string         login;
    std::string         haslo;
    unsigned short  numer;
    unsigned char   state;
    unsigned char   key_num;
    //klucz publiczny
};

struct text_message
{
    std::string text;
    unsigned short  sender_id;///numer
    unsigned short  receiver_id;///numer
    unsigned short  msg_number;
    unsigned char   key_num;
    //zaszyfrowany klucz sesyjny
};

struct message_ack                                          //////////nadpisane nad oryginalem
{
    unsigned short  sender_id;
    unsigned short  msg_number;
};

struct handle_number_map
{
    HANDLE  thandle;
    unsigned short   number;
    SOCKET socket;
};

struct challenge_log_ack
{
    std::string login;
};

struct challenge_reg
{
    std::string encoded_random_string;
};
