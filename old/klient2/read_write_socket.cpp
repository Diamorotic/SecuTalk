#include "read_write_socket.h"
#include <QHostAddress>
#include <QMessageBox>
#include <mainwindow.h>
#include <QObject>
#include <iostream>
#include "security.h"
//#include <Winsock2.h>


read_write_socket::read_write_socket(QObject *parent, struct_connect* params,char state) : QAbstractSocket(QAbstractSocket::TcpSocket, parent)
{
    this->state=state;
    IP_and_port = params;
    packet_size = 0;
    header_size = 0;
    connect(this, SIGNAL(error(QAbstractSocket::SocketError)), this,
    SLOT(displayError(QAbstractSocket::SocketError)));
    connect(this, SIGNAL(readyRead()),this,SLOT(time_to_read()));
    connect(this, SIGNAL(connected()),this,SLOT(connection_established()));

    Protocol = new protocol;

}
void read_write_socket::connection_established()
{
    //Rejestracja* r=(((MainWindow*)parent())->findChild<Rejestracja*>("Rejestracja"));
    //r->close();
    if(state=='r')
    {
        this->random_string=get_random_string();
        std::string encoded_random_string=encrypt(this->KeyFileName,this->random_string);

        if(encoded_random_string.empty()) return;
        ((MainWindow*)parent())->challenge_registration(encoded_random_string);
    }
}
void read_write_socket::set_password(QString password)
{
    this->password=password;
}

void read_write_socket::connect_to()
{
    connectToHost( QHostAddress( IP_and_port->adres), IP_and_port->port_serwera );

}


void read_write_socket::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError)
    {
        case QAbstractSocket::HostNotFoundError:
            break;
        default:
            break;
    }

}


void read_write_socket::time_to_read()
{
    while(true)
    {//pętle przerywamy breakiem, kiedy nei będziemy mogli dalej pobierać

        if( packet_size == 0)
        {//wszystkie poprzednie pakiety zostały pobrane w całości
            int read = readData((char*)&packet_type,1);
            if( read == 0 ) break;      //nie wierze w to, ale jednak się dzieje

            if( packet_type == RAMKA_MESSAGE )   //ramka: message
                ramka_message( PACKET_ID );
            else if( packet_type == RAMKA_USER_DATA )//ramka: user_data
                ramka_user_data( PACKET_ID );
            else if(packet_type == RAMKA_CHALLENGE_LOG_ACK)
                ramka_challenge_log_ack( PACKET_ID );
            else if(packet_type == RAMKA_USER_DATA_LOGIN)///   /////RAMKA_CHALLENGE_REG_ACK
                ramka_user_data_login( PACKET_ID );
            else if(packet_type == RAMKA_CHALLENGE_REG_ACK)
                ramka_challenge_reg_ack( PACKET_ID );
        }

        if( bytesAvailable() < header_size )
            break;
        if( header_size != 0 )//jeżeli jest równy 0, to znaczy ze nagłówek już pobraliśmy
        {//uzupełniamy strukturę danymi z nagłówka
            if( packet_type == RAMKA_MESSAGE )
                ramka_message( HEADER );
            else if( packet_type == RAMKA_USER_DATA )
                ramka_user_data( HEADER );
            else if(packet_type == RAMKA_CHALLENGE_LOG_ACK)
                ramka_challenge_log_ack( HEADER );
            else if(packet_type == RAMKA_USER_DATA_LOGIN)
                ramka_user_data_login( HEADER );
            else if(packet_type == RAMKA_CHALLENGE_REG_ACK)
                ramka_challenge_reg_ack( HEADER );
            header_size = 0;        //pobraliśmy nagłówek, ustawiamy 0 żeby w następnym obiegu nie pobierać
        }

        if( bytesAvailable() >= packet_size )
        {//teraz odbieramy dane faktyczne (po nagłówku)
            if( packet_type == RAMKA_MESSAGE )
                ramka_message( TEXTT );
            else if( packet_type == RAMKA_USER_DATA )
                ramka_user_data( TEXTT );
            else if(packet_type == RAMKA_CHALLENGE_LOG_ACK)
                ramka_challenge_log_ack( TEXTT );
            else if(packet_type == RAMKA_USER_DATA_LOGIN)
                ramka_user_data_login( TEXTT );
            else if(packet_type == RAMKA_CHALLENGE_REG_ACK)
                ramka_challenge_reg_ack( TEXTT );
            packet_size = 0;    //przeczytaliśmy wszystko

            if( bytesAvailable() == 0 )
                break;      //nie ma nic do czytania, przerywamy pętlę
            //jeżeli jest coś od przeczytania to idziemy dalej
            continue;
        }
        break;
    }

}


void read_write_socket::ramka_message( char etap)
{
    if( etap == PACKET_ID )
    {
        header_size = 6;
        packet_size = 6;    //ustawiamy długość nagłówka i pakietu narazie na tyle samo
        cur_packet = (void*) new text_message;
    }
    else if( etap == HEADER )
    {
        char bufor[9];        //nagłówek
        unsigned short  sender_id;
        unsigned short  receiver_id;
        unsigned short  msg_number;
        unsigned char   key_num;
        unsigned short  length;
        //wczytujemy z sieci//
        readData(bufor,9);

        data_copy( (char*)&sender_id, bufor, 2 );
        data_copy( (char*)&receiver_id, bufor+2, 2 );
        data_copy( (char*)&msg_number, bufor+4, 2 );
        data_copy( (char*)&key_num, bufor+6, 1 );
        data_copy( (char*)&length, bufor+7, 2 );

        ((text_message*)cur_packet)->sender_id = sender_id;
        ((text_message*)cur_packet)->receiver_id = receiver_id;
        ((text_message*)cur_packet)->msg_number = msg_number;
        ((text_message*)cur_packet)->key_num = key_num;
        packet_size = length;
    }
    else if( etap == TEXTT )
    {
        char data[packet_size];
        readData(data,packet_size);
        ((text_message*)cur_packet)->text = QString(data);
        emit msg_message((text_message*)cur_packet);
    }
}


