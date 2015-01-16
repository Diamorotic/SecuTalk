#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logowanie.h"
#include "rejestracja.h"
#include "deklaracje.h"
#include "connection.h"
#include <QMessageBox>
#include <QStringListModel>
#include <QListView>
void data_copy(char* dest, const char* src, int length)
{
    for( int i=0; i<length; ++i)
        dest[i] = src[i];
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    FindDialog = NULL;
    socket = NULL;
    //logged_user = NULL;
    model = new Model(this);

    IP_and_port.port_klienta = 5555;
    IP_and_port.port_serwera = 5555;
    IP_and_port.adres = "127.0.0.1";
    //connect( menuBar()->MenuUstawienia()->actionPolaczenie, SIGNAL(triggered()), this, SLOT(connection_params());

    QTableView* tabela_znajomych = this->findChild<QTableView*>("Znajomi");
    tabela_znajomych->setModel(model);
    connect( tabela_znajomych, SIGNAL(doubleClicked(QModelIndex)),this,SLOT(user_click(QModelIndex)));
    //logged_user.key_num='k';//to bedzie zrobione w logowanie rws
    //logged_user.login='uzytkownikLog';
    //logged_user.numer=1234;
    //logged_user.state=ZALOGOWANY;

}

MainWindow::~MainWindow()
{
    delete ui;
    if(FindDialog != NULL)
        delete FindDialog;
}


void MainWindow::on_actionPolaczenie_triggered()
{
    connection* DialogParam = new connection(this, &IP_and_port);
    DialogParam->exec();
    delete DialogParam;
}

//okienko wyszukiwania żąda zapytania do serwera
void MainWindow::find_user(user_data *)
{


}

//wysyłamy do serwera prośbę o dodanie znajomego
void MainWindow::add_friend(int)
{


}

void MainWindow::on_actionSzukaj_triggered()
{
    if( FindDialog == NULL)
        FindDialog = new find_friends(this);
    FindDialog->show();
}


void MainWindow::on_actionLogowanie_triggered()
{
    Logowanie* log_dialog = new Logowanie(this, NORMAL_LOG);
    log_dialog->exec();
    delete log_dialog;
}

void MainWindow::on_actionZarejestruj_konto_triggered()
{
    Rejestracja* log_dialog = new Rejestracja(this);
    log_dialog->exec();
    delete log_dialog;
}

void MainWindow::on_actionZablokuj_konto_triggered()
{
    Logowanie* log_dialog = new Logowanie(this, BLOCK_ACOUNT);
    log_dialog->exec();
    delete log_dialog;
}

void MainWindow::on_actionUsu_konto_triggered()
{
    Logowanie* log_dialog = new Logowanie(this, DELETE_ACOUNT);
    log_dialog->exec();
    delete log_dialog;
}

void MainWindow::on_actionZmie_klucz_publiczny_triggered()
{
    Logowanie* log_dialog = new Logowanie(this, CHANGE_KEY);
    log_dialog->exec();
    delete log_dialog;
}

void MainWindow::user_click(const QModelIndex& index)
{
    if( !index.isValid() )
        return;

    unsigned int numer = model->get_user_numer(index.row());
    int i = 0;
    for( ; i<speeches.count();++i )
        if( speeches[i]->user_numer == numer )
        {
            speeches[i]->show();
            speeches[i]->index=i;
            return;
        }
    Rozmowa* rozmowa = new Rozmowa( this, index, model  );
    speeches.push_back(rozmowa);
    rozmowa->index=i;
    rozmowa->user_numer = numer;

    connect(rozmowa,SIGNAL(destroyed(QObject*)),this,SLOT(user_window_close(QObject*)));
    rozmowa->show();
}

void MainWindow::user_window_close(QObject *rozmowa)
{
    speeches.removeAll((Rozmowa*)rozmowa);
    //delete
    QMessageBox::critical(this, tr("Uwaga!"),
       tr("Okno wysłało wiadomość destroy"));
}


void MainWindow::msg_message(text_message* msg)
{

    model->msg_message(msg);
}

void MainWindow::msg_user_data(user_data* data)
{

    model->msg_user_data(data);
}

void MainWindow::msg_user_data_login(user_data* data)
{

    logged_user=*data;
}

void MainWindow::msg_challenge_log_ack(challenge_log_ack* cla)
{

   //wyslij login z logowanie.cpp dodaj structa do .h i wszystko w accept log (login przez readwritelogin)
    this->logged_user.login=cla->login;
    this->socket->send_login();
}
void MainWindow::msg_challenge_reg_ack(challenge_reg* cr)
{

    std::string decoded_random_string=decrypt(cr->encoded_random_string);
    if(this->socket->random_string.toStdString()==decoded_random_string)//Im legit I swear!
    {
        this->socket->send_reg_data(logged_user.login.toStdString());/// weszlo
    }
    else
    {
        //cos sie zlego stalo
    }
}

void MainWindow::challenge_registration(std::string encoded_random_string)
{
//    QAbstractSocket::SocketState ss=socket->state();
    this->socket->send_challenge_reg(encoded_random_string);
}

void MainWindow::closeEvent (QCloseEvent *event)
{
//    QMessageBox::StandardButton resBtn = QMessageBox::question( this, APP_NAME, tr("Are you sure?\n"),
//                                                                QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
//                                                                QMessageBox::Yes);
//    speeches;
//    QListView* rozmowa = this->findChild<QListView*>("rozmowa");
//    model->messages[rozmowa->index].clear();
//    QStringList list= model->messages[index];
//    rozmowa->setModel(new QStringListModel(list));
//    event->accept();

//    if (resBtn != QMessageBox::Yes) {
//        event->ignore();
//    } else {
//        event->accept();
//    }
}
