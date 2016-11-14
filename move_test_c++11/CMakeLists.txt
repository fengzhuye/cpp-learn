cmake_minimum_required(VERSION 2.8.2 FATAL_ERROR)
project("move_test_C++11")
ADD_DEFINITIONS(
    -std=c++11 # Or -std=c++0x
    # Other flags
)
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_executable(main move_test_c++11.cpp)
