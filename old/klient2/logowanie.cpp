#include "logowanie.h"
#include "ui_logowanie.h"
#include "deklaracje.h"
#include <QFileDialog>
#include "mainwindow.h"
#include "model.h"
#include "iostream"
#include <QAbstractSocket>

Logowanie::Logowanie(QWidget *parent, char type) :
    QDialog(parent),
    ui(new Ui::Logowanie)
{
    ui->setupUi(this);

//ustawiamy stan radiobuttonów zgodnie z tym co ktoś kliknął w menu
    if( type == NORMAL_LOG )
    {
       QRadioButton* log_type =  this->findChild<QRadioButton*>("radioButton_1");
       log_type->setChecked(true);
    }
    else if( type == DELETE_ACOUNT )
    {
        QRadioButton* log_type =  this->findChild<QRadioButton*>("radioButton_3");
        log_type->setChecked(true);
    }
    else if( type == CHANGE_KEY )
    {
        QRadioButton* log_type =  this->findChild<QRadioButton*>("radioButton_2");
        log_type->setChecked(true);
    }
    else if( type == BLOCK_ACOUNT )
    {
        QRadioButton* log_type =  this->findChild<QRadioButton*>("radioButton_4");
        log_type->setChecked(true);
    }
    login = this->findChild<QLineEdit*>("Login");
    //dołączamy funkcję wyjścia z dialogu (przyciskiem OK)
    QDialogButtonBox* button =  this->findChild<QDialogButtonBox*>("buttonBox");
    connect(button, SIGNAL(accepted()),this, SLOT(accept_log()));
}

Logowanie::~Logowanie()
{
    delete ui;
}

void Logowanie::on_admin_log_clicked(bool checked)
{
    QGroupBox* log_type =  this->findChild<QGroupBox*>("groupBox");
    QLineEdit* pass_text_field =  this->findChild<QLineEdit*>("super_pass");
    if(checked)
        log_type->setEnabled(false),pass_text_field->setEnabled(false);
    else
    {
        QRadioButton* normal_log =  this->findChild<QRadioButton*>("radioButton_1");

        log_type->setEnabled(true);
        if(!normal_log->isChecked())
            pass_text_field->setEnabled(true);
    }
}


void Logowanie::on_radioButton_1_toggled(bool checked)
{
    QLineEdit* pass_text_field =  this->findChild<QLineEdit*>("super_pass");
    if(checked)
        pass_text_field->setEnabled(false);
    else
        pass_text_field->setEnabled(true);
}

void Logowanie::on_pushButton_clicked()
{
    KeyFileName = QFileDialog::getOpenFileName(this);
    if( KeyFileName != QString::null )
    {
        QLineEdit* FilePath =  this->findChild<QLineEdit*>("file_path");
        FilePath->setText(KeyFileName);
    }
}


void Logowanie::accept_log()
{
    //radio button dla normalnego logowania
    QRadioButton* radio =  this->findChild<QRadioButton*>("radioButton_1");
    QString log = login->text();
    ((MainWindow*)this->parent())->logged_user.login=log;//ramka z user data do wyslania z logowaniem zrobic
    if( radio->isChecked() )
    {//logujemy się w normalny sposób
        ((MainWindow*)parent())->socket = new read_write_socket( this->parent(), &(((MainWindow*)this->parent())->IP_and_port),'l' );
        connect_slots();
        ((MainWindow*)parent())->socket->connect_to();      //łączymy z adresem wcześniej ustalonym

        //tutaj bedzie challenge narazie wystarczy connect
        return;     //na wszelki wypadek; bo tylko jeden radio powinien być zaznaczony
    }

    radio =  this->findChild<QRadioButton*>("radioButton_2");
    if( radio->isChecked() )
    {

        return;     //na wszelki wypadek, tylko jeden radio powinien być zaznaczony
    }

    radio =  this->findChild<QRadioButton*>("radioButton_3");
    if( radio->isChecked() )
    {

        return;     //na wszelki wypadek, tylko jeden radio powinien być zaznaczony
    }

    radio =  this->findChild<QRadioButton*>("radioButton_4");
    if( radio->isChecked() )
    {

        return;     //na wszelki wypadek, tylko jeden radio powinien być zaznaczony
    }
}


void Logowanie::connect_slots()
{
    connect(((MainWindow*)parent())->socket, SIGNAL(msg_user_data(user_data*)),((MainWindow*)parent()), SLOT(msg_user_data(user_data*)));
   //to pozniej po logowaniu(na koncu!) connect(((MainWindow*)parent())->socket, SIGNAL(msg_user_data_login(user_data*)),((MainWindow*)parent()), SLOT(msg_user_data_login(user_data*)));
    connect(((MainWindow*)parent())->socket, SIGNAL(msg_message(text_message*)),((MainWindow*)parent()), SLOT(msg_message(text_message*)));
    connect(((MainWindow*)parent())->socket, SIGNAL(msg_challenge_log_ack(challenge_log_ack*)), ((MainWindow*)parent()), SLOT(msg_challenge_log_ack(challenge_log_ack*)));
    connect(((MainWindow*)parent())->socket, SIGNAL(msg_user_data_login(user_data*)),((MainWindow*)parent()), SLOT(msg_user_data_login(user_data*)));
}
