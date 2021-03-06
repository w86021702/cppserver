set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)

PROJECT(CORE_NET_LIB)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
ADD_COMPILE_OPTIONS(-g -Wall -std=c++11)

#INCLUDE_DIRECTORIES(${PROJECT_ROOT_DIRECTORY}/core/net/)
INCLUDE_DIRECTORIES(${PROJECT_BINARY_DIR}/src/)
INCLUDE_DIRECTORIES(${PROJECT_BINARY_DIR}/src/pbrpc/)
INCLUDE_DIRECTORIES(${PROJECT_BINARY_DIR}/src/log/)

SET(SRC_LIST 
    ${PROJECT_BINARY_DIR}/src/channel.cpp
    ${PROJECT_BINARY_DIR}/src/reactor.cpp
    ${PROJECT_BINARY_DIR}/src/cm_event_handler.cpp
    ${PROJECT_BINARY_DIR}/src/acceptor.cpp
    ${PROJECT_BINARY_DIR}/src/client.cpp
    ${PROJECT_BINARY_DIR}/src/request.cpp
    ${PROJECT_BINARY_DIR}/src/pbrpc/pb_ex.pb.cc
    ${PROJECT_BINARY_DIR}/src/pbrpc/httpserver.cpp
    ${PROJECT_BINARY_DIR}/src/pbrpc/pbrpcserver.cpp
    ${PROJECT_BINARY_DIR}/src/pbrpc/pbrpcclient.cpp
    ${PROJECT_BINARY_DIR}/src/pbrpc/rpccontrol.cpp
    ${PROJECT_BINARY_DIR}/src/log/logmgr.cpp
    )

MESSAGE(STATUS "src list dir :" ${SRC_LIST})
ADD_LIBRARY(corenet STATIC ${SRC_LIST})
TARGET_LINK_LIBRARIES(corenet pthread corenet protobuf)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

MESSAGE(STATUS "Net Project dir :" ${PROJECT_BINARY_DIR})
MESSAGE(STATUS "Net source Project dir :" ${CMAKE_SOURCE_DIR})
