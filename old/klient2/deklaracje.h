#ifndef DEKLARACJE_H
#define DEKLARACJE_H

#include <QString>


#define NORMAL_LOG      0x1
#define DELETE_ACOUNT   0x2
#define CHANGE_KEY      0x3
#define BLOCK_ACOUNT    0x4

#define ZALOGOWANY      0x1
#define WYLOGOWANY      0x2
#define ZABLOKOWANY     0x3
#define USUNIETY        0x4
#define NIE_ISTNIEJE    0x5
#define NIE_ZNANY       0x6             //przychodzi wiadomość od nieznajomego (tylko klient)

//funkcje odbierające
#define PACKET_ID       3
#define HEADER          0
#define TEXT            1
#define TEXTT            1

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
#define RAMAK_BLOCK_USER        0x15
#define RAMKA_CHALLENGE_REG     0x16
#define RAMKA_CHALLENGE_ACK     0x17
#define RAMKA_CHALLENGE_LOG     0x18
#define RAMKA_CHALLENGE_LOG_ACK 0x19
#define RAMKA_LOG_ME_IN         0x1A
#define RAMKA_LOG_CHANGE_KEY    0x1B
#define RAMKA_REG_DATA          0x1C
#define RAMKA_VERSION           0x1D
#define RAMKA_DISCONNECT        0x1E
#define RAMKA_USER_DATA_LOGIN   0x1F
#define RAMKA_CHALLENGE_REG_ACK  0x20

//kopiuje zawartość jednego bufora do drugiego bajt po bajcie
//nie wstawia \0, wymaga podania poprawnej długości
void data_copy(char* dest, const char* src, int length);


struct struct_connect
{
    unsigned short int port_serwera;
    unsigned short int port_klienta;
    QString adres;
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
    QString         login;
    QString         haslo;
    unsigned short  numer;
    unsigned char   state;
    unsigned char   key_num;
    //klucz publiczny
};

struct text_message
{
    QString text;
    unsigned short  sender_id;
    unsigned short  receiver_id;
    unsigned short  msg_number;
    unsigned char   key_num;
    //zaszyfrowany klucz sesyjny
};
struct challenge_log_ack
{
    QString login;
};

struct challenge_reg
{
    std::string encoded_random_string;
};

#endif // DEKLARACJE_H
