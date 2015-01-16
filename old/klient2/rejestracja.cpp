#include "rejestracja.h"
#include "ui_rejestracja.h"
#include "deklaracje.h"
#include <QFileDialog>
#include "mainwindow.h"
#include "model.h"
#include <QMessageBox>

Rejestracja::Rejestracja(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Rejestracja)
{
    ui->setupUi(this);
    login = this->findChild<QLineEdit*>("Login");
    haslo = this->findChild<QLineEdit*>("haslo");
    powtorz_haslo = this->findChild<QLineEdit*>("powtorz_haslo");
    haslo->setEchoMode(QLineEdit::Password);
    haslo->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);
    powtorz_haslo->setEchoMode(QLineEdit::Password);
    powtorz_haslo->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);


    KeyFileName="C:/Users/Toshiba/Downloads/secuTalk/STserwer-reloaded/keys/rsa-public.key";
    fileName = this->findChild<QLineEdit*>("file_path");
    fileName->setText(KeyFileName);
    //dołączamy funkcję wyjścia z dialogu (przyciskiem OK)
    QDialogButtonBox* button =  this->findChild<QDialogButtonBox*>("buttonBox");

    connect(button, SIGNAL(accepted()),this, SLOT(accept_reg()));
}

Rejestracja::~Rejestracja()
{
    delete ui;
}

void Rejestracja::on_pushButton_clicked()
{
    KeyFileName = QFileDialog::getOpenFileName(this);
    if( KeyFileName != QString::null )
    {
        QLineEdit* FilePath =  this->findChild<QLineEdit*>("file_path");
        FilePath->setText(KeyFileName);
    }
}

void Rejestracja::accept_reg()
{
    //radio button dla normalnego logowania
    //QRadioButton* radio =  this->findChild<QRadioButton*>("radioButton_1");
    QString log = login->text();
    QString has = haslo->text();
    QString pow_has = powtorz_haslo->text();
    if(has!=pow_has)
    {
        this->close();
        QMessageBox messageBox;
        messageBox.critical(0,"Blad","niepoprawne haslo !");
        messageBox.setFixedSize(500,200);
        return;
    }

    ((MainWindow*)this->parent())->logged_user.login=log;//ramka z user data do wyslania z logowaniem zrobic
    ((MainWindow*)parent())->socket = new read_write_socket( this->parent(), &(((MainWindow*)this->parent())->IP_and_port),'r' );
    ((MainWindow*)parent())->socket->KeyFileName=this->KeyFileName;
    connect_slots();//jakie sloty 3 poz? to pozniej
    ((MainWindow*)parent())->socket->connect_to();      //łączymy z adresem wcześniej ustalonym
    ((MainWindow*)parent())->socket->set_password(has);
    this->close();
    return;

}


void Rejestracja::connect_slots()
{
    connect(((MainWindow*)parent())->socket, SIGNAL(msg_user_data(user_data*)),((MainWindow*)parent()), SLOT(msg_user_data(user_data*)));
//   //to pozniej po logowaniu(na koncu!) connect(((MainWindow*)parent())->socket, SIGNAL(msg_user_data_login(user_data*)),((MainWindow*)parent()), SLOT(msg_user_data_login(user_data*)));
    connect(((MainWindow*)parent())->socket, SIGNAL(msg_message(text_message*)),((MainWindow*)parent()), SLOT(msg_message(text_message*)));
///    connect(((MainWindow*)parent())->socket, SIGNAL(msg_challenge_reg(challenge_log_ack*)), ((MainWindow*)parent()), SLOT(msg_challenge_log_ack(challenge_log_ack*)));
    connect(((MainWindow*)parent())->socket, SIGNAL(msg_user_data_login(user_data*)),((MainWindow*)parent()), SLOT(msg_user_data_login(user_data*)));
    connect(((MainWindow*)parent())->socket, SIGNAL(msg_challenge_reg_ack(challenge_reg*)),((MainWindow*)parent()), SLOT(msg_challenge_reg_ack(challenge_reg*)));
}


