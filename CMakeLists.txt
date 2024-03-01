cmake_minimum_required(VERSION 3.27)
project(tinker)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(tinker
        main.cpp
        exercise/sort.cpp
        exercise/sort.h)
