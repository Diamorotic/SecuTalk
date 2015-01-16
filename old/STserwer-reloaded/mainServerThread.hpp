#include "connectThread.hpp"



using namespace std;


extern MonitorList<User*>* userArray;
extern MonitorQueue<queued_frame>* recFrameQueue;
extern void createKeys();
extern void encrypt();
extern void decrypt();
class MainServerThread : public ThreadBase
{
private:
public:
    MainServerThread() { }
    virtual void run()
    {
        ///watek glowny serwera//////////////////////////////////////////////////////////
        ConnectThread connectThread;
        connectThread.start();

        while(true)
        {
            while(true)
            {
                queued_frame queuedFrame=recFrameQueue->popWait();
                Protocol *protocol = new Protocol();
                switch(queuedFrame.packet_type)          ///tutaj mala obrobka pakietu
                {
                case 0x0F:///#define RAMKA_MESSAGE           0x0F

                    int receiver_id = protocol->get_number(queuedFrame);
                    list<User*>::iterator tempIterator=userArray->begin();
                    while(tempIterator!=userArray->end())
                    {
                        if((*tempIterator)->numer==receiver_id)
                        {
                            (*tempIterator)->getSendFrameQueue()->push(queuedFrame);
                            break;
                        }
                        tempIterator++;
                    }

                    break;
                }
            }

        }
        connectThread.join();
    }
};
