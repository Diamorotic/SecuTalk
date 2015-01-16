/********************************************************************************
** Form generated from reading UI file 'rozmowa.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROZMOWA_H
#define UI_ROZMOWA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListView>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Rozmowa
{
public:
    QPlainTextEdit *wiadomosc;
    QPushButton *send;
    QListView *rozmowa;

    void setupUi(QDialog *Rozmowa)
    {
        if (Rozmowa->objectName().isEmpty())
            Rozmowa->setObjectName(QStringLiteral("Rozmowa"));
        Rozmowa->resize(401, 330);
        wiadomosc = new QPlainTextEdit(Rozmowa);
        wiadomosc->setObjectName(QStringLiteral("wiadomosc"));
        wiadomosc->setGeometry(QRect(20, 240, 361, 51));
        send = new QPushButton(Rozmowa);
        send->setObjectName(QStringLiteral("send"));
        send->setGeometry(QRect(280, 290, 101, 31));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(send->sizePolicy().hasHeightForWidth());
        send->setSizePolicy(sizePolicy);
        send->setMinimumSize(QSize(0, 0));
        QFont font;
        font.setPointSize(10);
        send->setFont(font);
        rozmowa = new QListView(Rozmowa);
        rozmowa->setObjectName(QStringLiteral("rozmowa"));
        rozmowa->setGeometry(QRect(10, 10, 381, 221));

        retranslateUi(Rozmowa);

        QMetaObject::connectSlotsByName(Rozmowa);
    } // setupUi

    void retranslateUi(QDialog *Rozmowa)
    {
        Rozmowa->setWindowTitle(QApplication::translate("Rozmowa", "Dialog", 0));
        send->setText(QApplication::translate("Rozmowa", "Wy\305\233lij", 0));
    } // retranslateUi

};

namespace Ui {
    class Rozmowa: public Ui_Rozmowa {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROZMOWA_H
