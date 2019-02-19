#-------------------------------------------------
#
# Project created by QtCreator 2019-02-19T17:49:17
#
#-------------------------------------------------
include( $${PWD}/specialForQwt.pri )
CONFIG   += qwt
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = meshViewTest
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    datareader.cpp \
    spectrgl.cpp

HEADERS  += mainwindow.h \
    datareader.h \
    datastruct.h \
    spectrgl.h

FORMS    += mainwindow.ui
