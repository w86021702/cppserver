#version
set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)

PROJECT(TEST_EVENTLIB)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
INCLUDE(../thirdpart/libevent/CMakeLists.txt)
#INCLUDE(${PROJECT_BINARY_DIR}/../core/net/CMakeLists.txt)
#ADD_SUBDIRECTORY(../core/net/include/)
LINK_DIRECTORIES(${PROJECT_BINARY_DIR}/../core/net/lib/)
LINK_DIRECTORIES(${PROJECT_BINARY_DIR}/../core/net/lib64_debug/)
INCLUDE_DIRECTORIES(${PROJECT_BINARY_DIR}/../core/net/include/)
INCLUDE_DIRECTORIES(${PROJECT_BINARY_DIR}/../thirdpart/protobuf/src/)

#INCLUDE_DIRECTORIES(../thirdpart/libevent/include/)
ADD_COMPILE_OPTIONS(-g -Wall -std=c++11)
SET(SRC_LIST 
    ${PROJECT_BINARY_DIR}/src/main.cpp
    ${PROJECT_BINARY_DIR}/src/worker.cpp
    )
ADD_EXECUTABLE(demosvr ${SRC_LIST})
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
TARGET_LINK_LIBRARIES(demosvr event pthread corenet protobuf)


#make cli
SET(SRC_CLI
    ${PROJECT_BINARY_DIR}/src/democli/democli.cpp
    )
ADD_EXECUTABLE(democli ${SRC_CLI})

#make_rpcsvr
SET(SRC_RPC
    ${PROJECT_BINARY_DIR}/src/protomain.cpp
    )
ADD_EXECUTABLE(rpcsvr ${SRC_RPC})
TARGET_LINK_LIBRARIES(rpcsvr event pthread corenet protobuf)
#TARGET_LINK_LIBRARIES(rpcsvr pthread corenet protobuf)
