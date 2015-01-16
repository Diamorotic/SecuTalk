#ifndef LOGOWANIE_H
#define LOGOWANIE_H

#include <QDialog>
#include <QLineEdit>

namespace Ui {
class Logowanie;
}

class Logowanie : public QDialog
{
    Q_OBJECT


    QString KeyFileName;
public:

    explicit Logowanie(QWidget *parent, char type);
    ~Logowanie();

private slots:
    void on_admin_log_clicked(bool checked);
    void on_radioButton_1_toggled(bool checked);
    void accept_log();

    void on_pushButton_clicked();

private:
    QLineEdit* login;
    Ui::Logowanie *ui;

    void connect_slots();
};

#endif // LOGOWANIE_H