void read_write_socket::ramka_user_data(char etap)
{
    if( etap == PACKET_ID )
    {
        header_size = 5;
        packet_size = 5;    //ustawiamy długość nagłówka i pakietu narazie na tyle samo
        cur_packet = (void*) new user_data;
    }
    else if( etap == HEADER )
    {
        char receive[5];        //nagłówek
        quint8 size;
        readData(receive,5);

        quint16 num;
        data_copy((char*)&num, receive, 2);
        ((user_data*)cur_packet)->numer = num;

        ((user_data*)cur_packet)->state = *(receive+2);
        ((user_data*)cur_packet)->key_num = *(receive+3);
        size = *(receive+4);

        packet_size = size;
    }
    else if( etap == TEXTT )
    {
        char data[packet_size];
        int read = readData(data,packet_size);
        ((user_data*)cur_packet)->login = QString(data);
        emit msg_user_data((user_data*)cur_packet);
    }
}

void read_write_socket::ramka_user_data_login(char etap)
{
    if( etap == PACKET_ID )
    {
        header_size = 5;
        packet_size = 5;    //ustawiamy długość nagłówka i pakietu narazie na tyle samo
        cur_packet = (void*) new user_data;
    }
    else if( etap == HEADER )
    {
        char receive[5];        //nagłówek
        quint8 size;
        readData(receive,5);

        quint16 num;
        data_copy((char*)&num, receive, 2);

        ((user_data*)cur_packet)->numer = num;

        ((user_data*)cur_packet)->state = *(receive+2);
        ((user_data*)cur_packet)->key_num = *(receive+3);
        size = *(receive+4);

        packet_size = size;
    }
    else if( etap == TEXTT )
    {
        char data[packet_size];
        int read = readData(data,packet_size);
        ((user_data*)cur_packet)->login = QString(data);
        emit msg_user_data_login((user_data*)cur_packet);
    }
}

void read_write_socket::ramka_challenge_log_ack( char etap)//odbieranie
{
    if( etap == PACKET_ID )
    {
        header_size = 1;
        packet_size = 1;    //ustawiamy długość nagłówka i pakietu narazie na tyle samo
        cur_packet = (void*) new challenge_log_ack;
    }
    else if( etap == HEADER )
    {
        char receive[1];        //nagłówek
        quint8 size;
        readData(receive,1);

        size = *(receive);
        packet_size = size;
    }
    else if( etap == TEXTT )
    {
        char data[packet_size];
        int read = readData(data,packet_size);
        ((challenge_log_ack*)cur_packet)->login = QString(data);
        emit msg_challenge_log_ack((challenge_log_ack*)cur_packet);
    }
}

void read_write_socket::ramka_challenge_reg_ack(char etap)
{
    if( etap == PACKET_ID )
    {
        header_size = 2;
        packet_size = 2;    //ustawiamy długość nagłówka i pakietu narazie na tyle samo
        cur_packet = (void*) new challenge_reg;
    }
    else if( etap == HEADER )
    {

        char receive[2];        //nagłówek
        readData(receive,2);

        quint16 length;
        data_copy((char*)&length, receive, 2);

        packet_size = length;
    }
    else if( etap == TEXTT )
    {
        char data[packet_size];
        int read = readData(data,packet_size);
                    std::string s2(data, packet_size-1);
        ((challenge_reg*)cur_packet)->encoded_random_string = std::string(s2);
        emit msg_challenge_reg_ack((challenge_reg*)cur_packet);
    }
}

void read_write_socket::send_text_message()//wysylanoe
{
        text_message data;

        QString tekst = ((Rozmowa*)(sender()->parent()))->message->toPlainText();

        data.key_num =((MainWindow*)parent())->logged_user.key_num;//    user_data* logged_user; in mainwindwo
        data.sender_id=((MainWindow*)parent())->logged_user.numer;
        data.receiver_id=((Rozmowa*)(sender()->parent()))->user_numer;
        data.msg_number=1;//sender()->msg number?????
        data.text = tekst;

        Protocol->packet_message(this, &data);
}

void read_write_socket::send_login()//wysylanie
{
    user_data data=((MainWindow*)parent())->logged_user;

////dane charakterystyczne dla danej ramki

   Protocol->packet_user_data(this, &data );

////------------------------------------------


}

void read_write_socket::send_challenge_reg(std::string encoded_random_string)//wysylanie
{

    challenge_reg creg;

    creg.encoded_random_string=encoded_random_string;

    Protocol->packet_challenge_reg(this, &creg);
}

void read_write_socket::send_reg_data(std::string login)//wysylanie   std::string encoded_random_string
{
    user_data data;
    QString random_string_plus_login=password+random_string+QString::fromStdString(login);
    data.login=random_string_plus_login;
    data.numer=3334;
    //data.haslo=this->password;
////dane charakterystyczne dla danej ramki
    std::cout <<endl<<"random_string_plus_login: "<<random_string_plus_login.toStdString()<<endl;
    Protocol->packet_user_data(this, &data);
////------------------------------------------

}

void read_write_socket::msg_wrap_up()
{
    //if(execution)
   //     ;///wyslano
    //else
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Blad","nie udalo sie wyslac pakietu !");
        messageBox.setFixedSize(500,200);
    }
}
