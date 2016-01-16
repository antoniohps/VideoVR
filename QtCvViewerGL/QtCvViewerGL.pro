#-------------------------------------------------
#
# Project created by QtCreator 2016-01-04T15:51:17
#
#-------------------------------------------------

QT       -= core gui

TARGET = QtCvViewerGL
TEMPLATE = lib

DEFINES += QTCVVIEWERGL_LIBRARY

SOURCES += qtcvviewergl.cpp

HEADERS += qtcvviewergl.h\
        qtcvviewergl_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
