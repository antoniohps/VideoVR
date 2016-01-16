#-------------------------------------------------
#
# Project created by QtCreator 2016-01-08T21:32:27
#
#-------------------------------------------------

QT       -= core gui

TARGET = ImageProc
TEMPLATE = lib
CONFIG += staticlib

SOURCES += imagebase.cpp

HEADERS += imagebase.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
