#-------------------------------------------------
#
# Project created by QtCreator 2017-06-02T16:09:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ModelView
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    nodeinfo.cpp \
    customtreeviewdelegate.cpp

HEADERS  += widget.h \
    nodeinfo.h \
    customtreeviewdelegate.h

FORMS    += widget.ui
