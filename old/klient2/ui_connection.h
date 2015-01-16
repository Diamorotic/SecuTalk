/********************************************************************************
** Form generated from reading UI file 'connection.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECTION_H
#define UI_CONNECTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_connection
{
public:
    QGridLayout *gridLayout;
    QLabel *IPlabel;
    QLineEdit *IP_addr;
    QLabel *serwerPortLabel;
    QLineEdit *serwerPort;
    QLabel *klientPortLabel;
    QLineEdit *klientPort;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *connection)
    {
        if (connection->objectName().isEmpty())
            connection->setObjectName(QStringLiteral("connection"));
        connection->resize(429, 246);
        gridLayout = new QGridLayout(connection);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        IPlabel = new QLabel(connection);
        IPlabel->setObjectName(QStringLiteral("IPlabel"));
        QFont font;
        font.setPointSize(10);
        IPlabel->setFont(font);
        IPlabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(IPlabel, 0, 0, 1, 1);

        IP_addr = new QLineEdit(connection);
        IP_addr->setObjectName(QStringLiteral("IP_addr"));
        IP_addr->setFont(font);

        gridLayout->addWidget(IP_addr, 0, 1, 1, 1);

        serwerPortLabel = new QLabel(connection);
        serwerPortLabel->setObjectName(QStringLiteral("serwerPortLabel"));
        serwerPortLabel->setFont(font);
        serwerPortLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(serwerPortLabel, 1, 0, 1, 1);

        serwerPort = new QLineEdit(connection);
        serwerPort->setObjectName(QStringLiteral("serwerPort"));

        gridLayout->addWidget(serwerPort, 1, 1, 1, 1);

        klientPortLabel = new QLabel(connection);
        klientPortLabel->setObjectName(QStringLiteral("klientPortLabel"));
        klientPortLabel->setFont(font);
        klientPortLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(klientPortLabel, 2, 0, 1, 1);

        klientPort = new QLineEdit(connection);
        klientPort->setObjectName(QStringLiteral("klientPort"));

        gridLayout->addWidget(klientPort, 2, 1, 1, 1);

        buttonBox = new QDialogButtonBox(connection);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 3, 0, 1, 2);

        QWidget::setTabOrder(serwerPort, klientPort);
        QWidget::setTabOrder(klientPort, buttonBox);

        retranslateUi(connection);
        QObject::connect(buttonBox, SIGNAL(accepted()), connection, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), connection, SLOT(reject()));

        QMetaObject::connectSlotsByName(connection);
    } // setupUi

    void retranslateUi(QDialog *connection)
    {
        connection->setWindowTitle(QApplication::translate("connection", "Ustawienia po\305\202\304\205cze\305\204", 0));
        IPlabel->setText(QApplication::translate("connection", "Adres IP serwera", 0));
        serwerPortLabel->setText(QApplication::translate("connection", "Port serwera", 0));
        klientPortLabel->setText(QApplication::translate("connection", "Port klienta", 0));
        klientPort->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class connection: public Ui_connection {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTION_H
