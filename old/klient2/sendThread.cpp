#include "sendThread.h"
#include <QTimer>

class read_write_socket;
sendThread::sendThread(read_write_socket* socket, char *bufor,unsigned int size)
{
    execution=false;
    this->size=size;
    this->socket=socket;
    this->bufor=bufor;
    connect(this, SIGNAL(msg_wrap_up()),socket, SLOT(msg_wrap_up()));
}

void sendThread::run()
{
    QTimer::singleShot(500, this, SLOT(wrap_up()));
    unsigned int sent_bytes=0;
    while(sent_bytes<size)
    {
        sent_bytes=socket->write((bufor+sent_bytes),size - sent_bytes)+sent_bytes;
    }
    terminate();//potrzebne?
}



void sendThread::wrap_up()
{
    emit msg_wrap_up();
}
