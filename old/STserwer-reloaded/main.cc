#include "mainServerThread.hpp"

using namespace std;

MonitorQueue<queued_frame>* recFrameQueue;
MonitorList<User*>* userArray;

///Monitor monitor; - blad zle inicjuje
int main()
{
    createKeys();
    MonitorQueue<queued_frame> recFrameQueue2;
    MonitorList<User*> userArray2;
    recFrameQueue=&recFrameQueue2;
    userArray=&userArray2;
    //char what;
    //cout << "Co uruchomic? Wpisz S jak serwer, albo C jak klient";
    // while (what != 'S' && what != 'C')
    //     cin >> what;
    MainServerThread mainServerThread;
    mainServerThread.start();
    mainServerThread.join();
    //(what == 'S')
    //{
    //cin >> what;
    //}

}
