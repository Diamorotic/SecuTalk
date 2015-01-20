TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    main.cpp \
    RawData.cpp \
    sttp.cpp \
    controllerscetch.cpp

include(deployment.pri)
qtcAddDeployment()

DISTFILES +=

HEADERS += \
    deklaracje.hh \
    PrioritableRawData.h \
    RawData.h \
    sttp.h

