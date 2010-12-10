#-------------------------------------------------
#
# Project created by QtCreator 2010-12-09T17:05:19
#
#-------------------------------------------------

QT       += core gui

TARGET = RoomMaker
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    roomview.cpp \
    core/world.cpp \
    core/room.cpp \
    core/area.cpp \
    core/item.cpp

HEADERS  += mainwindow.h \
    roomview.h \
    core/world.h \
    core/room.h \
    core/area.h \
    core/item.h

FORMS    += mainwindow.ui
