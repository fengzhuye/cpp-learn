cmake_minimum_required(VERSION 2.8.2 FATAL_ERROR)
project("underscore_name")
#ADD_DEFINITIONS(
#    -std=c++11 # Or -std=c++0x
#    -Wall
    # Other flags
#)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_executable(main main.cpp)
#add_executable(main2 main2.cpp)
