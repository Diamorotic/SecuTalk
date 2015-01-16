#include <string>
//#include "threadBase.hpp"

class ReadConnection : public ThreadBase
{
public:
    bool execution;
    unsigned int size;
    char *bufor;
    const SOCKET* socket;
    unsigned char   packet_type;
public:
    ReadConnection(const SOCKET &socket)
    {
        execution=false;
        this->socket=&socket;
    }
    virtual void run()
    {
        char recvbuf[ MAXLEN];
        int bytesRecv=0;
        int prevBytesRecv=0;
        size=1;

        while(bytesRecv < size)
        {
            bytesRecv = recv( (*socket), (recvbuf+prevBytesRecv), sizeof(recvbuf) - 1 - prevBytesRecv, 0 );

            if (bytesRecv == -1)
            {
                perror("blad odczytu");
                exit(1);
            }
            if(size==1)
            {
                switch(recvbuf[0])///if
                {
                case 0x10:///#define RAMKA_USER_DATA         0x10
                    //cout <<"ramka?"<<std::hex<<(int)bufor[0]<<endl;
                    packet_type=0x10;
                    if (bytesRecv < 6)
                    {
                        prevBytesRecv=prevBytesRecv+bytesRecv;
                        continue;
                    }
                    else
                    {
                        unsigned char   length;
                        memcpy((char*)&length,(recvbuf+5), 1);
                        size = (int)length+6;
                        bufor=(char*)malloc(size);

                    }
                    break;
                case 0x0F:///#define RAMKA_MESSAGE           0x0F
                    packet_type=0x0F;

                    if (bytesRecv < 10)
                    {
                        prevBytesRecv=prevBytesRecv+bytesRecv;
                        continue;
                    }
                    else
                    {
                        unsigned short   length;
                        memcpy((char*)&length,(recvbuf+8), 2);
                        size = (int)length+10;
                        bufor=(char*)malloc(size);
                    }
;
                    break;
                case 0x16:///#define RAMKA_CHALLENGE_REG     0x16
                    packet_type=0x16;
                    if (bytesRecv < 5)
                    {
                        prevBytesRecv=prevBytesRecv+bytesRecv;
                        continue;
                    }
                    else
                    {
                        unsigned int length;
                        memcpy((char*)&length,(recvbuf+1), 4);
                        size = (int)length+5;
                        bufor=(char*)malloc(size);
                    }
                    break;
                }
            }

            prevBytesRecv=prevBytesRecv+bytesRecv;

            if(prevBytesRecv==size)/// /////////////////////payload
            {
                switch(recvbuf[0])///if
                {
                case 0x10:///#define RAMKA_USER_DATA         0x10

                    //msg_id
                    memcpy(bufor, recvbuf , 1);
                    //user_id
                    memcpy((bufor+1),(recvbuf+1), 2);

                    //state
                    memcpy((bufor+3),(recvbuf+3), 1);

                    //key_num
                    memcpy((bufor+4),(recvbuf+4), 1);

                    //length
                    memcpy((bufor+5),(recvbuf+5), 1);
                    //login
                    memcpy((bufor+6),(recvbuf+6), size-6);

                    bufor[prevBytesRecv+1] = '\0';///mozliwy blad

                    break;

                case 0x0F:///#define RAMKA_MESSAGE           0x0F

                    //msg_id
                    memcpy(bufor, recvbuf , 1);
                    //sender_id
                    memcpy((bufor+1),(recvbuf+1), 2);

                    //receiver_id
                    memcpy((bufor+3),(recvbuf+3), 2);

                    //msg_number
                    memcpy((bufor+5),(recvbuf+5), 2);

                    //key_num
                    memcpy((bufor+7),(recvbuf+7), 1);

                    //length
                    memcpy((bufor+8),(recvbuf+8), 2);

                    //text
                    memcpy((bufor+10),(recvbuf+10), size-10);

                    bufor[prevBytesRecv+1] = '\0';

                    break;

                case 0x16:///#define RAMKA_CHALLENGE_REG     0x16


                    //msg_id
                    memcpy(bufor, recvbuf , 1);
                    //length
                    memcpy((bufor+1),(recvbuf+1), 4);
                    //encoded random string
                    memcpy((bufor+5),(recvbuf+5), (size)-5);

                    bufor[prevBytesRecv+1] = '\0';///mozliwy blad

                    break;
                }
            }

        }

        cout <<endl<<"ram user data: "<<std::string(bufor)<<endl;
    }

};
