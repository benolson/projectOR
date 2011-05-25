#-------------------------------------------------
#
# Project created by QtCreator 2011-05-23T14:30:02
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = ProjectOR
TEMPLATE = app

LIBS += -LC:\OpenCV2.1\lib -lcv210 -l cxcore210 -lcvaux210 -lhighgui210

INCLUDEPATH += "C:\OpenCV2.1\include\opencv"

SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    imageGrabber.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    imageGrabber.h
