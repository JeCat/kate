#-------------------------------------------------
#
# Project created by QtCreator 2013-01-23T16:46:20
#
#-------------------------------------------------

QT       += core gui webkit network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kate
TEMPLATE = app


SOURCES += main.cpp \
    htmlwindow.cpp \
    jsapi/scriptapi.cpp \
    screenshoter.cpp

HEADERS += \
    htmlwindow.h \
    jsapi/scriptapi.h \
    screenshoter.h

FORMS += \
    htmlwindow.ui \
    screenshoter.ui

