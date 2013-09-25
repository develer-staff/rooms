QT += declarative

# Add more folders to ship with the application, here
folder_01.source = qml/qml-frontend
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

INCLUDEPATH += ../src ../lib/tinyxml
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

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    controller.cpp

HEADERS += \
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
    ../src/versioning.h \
    ../lib/tinyxml/tinystr.h \
    ../lib/tinyxml/tinyxml.h \
    controller.h

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

OTHER_FILES +=
