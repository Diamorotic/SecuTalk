#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "deklaracje.h"
#include "find_friends.h"
#include "model.h"
#include "read_write_socket.h"
#include "rozmowa.h"
#include <QList>
#include <QModelIndex>
#include "connection.h"
#include "security.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    struct_connect IP_and_port;
    Model* model;
    read_write_socket* socket;
    user_data logged_user;
    //otwarte okna rozmów
    QList<Rozmowa*> speeches;

    void challenge_registration(std::string encoded_random_string);
    void closeEvent (QCloseEvent *event);
private:
    Ui::MainWindow *ui;
    find_friends* FindDialog;

public slots:
    void on_actionPolaczenie_triggered();               //dialog wyboru portów, i adresu serwera
    //class find_friends
    void on_actionSzukaj_triggered();
    void find_user(user_data*);                    //okienko wyszukiwania żąda zapytania do serwera
    void add_friend(int);                       //wysyłamy do serwera prośbę o dodanie znajomego
//tableview
    void user_click(const QModelIndex&);        //otwieramy okno rozmowy
    void user_window_close(QObject*);
//class read_write_socket
    void msg_message(text_message*);
    void msg_user_data(user_data*);
    void msg_user_data_login(user_data*);
    void msg_challenge_log_ack(challenge_log_ack*);
    void msg_challenge_reg_ack(challenge_reg*);
signals:
    //class find_friends
    void set_user_data(user_data*);

private slots:
    void on_actionLogowanie_triggered();
    void on_actionZarejestruj_konto_triggered();
    void on_actionZablokuj_konto_triggered();
    void on_actionUsu_konto_triggered();
    void on_actionZmie_klucz_publiczny_triggered();
    //zrob rejestracje
};


#endif // MAINWINDOW_H
