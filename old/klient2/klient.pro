#-------------------------------------------------
#
# Project created by QtCreator 2014-05-13T21:01:48
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT 		 += xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = klient2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    connection.cpp \
    logowanie.cpp \
    rejestracja.cpp \
    find_friends.cpp \
    rozmowa.cpp \
    model.cpp \
    read_write_socket.cpp \
    protocol.cpp \
    security.cpp \
    sendThread.cpp \
    watcher.cpp


HEADERS  += mainwindow.h \
    connection.h \
    logowanie.h \
    rejestracja.h \
    deklaracje.h \
    find_friends.h \
    rozmowa.h \
    model.h \
    read_write_socket.h \
    model.h \
    protocol.h \
    security.h \
    sendThread.h \
    watcher.h


FORMS    += mainwindow.ui \
    connection.ui \
    logowanie.ui \
    rejestracja.ui \
    find_friends.ui \
    rozmowa.ui

LIBS += C:\Qt\Tools\mingw482_32\i686-w64-mingw32\lib\libws2_32.a

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../cryptopp/release/ -lcryptopp
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../cryptopp/debug/ -lcryptopp

INCLUDEPATH += $$PWD/../../../../../cryptoppa
DEPENDPATH += $$PWD/../../../../../cryptoppa

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../cryptoppa/release/ -lcryptopp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../cryptoppa/release/ -lcryptopp

INCLUDEPATH += $$PWD/../../../../../cryptopp
DEPENDPATH += $$PWD/../../../../../cryptopp
