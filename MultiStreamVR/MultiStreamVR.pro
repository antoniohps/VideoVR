#-------------------------------------------------
#
# Project created by QtCreator 2016-01-05T12:03:04
#
#-------------------------------------------------

QT       -= core gui

TARGET = MultiStreamVR
TEMPLATE = lib

CONFIG += c++14
CONFIG += staticlib
CONFIG += create_prl
CONFIG += link_prl

SOURCES += MultiStreamVREnvironment.cpp \
    MSVRStream.cpp \
    MSVRStereoImage.cpp \
    MSVRPinholeCamera.cpp \
    MSVRCamera.cpp

HEADERS += MultiStreamVREnvironment.h \
    MSVRStream.h \
    MSVRStereoImage.h \
    MSVRPinholeCamera.h \
    MSVRCamera.h


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../StereoDepth/release/ -lStereoDepth
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../StereoDepth/debug/ -lStereoDepth
else:unix: LIBS += -L$$OUT_PWD/../StereoDepth/ -lStereoDepth

INCLUDEPATH += $$PWD/../StereoDepth $$PWD/../ImageProc
DEPENDPATH += $$PWD/../StereoDepth

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../StereoDepth/release/libStereoDepth.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../StereoDepth/debug/libStereoDepth.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../StereoDepth/release/StereoDepth.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../StereoDepth/debug/StereoDepth.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../StereoDepth/libStereoDepth.a

