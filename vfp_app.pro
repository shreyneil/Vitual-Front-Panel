#-------------------------------------------------
#
# Project created by QtCreator 2018-11-26T10:36:12
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = vfp_app
TEMPLATE = app


SOURCES += main.cpp\
        mainview.cpp \
        setuptab.cpp \
    startup.cpp \
    utils.cpp \
    settings.cpp \
    provider.cpp \
    intsocket.cpp \
    instrument.cpp \
    setupviewmangaer.cpp \
    controltab.cpp \
    ctviewmanager.cpp \
    aboutbox.cpp

HEADERS  += mainview.h \
        setuptab.h \
    startup.h \
    utils.h \
    settings.h \
    provider.h \
    intsocket.h \
    instrument.h \
    setupviewmangaer.h \
    controltab.h \
    ctviewmanager.h \
    aboutbox.h

FORMS    += mainview.ui \
        setuptab.ui \
    controltab.ui \
    aboutbox.ui

QMAKE_CXXFLAGS += -std=c++11

RESOURCES += \
    VfpResources.qrc
