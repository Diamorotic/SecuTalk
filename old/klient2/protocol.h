#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "deklaracje.h"
#include "read_write_socket.h"
#include "sendThread.h"

//=============================================//
//                  protocol                   //
//=============================================//


//UWAGA!!
//Pojedynczy obiekt danej klasy może być używany tylko w jednym wątku.
//Po kolejnym wywołaniu funkcji tworzącej pakiet, poprzedni pakiet zostaje
//nadpisany. NIE wolno zwalniać pamieci po pakietach!
class read_write_socket;
class sendThread;

class protocol
{
    //Q_OBJECT
private:
    char*   bufor;
    unsigned int bufor_size;
    unsigned int actual_pos;    //licznik, który musi byc wyzerowany przed wypełnianiem
                                //każdej nowej ramki

    void resize_bufor( unsigned int new_size );
    void data_copy(char* dest, const char* src, int length);
    void send_package(read_write_socket* socket, char *bufor,unsigned int size);
    //void wrap_up(sendThread* st);
public:
    protocol();
    ~protocol();
    //w polu size umieszczana jest długość pakietu
    void   packet_user_data(read_write_socket* socket, user_data*);
    void   packet_message(read_write_socket* socket, text_message* data);
    void   packet_ping(read_write_socket* socket);
    void   packet_ping_ack(read_write_socket* socket);
    void   packet_user_state(read_write_socket* socket, user_state* data);
    void   packet_user_add(read_write_socket* socket, unsigned short numer);
    void   packet_user_deleted(read_write_socket* socket, unsigned short numer );
    //char*   packet_log_me_in( unsigned short numer, unsigned int* size ); lolololo
    void   packet_challenge_log_ack(read_write_socket* socket, challenge_log_ack* data );
    void   packet_challenge_reg(read_write_socket* rws,  challenge_reg* data );
};

#endif // PROTOCOL_H
