QT += widgets multimedia

TEMPLATE = app
TARGET = engine.exe

INCLUDEPATH += $$PWD/../src $$PWD/../lib/tinyxml
QMAKE_LIBDIR += ../
LIBS += -L. -lrooms 

!isEmpty(PYTHON_VERSION){
    DEFINES += WITH_PYTHON
    LIBS += -lpython$${PYTHON_VERSION}
    unix {
        INCLUDEPATH += /usr/include/python$${PYTHON_VERSION}
    } win32 {
        SUFFIX = $$replace(PYTHON_VERSION,\.,)
        INCLUDEPATH += C:/Python$${SUFFIX}/include
    }
}

# Input
HEADERS += drawdevice.h \
           ../src/action.h \
           ../src/area.h \
           ../src/engine.h \
           ../src/event.h \
           ../src/eventsmanager.h \
           ../src/item.h \
           ../src/log.h \
           ../src/room.h \
           ../src/roomsmanager.h \
           ../src/dialog.h \
           ../src/roomsreader.h \
           ../lib/tinyxml/tinystr.h \
           ../lib/tinyxml/tinyxml.h
SOURCES += drawdevice.cpp \
           main.cpp \
