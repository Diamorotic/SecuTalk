TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    RawData.cpp \
    SockNet.cpp \
    SockNetSet.cpp \
    sttp.cpp \
    thread_functions.cpp \
    KontrolerWejsciowy.cpp \
    KomunikatMiedzywatkowy.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    deklaracje.h \
    PrioritableRawData.h \
    RawData.h \
    SockNet.h \
    SockNetSet.h \
    sttp.h \
    KontrolerWejsciowy.h \
    KomunikatMiedzywatkowy.h

