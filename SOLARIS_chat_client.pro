#-------------------------------------------------
#
# Project created by QtCreator 2015-02-06T13:51:35
#
#-------------------------------------------------

QT       += core gui network

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SOLARIS_chat_client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    connectdialog.cpp

HEADERS  += mainwindow.h \
    connectdialog.h

FORMS    += mainwindow.ui \
    connectdialog.ui
