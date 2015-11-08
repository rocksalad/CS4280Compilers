cmake_minimum_required(VERSION 3.3)
project(P0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp buildtree.cpp buildtree.h traversals.cpp traversals.h node.h)
add_executable(P0 ${SOURCE_FILES})