#include "rozmowa.h"
#include "ui_rozmowa.h"
#include <QString>
#include <mainwindow.h>
#include <iostream>
#include <QStringListModel>
#include <stdio.h>
#include <stdlib.h>

Rozmowa::Rozmowa(QWidget *parent, const QModelIndex& index, Model* mod ) :
    QDialog(parent),
    ui(new Ui::Rozmowa)
{
    ui->setupUi(this);
    message = this->findChild<QPlainTextEdit*>("wiadomosc");//message qplaintext wyslanie
    message->insertPlainText("");
    message->clear();
    QPushButton* send = this->findChild<QPushButton*>("send");
    model = mod;

    QModelIndex ind = model->index( index.row(), 0, QModelIndex() );
    //((MainWindow*)this->parent())->logged_user.numer;
    QVariant value = model->data( ind, Qt::DisplayRole).toString();
    QString title = value.toString();
    ind = model->index( index.row(), 2 );
    char numer[9];
    itoa(((MainWindow*)this->parent())->logged_user.numer,numer,10);
    title += " - (";
    //title += ind.data().toString();
    title += " moj numer: ";
    title += numer;
    title += ")";

    setWindowTitle(title);

    QListView* rozmowa = this->findChild<QListView*>("rozmowa");
    rozmowa->setModel(model);
    rozmowa->setRootIndex(index);

    connect(send, SIGNAL(clicked()), ((MainWindow*)this->parent())->socket, SLOT(send_text_message()));
    connect(this->model, SIGNAL(syg_rozm(int)),this,SLOT(syg_rozm_slot(int)));
}

void Rozmowa::syg_rozm_slot(int index)
{
    //this->index=index;
    QListView* rozmowa = this->findChild<QListView*>("rozmowa");
    QStringList list= model->messages[index];
    rozmowa->setModel(new QStringListModel(list));
}

Rozmowa::~Rozmowa()
{
    delete ui;
}

void Rozmowa::reject()
{
    QListView* rozmowa = this->findChild<QListView*>("rozmowa");
    model->messages[index].clear();
    QStringList list= model->messages[index];
    rozmowa->setModel(new QStringListModel(list));
    message->clear();
    QDialog::reject();
}
