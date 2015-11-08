cmake_minimum_required(VERSION 3.3)
project(P1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp driver4scanner.cpp driver4scanner.h scanner.cpp scanner.h token.h)
add_executable(P1 ${SOURCE_FILES})