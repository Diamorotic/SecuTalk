//#include "connection.hh"
//#include <string>
//#include <iostream>
//#include "readConnection.hpp"

//void Connection::send_user_data(user_data userData,const SOCKET &sock)///
//{
//    Protocol *pp=new Protocol();
//    userData.key_num ='k';
//    pp->packet_user_data( &userData, sock );
//}

//void Connection::send_user_data_login(user_data userData,const SOCKET &sock)
//{
//    int bytesSent;
//    Protocol *p=new Protocol();
//    user_data data;
//
////dane charakterystyczne dla danej ramki
//    data.login = userData.login;
//    data.numer = userData.numer;
//    data.state = userData.state;
//    data.key_num ='k';
//
//    unsigned int size;
//    p->packet_user_data_login( &data, sock );
//    //bytesSent = send( sock, sendd, size, 0 );
//}

//void Connection::send_challenge_log_ack(string log,const SOCKET &sock)
//{
//    Protocol *p=new Protocol();
//
//    challenge_log_ack cla;
//
//    cla.login=log;
//
//    unsigned int size;
//    p->packet_challenge_log_ack( &cla, sock );
//    //bytesSent = send( sock, sendd, size, 0 );
//}

//void Connection::send_text_message(char* bufor,unsigned int size, const SOCKET &sock)///bez analizy pakietu
//{
//    Protocol *p=new Protocol();
//    p->send_package(bufor,size,sock);
//    //bytesSent = send( sock, bufor, size, 0 );
//}

//void Connection::send_challenge_reg_ack(string encoded_random_string, const SOCKET &sock)
//{
//    int bytesSent;
//    Protocol *p=new Protocol();
//    challenge_reg cra;
//
////dane charakterystyczne dla danej ramki
//    cra.encoded_random_string = encoded_random_string;
//
//    //unsigned int size;
//    p->packet_challenge_reg_ack( &cra, sock);
//    //bytesSent = send( sock, sendd, size, 0 );
//    //cout <<endl<<"bytesSent: "<<bytesSent<<endl;
//}


//queued_frame Connection::read_data(const SOCKET &sock)///tutaj read
//{
//    ReadConnection readConnection(sock);
//    readConnection.start();
//    readConnection.join();///jakims cudem zdetachowac - zrobic
//    queued_frame qf;
//    qf.packet_size=readConnection.size;
//    qf.cur_packet=readConnection.bufor;
//    qf.packet_type=qf.cur_packet[0];
//    return qf;
//}

//queued_frame Connection::read_data(char *bufor,unsigned int size)///tutaj read
//{
//    queued_frame qf;
//    qf.packet_size=size;
//    qf.cur_packet=bufor;
//    switch(bufor[0])
//    {
//    case 0x10:///#define RAMKA_USER_DATA         0x10
//        //cout <<"ramka?"<<std::hex<<(int)bufor[0]<<endl;
//        qf.packet_type=0x10;
//        return qf;
//        break;
//    case 0x0F:///#define RAMKA_MESSAGE           0x0F
//        qf.packet_type=0x0F;
//        return qf;
//        break;
//    case 0x16:///#define RAMKA_CHALLENGE_REG     0x16
//        qf.packet_type=0x16;
//        return qf;
//        break;
//    }
//    qf.cur_packet=NULL;
//    qf.packet_size=0;
//    return qf;
//}
