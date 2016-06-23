CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(SERVER)
#Set project root directory.    
SET(PROJECT_ROOT_DIRECTORY "/home/godman/webpoj/cppserver")

ADD_SUBDIRECTORY(./core)

MESSAGE(STATUS "Root Project dir :" ${PROJECT_BINARY_DIR})
MESSAGE(STATUS "Root source Project dir :" ${CMAKE_SOURCE_DIR})
