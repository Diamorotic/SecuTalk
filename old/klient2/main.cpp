#include "mainwindow.h"
#include <QApplication>

#include <iostream>
#include <fstream>

int main(int argc, char *argv[])
{
    createKeys();
//    encrypt();
//    decrypt();


    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
