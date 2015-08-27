cmake_minimum_required(VERSION 2.8.2 FATAL_ERROR)
project("Inheritance")
ADD_DEFINITIONS(
    -std=c++11 # Or -std=c++0x
    -Wall
    -Wfatal-errors
    # Other flags
)
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_executable(main main.cpp car.cpp engine.cpp)
