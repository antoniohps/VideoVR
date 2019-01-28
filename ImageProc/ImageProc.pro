#-------------------------------------------------
#
# Project created by QtCreator 2016-01-08T21:32:27
#
#-------------------------------------------------

QT       -= core gui

TARGET = ImageProc
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++14
CONFIG += create_prl

SOURCES += \
    CDImage.cpp \
    Image.cpp \
    Image-opencv.cpp

HEADERS += \
    CDImage.h \
    Image.h \
    apiconfig.hpp

DEFINES += USE_OPENCV
