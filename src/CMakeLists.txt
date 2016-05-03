cmake_minimum_required(VERSION 3.4)
project(banking-system)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp src/Address.cpp src/Address.h)
add_executable(banking-system ${SOURCE_FILES})