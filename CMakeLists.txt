cmake_minimum_required(VERSION 3.4)
project(banking-system)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB SOURCE_FILES src/*.cpp src/*.h sqlite/*.cpp sqlite/*.h sqlite/sqlite3.c)
add_executable(banking-system ${SOURCE_FILES})