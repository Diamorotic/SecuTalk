TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ../../../../../Users/Diamorotic/Desktop/Micha³ 16.01.15/RawData.cpp \
    ../../../../../Users/Diamorotic/Desktop/Micha³ 16.01.15/sttp.cpp \
    RawData.cpp \
    sttp.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    ../../../../../Users/Diamorotic/Desktop/Micha³ 16.01.15/ProritableRawData.h \
    ../../../../../Users/Diamorotic/Desktop/Micha³ 16.01.15/RawData.h \
    ../../../../../Users/Diamorotic/Desktop/Micha³ 16.01.15/sttp.h \
    ../../../../../Users/Diamorotic/Desktop/Micha³ 16.01.15/ProritableRawData.h \
    ProritableRawData.h \
    RawData.h \
    sttp.h

