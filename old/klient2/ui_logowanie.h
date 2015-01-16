/********************************************************************************
** Form generated from reading UI file 'logowanie.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGOWANIE_H
#define UI_LOGOWANIE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_Logowanie
{
public:
    QGridLayout *gridLayout;
    QCheckBox *admin_log;
    QLabel *label_4;
    QLineEdit *file_path;
    QPushButton *pushButton;
    QLineEdit *key_pass;
    QLabel *label;
    QDialogButtonBox *buttonBox;
    QLineEdit *Login;
    QLabel *label_3;
    QLabel *label_5;
    QLineEdit *super_pass;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer;
    QRadioButton *radioButton_1;
    QRadioButton *radioButton_3;
    QSpacerItem *horizontalSpacer_2;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_4;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QDialog *Logowanie)
    {
        if (Logowanie->objectName().isEmpty())
            Logowanie->setObjectName(QStringLiteral("Logowanie"));
        Logowanie->resize(525, 352);
        gridLayout = new QGridLayout(Logowanie);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        admin_log = new QCheckBox(Logowanie);
        admin_log->setObjectName(QStringLiteral("admin_log"));
        QFont font;
        font.setPointSize(10);
        admin_log->setFont(font);

        gridLayout->addWidget(admin_log, 6, 1, 1, 1);

        label_4 = new QLabel(Logowanie);
        label_4->setObjectName(QStringLiteral("label_4"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        label_4->setFont(font);

        gridLayout->addWidget(label_4, 1, 1, 1, 1);

        file_path = new QLineEdit(Logowanie);
        file_path->setObjectName(QStringLiteral("file_path"));
        file_path->setEnabled(true);
        file_path->setFont(font);
        file_path->setReadOnly(true);
        file_path->setClearButtonEnabled(false);

        gridLayout->addWidget(file_path, 2, 1, 1, 1);

        pushButton = new QPushButton(Logowanie);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 2, 0, 1, 1);

        key_pass = new QLineEdit(Logowanie);
        key_pass->setObjectName(QStringLiteral("key_pass"));
        key_pass->setInputMethodHints(Qt::ImhHiddenText);

        gridLayout->addWidget(key_pass, 3, 1, 1, 1);

        label = new QLabel(Logowanie);
        label->setObjectName(QStringLiteral("label"));
        label->setFont(font);
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(Logowanie);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(buttonBox->sizePolicy().hasHeightForWidth());
        buttonBox->setSizePolicy(sizePolicy1);
        buttonBox->setFont(font);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 7, 1, 1, 1);

        Login = new QLineEdit(Logowanie);
        Login->setObjectName(QStringLiteral("Login"));

        gridLayout->addWidget(Login, 0, 1, 1, 1);

        label_3 = new QLabel(Logowanie);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font);
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        label_5 = new QLabel(Logowanie);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setFont(font);
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        super_pass = new QLineEdit(Logowanie);
        super_pass->setObjectName(QStringLiteral("super_pass"));
        super_pass->setInputMethodHints(Qt::ImhHiddenText);

        gridLayout->addWidget(super_pass, 4, 1, 1, 1);

        groupBox = new QGroupBox(Logowanie);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(3);
        sizePolicy2.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy2);
        groupBox->setMinimumSize(QSize(507, 149));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalSpacer = new QSpacerItem(112, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 1, 0, 2, 1);

        radioButton_1 = new QRadioButton(groupBox);
        radioButton_1->setObjectName(QStringLiteral("radioButton_1"));
        radioButton_1->setFont(font);

        gridLayout_2->addWidget(radioButton_1, 1, 1, 1, 2);

        radioButton_3 = new QRadioButton(groupBox);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));
        radioButton_3->setFont(font);

        gridLayout_2->addWidget(radioButton_3, 1, 3, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(112, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 1, 4, 2, 1);

        radioButton_2 = new QRadioButton(groupBox);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setFont(font);

        gridLayout_2->addWidget(radioButton_2, 2, 1, 1, 1);

        radioButton_4 = new QRadioButton(groupBox);
        radioButton_4->setObjectName(QStringLiteral("radioButton_4"));
        radioButton_4->setFont(font);

        gridLayout_2->addWidget(radioButton_4, 2, 3, 1, 1);

        verticalSpacer = new QSpacerItem(485, 26, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 0, 0, 1, 5);

        verticalSpacer_2 = new QSpacerItem(485, 26, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 3, 0, 1, 5);


        gridLayout->addWidget(groupBox, 5, 0, 1, 2);

        buttonBox->raise();
        file_path->raise();
        pushButton->raise();
        label_3->raise();
        key_pass->raise();
        label->raise();
        label_4->raise();
        groupBox->raise();
        admin_log->raise();
        Login->raise();
        super_pass->raise();
        label_5->raise();

        retranslateUi(Logowanie);
        QObject::connect(buttonBox, SIGNAL(accepted()), Logowanie, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Logowanie, SLOT(reject()));

        QMetaObject::connectSlotsByName(Logowanie);
    } // setupUi

    void retranslateUi(QDialog *Logowanie)
    {
        Logowanie->setWindowTitle(QApplication::translate("Logowanie", "Dialog", 0));
        admin_log->setText(QApplication::translate("Logowanie", "Zaloguj si\304\231 jako administrator", 0));
        label_4->setText(QApplication::translate("Logowanie", "Plik z kluczem prywatnym", 0));
        pushButton->setText(QApplication::translate("Logowanie", "Wczytaj Plik", 0));
        label->setText(QApplication::translate("Logowanie", "Login", 0));
        label_3->setText(QApplication::translate("Logowanie", "Has\305\202o chroni\304\205ce klucz", 0));
        label_5->setText(QApplication::translate("Logowanie", "Superhas\305\202o", 0));
        groupBox->setTitle(QApplication::translate("Logowanie", "Tryb logowania", 0));
        radioButton_1->setText(QApplication::translate("Logowanie", "Zwyk\305\202e logowanie", 0));
        radioButton_3->setText(QApplication::translate("Logowanie", "Usuwanie konta", 0));
        radioButton_2->setText(QApplication::translate("Logowanie", "Zmiana klucza", 0));
        radioButton_4->setText(QApplication::translate("Logowanie", "Blokowanie konta", 0));
    } // retranslateUi

};

namespace Ui {
    class Logowanie: public Ui_Logowanie {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGOWANIE_H
