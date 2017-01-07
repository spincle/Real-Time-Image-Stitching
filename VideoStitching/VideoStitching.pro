#-------------------------------------------------
#
# Project created by QtCreator 2016-02-14T19:53:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VideoStitching
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    MarkerSplash.cpp \
    Stitching.cpp

HEADERS  += MainWindow.h \
    MarkerSplash.h

FORMS    += MainWindow.ui

RC_ICONS = ./Res/AppIcon.ico

INCLUDEPATH += ../OpenCV/include

RESOURCES += \
    videostitching.qrc
