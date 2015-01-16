
#ifndef WATCHER_H
#define WATCHER_H

#include "QThread"
#include "read_write_socket.h"

class read_write_socket;

class watcher : public QThread
{
    Q_OBJECT
public:
    watcher(read_write_socket* socket, char *bufor,unsigned int size);
public slots:
    void wrap_up();
signals:
    void msg_wrap_up(bool);
protected:
    void run();
    bool execution;
    unsigned int size;
    char *bufor;
    read_write_socket* socket;
    QTimer* timer;
};

#endif // WATCHER_H
