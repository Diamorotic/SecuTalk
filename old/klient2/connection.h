#ifndef CONNECTION_H
#define CONNECTION_H

#include <QDialog>
#include "deklaracje.h"

namespace Ui {
class connection;
}

class connection : public QDialog
{
    Q_OBJECT

public:
    explicit connection(QWidget *parent, struct_connect*);
    ~connection();

public slots:
    void connect_data_accept();

private:
    Ui::connection *ui;
    struct_connect* con;
};

#endif // CONNECTION_H
