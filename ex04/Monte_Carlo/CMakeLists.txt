cmake_minimum_required(VERSION 3.8)
project(Monte_Carlo)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp main.h)
add_executable(Monte_Carlo ${SOURCE_FILES})

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Link runTests with what we want to test and the GTest and pthread library
ADD_EXECUTABLE(run_unit_tests tests/gtest.cpp)
target_link_libraries(run_unit_tests ${GTEST_LIBRARIES} pthread)

