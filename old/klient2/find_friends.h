#ifndef FIND_FRIENDS_H
#define FIND_FRIENDS_H

#include <QDialog>
#include "deklaracje.h"

namespace Ui {
class find_friends;
}

class find_friends : public QDialog
{
    Q_OBJECT

public:
    explicit find_friends(QWidget *parent = 0);
    ~find_friends();

private:
    Ui::find_friends *ui;

signals:
    void find_user(user_data*);           //prosimy o zapytanie serwera o użytkownika
    void add_friend(int);               //prosimy o dodanie znajomego

public slots:
    void set_user_data(user_data*);         //wstawiamy dane do formularza
};

#endif // FIND_FRIENDS_H
