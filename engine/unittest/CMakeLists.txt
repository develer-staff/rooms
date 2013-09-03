cmake_minimum_required(VERSION 2.8.9)
project(test)

include(ExternalProject)
ExternalProject_Add(libcppunit
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../lib/cppunit
    CONFIGURE_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/../lib/cppunit/configure "LDFLAGS=-ldl" --prefix=${CMAKE_CURRENT_SOURCE_DIR}/libcppunit
    BUILD_COMMAND ${MAKE})

include_directories(${CMAKE_CURRENT_SOURCE_DIR} "../frontend" "../src" "../lib/tinyxml" "./libcppunit/include")
link_directories("./libcppunit/lib")

set(src main.cpp
    enginetests.cpp
    ../src/action.cpp
    ../src/dialog.cpp
    ../src/area.cpp
    ../src/engine.cpp
    ../src/event.cpp
    ../src/eventsmanager.cpp
    ../src/item.cpp
    ../src/log.cpp
    ../src/room.cpp
    ../src/roomsmanager.cpp
    ../src/roomsreader.cpp
    ../src/gui.cpp
    ../src/versioning.cpp
    ../lib/tinyxml/tinystr.cpp
    ../lib/tinyxml/tinyxml.cpp
    ../lib/tinyxml/tinyxmlerror.cpp
    ../lib/tinyxml/tinyxmlparser.cpp)

add_executable(test ${src})
target_link_libraries(test cppunit)
