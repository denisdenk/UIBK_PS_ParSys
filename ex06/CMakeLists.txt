cmake_minimum_required(VERSION 3.8)
project(ex06)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp)
add_executable(ex06 ${SOURCE_FILES})

#set(CMAKE_CXX_FLAGS "-fopenmp")