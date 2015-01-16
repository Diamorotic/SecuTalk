#include "user.hh"
#include <string>

using namespace std;

User::User(SOCKET &s,user_data userData)
{
    socket=s;
    //thandleSend=ths;
    //thandleReceive=thr;
    login=userData.login;
    numer=userData.numer;
    state=userData.state;
    key_num=userData.key_num;//klucz publiczny
}

User::User()
{

}

SOCKET User::getSocket()
{
    return socket;
}

MonitorQueue<queued_frame>* User::getSendFrameQueue()
{
    return &sendFrameQueue;
}

//void User::setNewFrameEvent()
//{
//    newFrame = CreateEvent(NULL,FALSE,FALSE,"newFrameUser");
//}
