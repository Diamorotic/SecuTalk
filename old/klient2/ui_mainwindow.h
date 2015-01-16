/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionPolaczenie;
    QAction *actionLogowanie;
    QAction *actionZarejestruj_konto;
    QAction *actionZablokuj_konto;
    QAction *actionUsu_konto;
    QAction *actionWyloguj;
    QAction *actionSzukaj;
    QAction *actionZmie_klucz_publiczny;
    QWidget *centralWidget;
    QTableView *Znajomi;
    QMenuBar *menuBar;
    QMenu *menuUstawienia;
    QMenu *menuU_ytkownik;
    QMenu *menuZnajomi;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(370, 345);
        actionPolaczenie = new QAction(MainWindow);
        actionPolaczenie->setObjectName(QStringLiteral("actionPolaczenie"));
        actionLogowanie = new QAction(MainWindow);
        actionLogowanie->setObjectName(QStringLiteral("actionLogowanie"));
        actionZarejestruj_konto = new QAction(MainWindow);
        actionZarejestruj_konto->setObjectName(QStringLiteral("actionZarejestruj_konto"));
        actionZablokuj_konto = new QAction(MainWindow);
        actionZablokuj_konto->setObjectName(QStringLiteral("actionZablokuj_konto"));
        actionUsu_konto = new QAction(MainWindow);
        actionUsu_konto->setObjectName(QStringLiteral("actionUsu_konto"));
        actionWyloguj = new QAction(MainWindow);
        actionWyloguj->setObjectName(QStringLiteral("actionWyloguj"));
        actionSzukaj = new QAction(MainWindow);
        actionSzukaj->setObjectName(QStringLiteral("actionSzukaj"));
        actionZmie_klucz_publiczny = new QAction(MainWindow);
        actionZmie_klucz_publiczny->setObjectName(QStringLiteral("actionZmie_klucz_publiczny"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Znajomi = new QTableView(centralWidget);
        Znajomi->setObjectName(QStringLiteral("Znajomi"));
        Znajomi->setGeometry(QRect(9, 9, 351, 301));
        QFont font;
        font.setPointSize(10);
        Znajomi->setFont(font);
        Znajomi->setFrameShape(QFrame::NoFrame);
        Znajomi->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        Znajomi->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        Znajomi->setEditTriggers(QAbstractItemView::DoubleClicked);
        Znajomi->setAlternatingRowColors(false);
        Znajomi->setSelectionMode(QAbstractItemView::SingleSelection);
        Znajomi->setSelectionBehavior(QAbstractItemView::SelectRows);
        Znajomi->horizontalHeader()->setVisible(false);
        Znajomi->verticalHeader()->setVisible(false);
        Znajomi->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 370, 26));
        menuUstawienia = new QMenu(menuBar);
        menuUstawienia->setObjectName(QStringLiteral("menuUstawienia"));
        menuU_ytkownik = new QMenu(menuBar);
        menuU_ytkownik->setObjectName(QStringLiteral("menuU_ytkownik"));
        menuZnajomi = new QMenu(menuBar);
        menuZnajomi->setObjectName(QStringLiteral("menuZnajomi"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuUstawienia->menuAction());
        menuBar->addAction(menuU_ytkownik->menuAction());
        menuBar->addAction(menuZnajomi->menuAction());
        menuUstawienia->addAction(actionPolaczenie);
        menuU_ytkownik->addAction(actionLogowanie);
        menuU_ytkownik->addAction(actionZablokuj_konto);
        menuU_ytkownik->addAction(actionUsu_konto);
        menuU_ytkownik->addAction(actionZmie_klucz_publiczny);
        menuU_ytkownik->addAction(actionWyloguj);
        menuU_ytkownik->addSeparator();
        menuU_ytkownik->addAction(actionZarejestruj_konto);
        menuZnajomi->addAction(actionSzukaj);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Komunikator", 0));
        actionPolaczenie->setText(QApplication::translate("MainWindow", "Po\305\202\304\205czenie", 0));
        actionLogowanie->setText(QApplication::translate("MainWindow", "Zaloguj", 0));
        actionZarejestruj_konto->setText(QApplication::translate("MainWindow", "Zarejestruj konto", 0));
        actionZablokuj_konto->setText(QApplication::translate("MainWindow", "Zablokuj konto", 0));
        actionUsu_konto->setText(QApplication::translate("MainWindow", "Usu\305\204 konto", 0));
        actionWyloguj->setText(QApplication::translate("MainWindow", "Wyloguj", 0));
        actionSzukaj->setText(QApplication::translate("MainWindow", "Szukaj", 0));
        actionZmie_klucz_publiczny->setText(QApplication::translate("MainWindow", "Zmie\305\204 klucz publiczny", 0));
        menuUstawienia->setTitle(QApplication::translate("MainWindow", "Ustawienia", 0));
        menuU_ytkownik->setTitle(QApplication::translate("MainWindow", "U\305\274ytkownik", 0));
        menuZnajomi->setTitle(QApplication::translate("MainWindow", "Znajomi", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
