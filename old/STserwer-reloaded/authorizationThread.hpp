#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

#include "sendThread.hpp"
#include "receiveThread.hpp"


using namespace std;
extern MonitorList<User*>* userArray;
extern std::string decrypt(std::string cipher2);
extern std::string encrypt(std::string message);

static int aa=0;///tymczosowo do testowania

class AuthorizationThread : public ThreadBase
{
private:
    SOCKET* m_resource;

public:
    AuthorizationThread(SOCKET* i_resource) : m_resource(i_resource) { }

    virtual void run()
    {
        ///watek autoryzacji serwera///////////////////////////////////////////////////////////////
        bool rejestracj=true;
        SOCKET* sock = m_resource;
//        Connection *connection=new Connection();
        Protocol *protocol=new Protocol();
        user_data loggedUser;
        char recvbuf[ MAXLEN];
        int bytesRecv=0;
        if(rejestracj)
        {
            queued_frame receivedFrame=protocol->read_data(*sock);//frame, bytesRecv+1,


            if(receivedFrame.packet_type == RAMKA_CHALLENGE_REG)
            {
                ///Rejestracja
                //dekodowanie i obrobka poza watkiem glownym -> i tak nic nie moze przetwarzac bez zestawienia polaczenia z klientem
                challenge_reg challengeReg=protocol->get_challenge_reg(receivedFrame);
                std::string random_string=decrypt(challengeReg.encoded_random_string);///bardzo wazne// tak po prawdzie sam powinien wygenerowac nowy

                challenge_reg cra;
                cra.encoded_random_string = encrypt(random_string);
                protocol->packet_challenge_reg_ack(&cra,*sock);
                ///czekamy na userdata
                queued_frame receivedFrame=protocol->read_data(*sock);
                loggedUser=protocol->get_user_data(receivedFrame);

                if(receivedFrame.packet_type == RAMKA_USER_DATA)
                {
                    std::string login=loggedUser.login;
                    std::size_t pos = login.find(random_string);
                    if(pos != string::npos)/// random_string sie zgadza klient uwierzytelniony
                    {
                        std::string haslo = string (login, 0,pos);
                        std::string l = string (login.substr (pos), random_string.length(), login.length());
                        loggedUser.login=l;///login
                        loggedUser.haslo=haslo;
                        loggedUser.state=0x1;
                        ///wyslij numer
                        ///scenariusz testowy
                        if(aa==0)
                            loggedUser.numer=2345;
                        else if(aa==1)
                            loggedUser.numer=9000;
                        else if(aa==2)
                            loggedUser.numer=4567;
                        else
                            aa++;
                        aa++;
                        protocol->packet_user_data_login(&loggedUser,*sock);

                    }
                    else
                    {
                        ///cos zlego
                    }
                }
            }
        }
//        if ( !rejestracj)
//        {
//            /// /////////////////////////////////LOGOWANIE
//            connection->send_challenge_log_ack("asdfbotak",*sock);//do klienta qt
//            // rownie dobrze mozna dac nowa funkcje ustaw dane uzytkownika pomocniczo
//            while(bytesRecv<1)
//            {
//                bytesRecv = recv( (*sock), recvbuf, sizeof(recvbuf) - 1, 0 )+bytesRecv;
//                if (bytesRecv == -1)
//                {
//                    perror("blad odczytu");
//                    exit(1);
//                }
//            }
//            recvbuf[bytesRecv+1] = '\0';///odbior challenge reg///
//
//            //alokacja danych
//            char* frame=(char*)malloc(bytesRecv+1);
//            memcpy(frame,recvbuf, bytesRecv+1);
//            connection->read_data(frame, sizeof(frame));///odebrana ramka, przerobic na user data pozniej, patrz nizej //prerobic login protocol, caly
//
//            //odczytanie ramki powinien by user data
//            user_data loggedUser;
//            loggedUser.login=string(recvbuf);
//            cout <<"logged user login: "<<loggedUser.login<<endl;
//            loggedUser.numer=1234;
//            //tymczasowo cos wyslemy anyway
//            if(aa==0)
//            {
//                user_data userData;
//                userData.login="uzytkownik a";
//                userData.numer=1234;
//                userData.state=0x1;
//
//                user_data userData2;
//                userData2.login="uzytkownik b";
//                userData2.numer=2345;
//                userData2.state=0x1;
//
//                connection->send_user_data_login(userData,*sock);
//                connection->send_user_data(userData2,*sock);//9876
//                connection->send_user_data(userData,*sock);//9876
//                loggedUser.numer=1234;
//                aa++;
//            }
//            else
//            {
//                user_data userData;
//                userData.login="uzytkownik a";
//                userData.numer=1234;
//                userData.state=0x1;
//
//                user_data userData2;
//                userData2.login="uzytkownik b";
//                userData2.numer=2345;
//                userData2.state=0x1;
//                connection->send_user_data_login(userData2,*sock);
//                connection->send_user_data(userData,*sock);//9876
//                loggedUser.numer=2345;
//            }
/////  //////////////////////////////
//        }
        User* newUser=new User(*sock,loggedUser);
        if(userArray->push(newUser)==false)/// jesli numer juz jest w bazie odrzuc polaczenie - do zrobienia
            ExitProcess(0);

        if(aa==3)
            scenariusz();

        SendThread sendThread(newUser);///odpalamy watki
        ReceiveThread receiveThread(newUser);
        receiveThread.start();
        sendThread.start();

        receiveThread.join();
        sendThread.join();
    }

    void scenariusz()
    {
        list<User*>::iterator temp=userArray->begin();
        while(temp!=userArray->end())
        {

            list<User*>::iterator tempIterator=userArray->begin();
            while(tempIterator!=userArray->end())
            {
                Protocol *protocol=new Protocol();
                user_data send_user_data;
                send_user_data.numer=(*tempIterator)->numer;
                send_user_data.state=(*tempIterator)->state;
                send_user_data.login=(*tempIterator)->login;
                protocol->packet_user_data(&send_user_data,(*temp)->getSocket());
                tempIterator++;
            }
            temp++;
        }
    }
};
