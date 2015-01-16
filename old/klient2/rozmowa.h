#ifndef ROZMOWA_H
#define ROZMOWA_H

#include <QDialog>
#include <QPlainTextEdit>
//#include <mainwindow.h>
#include "model.h"

namespace Ui {
class Rozmowa;
}

class Rozmowa : public QDialog
{
    Q_OBJECT

public:
    explicit Rozmowa(QWidget *parent, const QModelIndex& index, Model* mod );
    ~Rozmowa();
    QPlainTextEdit* message;
    unsigned short      user_numer;           //numer użytkownika, z którym rozmawiamy
    int index;
public slots:
        void syg_rozm_slot(int index);
        void reject();
private:
    Ui::Rozmowa *ui;
    Model*              model;


};

#endif // ROZMOWA_H
