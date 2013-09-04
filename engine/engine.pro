CONFIG -= QT
QT -= core gui

TEMPLATE = lib
TARGET = rooms
INCLUDEPATH += . src lib/tinyxml
OBJECTS_DIR = ./build
MOC_DIR = ./build
CONFIG += staticlib

!isEmpty(PYTHON_VERSION){
    DEFINES += WITH_PYTHON
    LIBS += -lpython$${PYTHON_VERSION}
    INCLUDEPATH += /usr/include/python$${PYTHON_VERSION}
    HEADERS += pythonvm.h
    SOURCES += src/pythonvm.cpp \
               src/pythonapi.cpp
}

# Input
HEADERS += src/action.h \
           src/area.h \
           src/engine.h \
           src/event.h \
           src/eventsmanager.h \
           src/item.h \
           src/log.h \
           src/room.h \
           src/roomsmanager.h \
           src/dialog.h \
           src/roomsreader.h \
           src/gui.h \
           lib/tinyxml/tinystr.h \
           lib/tinyxml/tinyxml.h \
           src/versioning.h
SOURCES += src/action.cpp \
           src/area.cpp \
           src/engine.cpp \
           src/event.cpp \
           src/eventsmanager.cpp \
           src/item.cpp \
           src/log.cpp \
           src/room.cpp \
           src/roomsmanager.cpp \
           src/dialog.cpp \
           src/roomsreader.cpp \
           src/gui.cpp \
           lib/tinyxml/tinystr.cpp \
           lib/tinyxml/tinyxml.cpp \
           lib/tinyxml/tinyxmlerror.cpp \
           lib/tinyxml/tinyxmlparser.cpp \
           src/versioning.cpp
