#include "deklaracje.hh"
//#include "sendProtocol.hpp"
using namespace std;

//=============================================//
//                  Protocol                   //
//=============================================//


//UWAGA!!
//Pojedynczy obiekt danej klasy mo¿e byæ u¿ywany tylko w jednym w¹tku.
//Po kolejnym wywo³aniu funkcji tworz¹cej pakiet, poprzedni pakiet zostaje
//nadpisany. NIE wolno zwalniaæ pamieci po pakietach!

class Protocol
{
private:
    char*   bufor;
    unsigned int bufor_size;
    //licznik, który musi byc wyzerowany przed wype³nianiem
    void    data_copy(char* dest, const char* src, int length);                               //ka¿dej nowej ramki
    void resize_bufor( unsigned int new_size );

public:

    Protocol();
    ~Protocol();
    unsigned int actual_pos; //////////nadpisane nad oryginalem - zminione z priv na pub

    //w polu size umieszczana jest d³ugoœæ pakietu
    void    packet_user_data( user_data*, const SOCKET &sock ) ;
    void    packet_user_data_login( user_data*, const SOCKET &sock  );
    void    packet_message( text_message* data, const SOCKET &sock  );
    void    packet_ping( const SOCKET &sock  );
    void    packet_ping_ack( const SOCKET &sock  );
    void    packet_user_state( user_state* data, const SOCKET &sock );
    void    packet_user_add( unsigned short numer, const SOCKET &sock  );
    void    packet_user_deleted( unsigned short numer, const SOCKET &sock  );
    void    packet_challenge_log_ack(challenge_log_ack* data, const SOCKET &sock  );
    void    packet_challenge_reg( challenge_reg* data, const SOCKET &sock  );
    void    packet_challenge_reg_ack( challenge_reg* data, const SOCKET &sock );
    void    send_package(char *bufor,unsigned int size, const SOCKET &sock );
    user_data   get_user_data(queued_frame queuedFrame);
    challenge_reg   get_challenge_reg(queued_frame queuedFrame);
    int     get_number(queued_frame queuedFrame);
    queued_frame    read_data(const SOCKET &sock);

};
