set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)

PROJECT(CORE_NET_LIB)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
ADD_COMPILE_OPTIONS(-g -Wall -std=c++11)

SET(SRC_LIST 
    src/channel.cpp
    src/reactor.cpp
    src/cm_event_handler.cpp
    src/acceptor.cpp
    src/client.cpp
    )
ADD_LIBRARY(corenet STATIC ${SRC_LIST})
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
