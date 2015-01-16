#ifndef REJESTRACJA_H
#define REJESTRACJA_H

#include <QDialog>
#include <QLineEdit>

namespace Ui {
class Rejestracja;
}

class Rejestracja : public QDialog
{
    Q_OBJECT
public:

    explicit Rejestracja(QWidget *parent);
    ~Rejestracja();

private slots:
    //void on_admin_log_clicked(bool checked);
    //void on_radioButton_1_toggled(bool checked);
    void accept_reg();//challenge_reg
    void on_pushButton_clicked();
    //void on_pushButton_clicked();

private:
    QString KeyFileName;
    QLineEdit* login;
    QLineEdit* haslo;
    QLineEdit* powtorz_haslo;
    QLineEdit* fileName;
    Ui::Rejestracja *ui;
    void connect_slots();
};

#endif // REJESTRACJA_H
