#-------------------------------------------------
#
# Project created by QtCreator 2014-10-05T23:30:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IPCameraViewer
TEMPLATE = app
CONFIG += debug

SOURCES += main.cpp\
        mainwindow.cpp \
    screen.cpp \
    viewsettings.cpp \
    videoplayer.cpp \
    view.cpp \
    vlcvideoplayer.cpp \
    vlcinstance.cpp

HEADERS  += mainwindow.h \
    screen.h \
    viewsettings.h \
    videoplayer.h \
    view.h \
    vlcvideoplayer.h \
    vlcinstance.h

FORMS    += mainwindow.ui \
    screen.ui \
    view.ui \
    viewsettings.ui \
    viewoverlay.ui

LIBS += -lvlc -lX11 -lqjson

QMAKE_CXXFLAGS += -std=c++11

include(../vendor/QtAwesome/QtAwesome.pri)
