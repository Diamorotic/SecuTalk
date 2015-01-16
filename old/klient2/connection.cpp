#include "connection.h"
#include "ui_connection.h"
#include <QString>

connection::connection(QWidget *parent, struct_connect* conn) :
    QDialog(parent),
    ui(new Ui::connection)
{
    ui->setupUi(this);
    con = conn;

    QDialogButtonBox* buttonBox = this->findChild<QDialogButtonBox*>("buttonBox");
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(connect_data_accept()) );

    QLineEdit* textField =  this->findChild<QLineEdit*>("IP_addr");
    textField->setText(conn->adres);

    /*textField =  this->findChild<QLineEdit*>("IP2");
    textFiled->setText(tekst.setNum(conn->IP_part2));

    textField =  this->findChild<QLineEdit*>("IP3");
    textFiled->setText(tekst.setNum(conn->IP_part3));

    textField =  this->findChild<QLineEdit*>("IP4");
    textField->setText(tekst.setNum(conn->IP_part4));*/

    QString tekst;
    textField =  this->findChild<QLineEdit*>("klientPort");
    textField->setText(tekst.setNum(conn->port_klienta));

    textField =  this->findChild<QLineEdit*>("serwerPort");
    textField->setText(tekst.setNum(conn->port_serwera));
}

connection::~connection()
{
    delete ui;
}


void connection::connect_data_accept()
{//użytkownik kliknął OK w oknie dialogowym wyboru danych połączenia
    //przepisujemy wpisane przez użytkownika wartości do struktury
    QLineEdit* textFiled =  this->findChild<QLineEdit*>("IP_addr");
    con->adres = textFiled->text();

    /*textFiled =  this->findChild<QLineEdit*>("IP2");
    tekst = textFiled->text();
    con->IP_part1 = (char)tekst.toUShort();

    textFiled =  this->findChild<QLineEdit*>("IP3");
    tekst = textFiled->text();
    con->IP_part1 = (char)tekst.toUShort();

    textFiled =  this->findChild<QLineEdit*>("IP4");
    tekst = textFiled->text();
    con->IP_part1 = (char)tekst.toUShort();*/

    QString tekst;
    textFiled =  this->findChild<QLineEdit*>("klientPort");
    tekst = textFiled->text();
    con->port_klienta = tekst.toUShort();

    textFiled =  this->findChild<QLineEdit*>("serwerPort");
    tekst = textFiled->text();
    con->port_serwera = tekst.toUShort();
}
