cmake_minimum_required(VERSION 3.8)
project(Monte_Carlo_parallel)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp)
add_executable(Monte_Carlo_parallel ${SOURCE_FILES})

set(CMAKE_CXX_FLAGS "-fopenmp")