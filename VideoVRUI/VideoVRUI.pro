#-------------------------------------------------
#
# Project created by QtCreator 2016-01-04T15:48:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VideoVRUI
TEMPLATE = app

CONFIG += c++14
CONFIG += link_prl

SOURCES += main.cpp\
        mainwindow.cpp \
    addstereoimage.cpp \
    streamintegrationdialog.cpp \
    matchnewstreamdialog.cpp

HEADERS  += mainwindow.h \
    addstereoimage.h \
    streamintegrationdialog.h \
    matchnewstreamdialog.h

FORMS    += mainwindow.ui \
    addstereoimage.ui \
    streamintegrationdialog.ui \
    matchnewstreamdialog.ui


DEPLIBS = MultiStreamVR StereoDepth ImageProc QtCvViewerGL

for(mlib,DEPLIBS) {

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../$$mlib/release/ -l$$mlib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../$$mlib/debug/ -l$$mlib
else:unix: LIBS += -L$$OUT_PWD/../$$mlib/ -l$$mlib

INCLUDEPATH += $$PWD/../$$mlib
DEPENDPATH += $$PWD/../$$mlib

}

RESOURCES += \
    icons.qrc
