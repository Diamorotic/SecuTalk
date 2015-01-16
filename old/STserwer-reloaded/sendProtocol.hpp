#include "threadBase.hpp"


class SendProtocol : public ThreadBase
{
private:
    bool execution;
    unsigned int size;
    char *bufor;
    const SOCKET* socket;

public:
    SendProtocol(const SOCKET &socket , char *bufor,unsigned int size)
    {
        execution=false;
        this->size=size;
        this->socket=&socket;
        this->bufor=bufor;
    }

    virtual void run()
    {
        unsigned int sent_bytes=0;
        while(sent_bytes<size)
        {
            sent_bytes=send( *socket, (bufor+sent_bytes), size - sent_bytes, 0 )+sent_bytes;
        }
        if(sent_bytes!=size)
        {
            ///blad transmisji
        }
        execution=true;
    }

};
