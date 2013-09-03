CONFIG -= QT
QT -= core gui

TEMPLATE = lib
TARGET = rooms
DEPENDPATH += . src lib/tinyxml
INCLUDEPATH += . src lib/tinyxml
OBJECTS_DIR = ./build
MOC_DIR = ./build
CONFIG += staticlib
LIBS += -lpython2.6

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
           gui.h \
           pythonvm.h \
           tinystr.h \
           tinyxml.h \
           versioning.h
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
           src/pythonvm.cpp \
           src/pythonapi.cpp \
           lib/tinyxml/tinystr.cpp \
           lib/tinyxml/tinyxml.cpp \
           lib/tinyxml/tinyxmlerror.cpp \
           lib/tinyxml/tinyxmlparser.cpp \
           src/versioning.cpp
