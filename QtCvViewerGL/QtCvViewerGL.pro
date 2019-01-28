#-------------------------------------------------
#
# Project created by QtCreator 2016-01-04T15:51:17
#
#-------------------------------------------------

QT       += opengl

TARGET = QtCvViewerGL
TEMPLATE = lib

CONFIG += staticlib c++14
CONFIG += create_prl

DEFINES += QTCVVIEWERGL_LIBRARY

SOURCES += qtcvviewergl.cpp

HEADERS += qtcvviewergl.h\
        qtcvviewergl_global.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ImageProc/release/ -lImageProc
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ImageProc/debug/ -lImageProc
else:unix: LIBS += -L$$OUT_PWD/../ImageProc/ -lImageProc

INCLUDEPATH += $$PWD/../ImageProc
DEPENDPATH += $$PWD/../ImageProc

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ImageProc/release/libImageProc.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ImageProc/debug/libImageProc.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ImageProc/release/ImageProc.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../ImageProc/debug/ImageProc.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../ImageProc/libImageProc.a
