#version
set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)

PROJECT(TEST_EVENTLIB)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
INCLUDE(../thirdpart/libevent/CMakeLists.txt)
#INCLUDE_DIRECTORIES(../thirdpart/libevent/include/)
ADD_COMPILE_OPTIONS(-g -Wall -std=c++11)
SET(SRC_LIST 
    src/main.cpp
    src/channel.cpp
    src/reactor.cpp
    src/cm_event_handler.cpp
    src/worker.cpp
    )
ADD_EXECUTABLE(demosvr ${SRC_LIST})
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
TARGET_LINK_LIBRARIES(demosvr event pthread)
