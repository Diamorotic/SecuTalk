#ifndef MODEL_H
#define MODEL_H

#include <QAbstractItemModel>
#include "deklaracje.h"
#include <QList>
#include <QVector>


class Model : public QAbstractItemModel
{
    Q_OBJECT

public:
    Model(QObject *parent = 0);
    ~Model();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    //QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QModelIndex index ( int row, int column, const QModelIndex & parent = QModelIndex() ) const;
    QModelIndex parent ( const QModelIndex & index ) const;

    text_message mes;
    QVector<QList<QString> > messages;
    unsigned int get_user_numer( int row );
signals:
    void syg_rozm(int index);

private:
    QVector<QList<QString> > user_list;

    QVector<user_data> users;          //tutaj są dane w postaci struktury


public slots:
    void msg_message(text_message*);
    void msg_user_data(user_data*);
};

#endif // MODEL_H
