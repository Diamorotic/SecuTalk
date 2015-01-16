#include "model.h"
#include <QModelIndex>
#include <QDebug>
#include <iostream>
#include <QListView>
#include <QStringListModel>

#define MAX_COLUMN     3

Model::Model(QObject* parent) : QAbstractItemModel( parent )
{
    //connect(this, SIGNAL(syg_rozm()),this,SLOT(syg_rozm_slot()));
    //connect(this, SIGNAL(columnsInserted()),this,SLOT(insertion_complete()));
    /*QString login = "login1";
    QString numer = "63444";
    QString status = "zalogowany";
    QList<QString> lista;
    lista.push_back(login);
    lista.push_back(numer);
    lista.push_back(status);
    user_list.push_back(lista);

    login = "login2";
    numer = "11111";
    status = "zalogowany";
    QList<QString> lista2;
    lista2.push_back(login);
    lista2.push_back(numer);
    lista2.push_back(status);
    user_list.push_back(lista2);

    login = "login3";
    numer = "22222";
    status = "wylogowany";
    QList<QString> lista3;
    lista3.push_back(login);
    lista3.push_back(numer);
    lista3.push_back(status);
    user_list.push_back(lista3);

    login = "login4";
    numer = "33333";
    status = "zablokowany";
    QList<QString> lista4;
    lista4.push_back(login);
    lista4.push_back(numer);
    lista4.push_back(status);
    user_list.push_back(lista4);*/
}

Model::~Model()
{
    for( int i =0; i<users.count(); ++i )
        delete &users[i];

    for( int i =0; i<messages.count(); ++i )
        delete &messages[i];

//    QListView* rozmowa = this->findChild<QListView*>("rozmowa");
//    QStringList list;
//    rozmowa->setModel(new QStringListModel(list));
}


int Model::rowCount(const QModelIndex &parent) const
{
    if( parent == QModelIndex() )//jestesmy na poziomie listy użytkowników
        return user_list.count();//zliczamy użytkowników
    else if( parent.internalPointer() == &user_list )       //jesteśmy na poziomie wiadomości
        return messages[parent.row()].count();          //zliczamy liczbę wiadomości dla danego użytkownika
    return 0;
}

int Model::columnCount(const QModelIndex & parent) const
{
    if( parent == QModelIndex() )//jestesmy na poziomie listy użytkowników
        return MAX_COLUMN;      //liczba różnych pól danych
    else if( parent.internalPointer() == &user_list )       //jesteśmy na poziomie wiadomości
        return 1;       //na tym poziomie jest zwykła lista
    return 0;
}

QVariant Model::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        if( index.internalPointer() == &user_list )
        {
            if( index.row() > user_list.count())
                return QVariant();
            if( index.column() > MAX_COLUMN )
                return QVariant();

            return user_list[index.row()].at(index.column());

        }

        if( index.column() > 1 )    //zawsze jest jedna kolumna
            return QVariant();

        int i = 0;
        for( ; i<messages.count(); ++i )
        //szukamy użytkownika, którego dotyczy index
            if( index.internalPointer() == &messages[i] )
                break;
        if( i >= messages.count() )
        //nie znalexlismy takiego użytkownika
            return QVariant();
        int a=index.row();
       //qDebug() << "index.row() w data:" << a<<"   "<<messages[i];
        return messages[i].at(index.row());
    }

    return QVariant();

}

QModelIndex Model::index ( int row, int column, const QModelIndex & parent ) const
{
    if( parent == QModelIndex() )   //jesteśmy na poziomie danych użytkowników
        return createIndex( row, column, (void*)&user_list );
    else if( parent.internalPointer() == &user_list )
    {
        //pobieramy użytkownika
        int new_column = parent.row();
        if( column > 0 )
            return QModelIndex();

        //qDebug() << "new_column w index:" << new_column;

        return createIndex( row, 0, (void*)(&messages[new_column]) );
    }
    return QModelIndex();
}


QModelIndex Model::parent ( const QModelIndex & index ) const
{
    int i=0;
    for( ; i<messages.count(); ++i )
    //szukamy użytkownika, którego dotyczy index
        if( index.internalPointer() == &messages[i] )
            break;
    if( i >= messages.count() )
        return QModelIndex();
    return createIndex(i,0,(void*)&user_list);
}


unsigned int Model::get_user_numer( int row )
{
    return users[row].numer;
}


void Model::msg_message(text_message* msg)
{

    unsigned short i = 0;
    for( ; i < users.size();++i)
        if( users[i].numer == msg->sender_id )
            break;

    if( i >= users.size() )
    {//a to ciekawe, dostaliśmy wiadomość od kogoś kogo nie znamy
        user_data* data = new user_data;
        data->numer = msg->sender_id;
        data->key_num = 0;
        data->state = NIE_ZNANY;

        users.push_back(*data);

        QString login = data->login;
        QString numer;
        numer.setNum(data->numer);

        QString status = "użytkownik nieznany";

        QList<QString> lista;
        lista.push_back(login);
        lista.push_back(numer);
        lista.push_back(status);
        int size = user_list.count();

        beginInsertRows(QModelIndex(),size,size);
        user_list.push_back(lista);

        //wrzucamy pustą listę wiadomości
        QList<QString>* lista_wiadomosci = new QList<QString>;
        messages.push_back(*lista_wiadomosci);

        endInsertRows();
    }

    QModelIndex index = createIndex(i,0,(void*)&user_list);

    int size = messages[i].count();

    beginInsertRows(index,size,size);
    QString* txt=new QString(msg->text);
    messages[i].push_back(*txt);
    endInsertRows();
    emit syg_rozm(i);
    delete msg;     //to jest ostatnie miejsce, w którym pakiet się pojawi
}



void Model::msg_user_data(user_data* data)
{
    if( data->state == NIE_ISTNIEJE )
    {//struktura już nie będzie wiecej potrzebna
        delete data;
        return;
    }

    unsigned short i = 0;
    for( ; i < users.size();++i)
        if( users[i].numer == data->numer )
            break;

    if( i >= users.size() )
    {//nie było jeszcze użytkownika, wiec dodajemy
        users.push_back(*data);

        QString login = data->login;
        QString numer;
        numer.setNum(data->numer);

        QString status;
        if( data->state == ZALOGOWANY )
            status = "zalogowany";
        else if( data->state == WYLOGOWANY )
            status = "wylogowany";
        else if( data->state == ZABLOKOWANY )
            status = "zablokowany";
        else if( data->state == USUNIETY )
            status = "usunięty";

        QList<QString> lista;
        lista.push_back(login);
        lista.push_back(numer);
        lista.push_back(status);
        int size = user_list.count();

        beginInsertRows(QModelIndex(),size,size);
        user_list.push_back(lista);

        //wrzucamy pustą listę wiadomości
        QList<QString>* lista_wiadomosci = new QList<QString>;
        messages.push_back(*lista_wiadomosci);

        endInsertRows();
                  //qDebug() << "list size:" << user_list.size();
    }
    else    //użytkownik już był, więc musimy skasować strukturę
        delete data;

}


