#-------------------------------------------------
#
# Project created by QtCreator 2010-12-09T17:05:19
#
#-------------------------------------------------

QT += core gui

TARGET = RoomsMaker
TEMPLATE = app


SOURCES += main.cpp \
    mainwindow.cpp \
    wizard.cpp \
    roomview.cpp \
    core/world.cpp \
    core/room.cpp \
    core/area.cpp \
    core/item.cpp \
    core/roomsmodel.cpp \
    roomslist.cpp \
    arearect.cpp

HEADERS += mainwindow.h \
    wizard.h \
    roomview.h \
    core/world.h \
    core/room.h \
    core/area.h \
    core/item.h \
    core/roomsmodel.h \
    roomslist.h \
    arearect.h

FORMS += mainwindow.ui \
    wizard.ui
