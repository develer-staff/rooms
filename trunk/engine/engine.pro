TEMPLATE = lib
TARGET = rooms
DEPENDPATH += . src lib/tinyxml
INCLUDEPATH += . src lib/tinyxml
OBJECTS_DIR = ./build
MOC_DIR = ./build
CONFIG += staticlib

# Input
HEADERS += action.h \
           area.h \
           engine.h \
           event.h \
           eventsmanager.h \
           item.h \
           log.h \
           room.h \
           roomsmanager.h \
           dialog.h \
           roomsreader.h \
           tinystr.h \
           tinyxml.h
SOURCES += action.cpp \
           area.cpp \
           engine.cpp \
           event.cpp \
           eventsmanager.cpp \
           item.cpp \
           log.cpp \
           room.cpp \
           roomsmanager.cpp \
           dialog.cpp \
           roomsreader.cpp \
           tinystr.cpp \
           tinyxml.cpp \
           tinyxmlerror.cpp \
           tinyxmlparser.cpp
