#ifndef READ_WRITE_SOCKET_H
#define READ_WRITE_SOCKET_H

#include <QAbstractSocket>
#include <QString>
#include "deklaracje.h"
#include "protocol.h"
#include "rejestracja.h"

class protocol;
class read_write_socket : public QAbstractSocket
{
    Q_OBJECT
public:
    read_write_socket( QObject* parent, struct_connect* params, char state);


    //QAbstractSocket socket;
    unsigned int    packet_size;        //wielkość aktualnie pobieranego pakietu
    unsigned char   packet_type;
    unsigned short  header_size;    //wielkość nagłówka
    void*           cur_packet;     //tutaj przyczepiamy strukturę pakietu
    char state;
    QString KeyFileName;
    protocol* Protocol;

    void connect_to();
    void set_password(QString password);
    QString random_string;
public slots:
    void send_text_message();//wysylanie
    void send_login();//wysylanie
    void send_challenge_reg(std::string encoded_random_string);//wysylanie
    void send_reg_data(std::string login);
    void msg_wrap_up();
private:

    QString password;
    struct_connect* IP_and_port;
    void ramka_message(char etap);//ramka - odbieranie
    void ramka_user_data(char etap);
    void ramka_user_data_login(char etap);
    void ramka_challenge_log_ack(char etap);
    void ramka_challenge_reg_ack(char etap);
signals:
    void msg_message(text_message*);
    void msg_user_data(user_data*);
    void msg_user_data_login(user_data*);
    void msg_challenge_log_ack(challenge_log_ack*);
    void msg_challenge_reg_ack(challenge_reg*);
private slots:
    void displayError(QAbstractSocket::SocketError);
    void time_to_read();
    void connection_established();
};

#endif // READ_WRITE_SOCKET_H
