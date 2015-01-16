#include "connection.hh"
#include "user.hh"
#include "monitorList.hpp"
#include "sendProtocol.hpp"

class SendThread : public ThreadBase
{
private:

    User* m_resource;
public:
    SendThread(User* i_resource) : m_resource(i_resource) { }

    virtual void run()
    {
        ///watek wysylajacy//////////////////////////////////////////////////////////////
        User* threadUser = m_resource;
        SOCKET sock = threadUser->getSocket();
        Protocol *protocol=new Protocol();

        while(true)
        {
            queued_frame queuedFrame=threadUser->getSendFrameQueue()->popWait();
            //connection->send_text_message(queuedFrame.cur_packet,queuedFrame.packet_size,sock);
            protocol->send_package(queuedFrame.cur_packet,queuedFrame.packet_size,sock);
        }

    }

};
