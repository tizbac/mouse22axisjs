#-------------------------------------------------
#
# Project created by QtCreator 2011-10-30T17:15:45
#
#-------------------------------------------------

QT       += core gui

TARGET = Mouse22AxisJoy
TEMPLATE = app


SOURCES += main.cpp\
        mouse2j.cpp \
    virtualjoystick.cpp \
    mouseposition.cpp

HEADERS  += mouse2j.h \
    virtualjoystick.h \
    mouseposition.h

FORMS    += mouse2j.ui


LIBS += -lXrandr
