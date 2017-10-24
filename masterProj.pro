#-------------------------------------------------
#
# Project created by QtCreator 2017-09-25T22:24:58
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = masterProj
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
#    graphitems.cpp \
#    backgrounditem.cpp \
    ipcgateway.cpp \
    fileparser.cpp \
    platform_init.cpp \
    diagramview.cpp \
    platform_ui.cpp \
    landmark.cpp \
    obstacle.cpp \
    link.cpp

HEADERS += \
#    graphitems.h \
#    backgrounditem.h \
    platform.h \
    ipcgateway.h \
    fileparser.h \
    datatype.h \
    diagramview.h \
    landmark.h \
    obstacle.h \
    link.h
