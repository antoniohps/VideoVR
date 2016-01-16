#-------------------------------------------------
#
# Project created by QtCreator 2016-01-05T12:03:04
#
#-------------------------------------------------

QT       -= core gui

TARGET = MultiStreamVR
TEMPLATE = lib
CONFIG += staticlib

SOURCES += MultiStreamVREnvironment.cpp

HEADERS += MultiStreamVREnvironment.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
