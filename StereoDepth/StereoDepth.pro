#-------------------------------------------------
#
# Project created by QtCreator 2016-01-08T09:15:31
#
#-------------------------------------------------

QT       -= core gui

TARGET = StereoDepth
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++14
CONFIG += create_prl
CONFIG += link_prl

SOURCES += StereoDepth.cpp \
    cvmethods.cpp

HEADERS += StereoDepth.h

LIBS += -lopencv_calib3d -lopencv_video -lopencv_imgproc -lopencv_highgui -lopencv_core

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
