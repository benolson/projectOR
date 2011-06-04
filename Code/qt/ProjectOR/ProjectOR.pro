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
    glwidget.cpp \
    imageGrabber.cpp \
    screenshot.cpp \
    screengrabber.cpp \
    geometriccalibration.cpp \
    vector2.cpp

HEADERS  += \
    glwidget.h \
    imageGrabber.h \
    screengrabber.h \
    screenshot.h \
    geometriccalibration.h \
    vector2.h
