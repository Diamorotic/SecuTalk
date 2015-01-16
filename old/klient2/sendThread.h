#ifndef SENDTHREAD_H
#define SENDTHREAD_H

#include "QThread"

#include "read_write_socket.h"

class read_write_socket;

class sendThread : public QThread
{
    Q_OBJECT
public:
    sendThread(read_write_socket* socket, char *bufor,unsigned int size);
public slots:
    void wrap_up();
signals:
    void msg_wrap_up();
protected:
    void run();
    bool execution;
    unsigned int size;
    char *bufor;
    read_write_socket* socket;

};

#endif // SENDTHREAD_H
