cmake_minimum_required(VERSION 3.8)
project(ParallelMergeSort)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp main.h MerseSort.cpp)
add_executable(ParallelMergeSort ${SOURCE_FILES})

set (CMAKE_CXX_FLAGS "-fopenmp")