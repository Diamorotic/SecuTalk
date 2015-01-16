/********************************************************************************
** Form generated from reading UI file 'rejestracja.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REJESTRACJA_H
#define UI_REJESTRACJA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Rejestracja
{
public:
    QLineEdit *powtorz_haslo;
    QLineEdit *haslo;
    QLabel *label_5;
    QLabel *label;
    QDialogButtonBox *buttonBox;
    QLineEdit *Login;
    QLabel *label_3;
    QLineEdit *file_path;
    QPushButton *pushButton;

    void setupUi(QDialog *Rejestracja)
    {
        if (Rejestracja->objectName().isEmpty())
            Rejestracja->setObjectName(QStringLiteral("Rejestracja"));
        Rejestracja->resize(527, 202);
        powtorz_haslo = new QLineEdit(Rejestracja);
        powtorz_haslo->setObjectName(QStringLiteral("powtorz_haslo"));
        powtorz_haslo->setGeometry(QRect(170, 90, 340, 22));
        powtorz_haslo->setInputMethodHints(Qt::ImhHiddenText);
        haslo = new QLineEdit(Rejestracja);
        haslo->setObjectName(QStringLiteral("haslo"));
        haslo->setGeometry(QRect(170, 60, 340, 22));
        haslo->setInputMethodHints(Qt::ImhHiddenText);
        label_5 = new QLabel(Rejestracja);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(40, 90, 111, 22));
        QFont font;
        font.setPointSize(10);
        label_5->setFont(font);
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label = new QLabel(Rejestracja);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(110, 30, 41, 22));
        label->setFont(font);
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        buttonBox = new QDialogButtonBox(Rejestracja);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(170, 150, 340, 30));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(buttonBox->sizePolicy().hasHeightForWidth());
        buttonBox->setSizePolicy(sizePolicy);
        buttonBox->setFont(font);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        Login = new QLineEdit(Rejestracja);
        Login->setObjectName(QStringLiteral("Login"));
        Login->setGeometry(QRect(170, 30, 340, 22));
        label_3 = new QLabel(Rejestracja);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(100, 60, 51, 22));
        label_3->setFont(font);
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        file_path = new QLineEdit(Rejestracja);
        file_path->setObjectName(QStringLiteral("file_path"));
        file_path->setEnabled(true);
        file_path->setGeometry(QRect(170, 120, 340, 27));
        file_path->setFont(font);
        file_path->setReadOnly(true);
        file_path->setClearButtonEnabled(false);
        pushButton = new QPushButton(Rejestracja);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(0, 120, 160, 28));

        retranslateUi(Rejestracja);

        QMetaObject::connectSlotsByName(Rejestracja);
    } // setupUi

    void retranslateUi(QDialog *Rejestracja)
    {
        Rejestracja->setWindowTitle(QApplication::translate("Rejestracja", "Dialog", 0));
        label_5->setText(QApplication::translate("Rejestracja", "Powt\303\263rz has\305\202o", 0));
        label->setText(QApplication::translate("Rejestracja", "Login", 0));
        label_3->setText(QApplication::translate("Rejestracja", "Has\305\202o", 0));
        pushButton->setText(QApplication::translate("Rejestracja", "Wczytaj Plik", 0));
    } // retranslateUi

};

namespace Ui {
    class Rejestracja: public Ui_Rejestracja {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REJESTRACJA_H
