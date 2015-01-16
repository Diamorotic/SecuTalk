extern MonitorQueue<queued_frame>* recFrameQueue;

class ReceiveThread : public ThreadBase
{
private:
    User* m_resource;
public:
    ReceiveThread(User* i_resource) :m_resource(i_resource) { }

    virtual void run()
    {
        ///watek odbierajacy///////////////////////////////////////////////////////////////
        User* threadUser = m_resource;
        SOCKET sock = threadUser->getSocket();
        Protocol *protocol=new Protocol();

        while(true)//COS ODBIERAM?
        {

            queued_frame receivedFrame=protocol->read_data(sock);//frame, bytesRecv+1,
            if(receivedFrame.packet_type == RAMKA_MESSAGE)
            {
                recFrameQueue->push(receivedFrame);
            }
        }
    }
};


