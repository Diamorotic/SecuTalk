#include "watcher.h"
#include <QTimer>
#include <windows.h>

class read_write_socket;

watcher::watcher(read_write_socket* socket, char *bufor,unsigned int size)
{
    execution=false;
    this->size=size;
    this->socket=socket;
    this->bufor=bufor;
}

void watcher::run()
{
    //exec();
    QThread* somethread = new QThread(this);
    QTimer* timer = new QTimer(0); //parent must be null
    timer->setInterval(1);
    timer->moveToThread(somethread);
    QObject::connect(timer, SIGNAL(timeout()), somethread, SLOT(watcher::wrap_up()));
    //connect what you want
    somethread->start();
    Sleep(5000);
}

void watcher::wrap_up()
{
    emit msg_wrap_up(execution);
    int a;
}
