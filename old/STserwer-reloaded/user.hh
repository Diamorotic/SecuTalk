#include "monitorQueue.hpp"
#include "protocol.hh"

using namespace std;

class User : public user_data
{
private:
    SOCKET socket;
    MonitorQueue<queued_frame> sendFrameQueue;
public:
    User();
    User(SOCKET &s,user_data userData);
    SOCKET getSocket();
    MonitorQueue<queued_frame>* getSendFrameQueue();
};
