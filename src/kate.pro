#-------------------------------------------------
#
# Project created by QtCreator 2013-01-23T16:46:20
#
#-------------------------------------------------

QT       += core gui webkit script scripttools network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kate
TEMPLATE = app


SOURCES += main.cpp \
    jsapi/qtwidgets.cpp \
    kateengine.cpp \
    jsapi/wapper/qdialogwapper.cpp \
    htmlwindow.cpp

HEADERS  += \
    kateengine.h \
    jsapi/wapper/qdialogwapper.h \
    htmlwindow.h

FORMS    += \
    htmlwindow.ui
