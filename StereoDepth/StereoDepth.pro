#-------------------------------------------------
#
# Project created by QtCreator 2016-01-08T09:15:31
#
#-------------------------------------------------

QT       -= core gui

TARGET = StereoDepth
TEMPLATE = lib
CONFIG += staticlib

SOURCES += StereoDepth.cpp

HEADERS += StereoDepth.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
