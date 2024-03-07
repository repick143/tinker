cmake_minimum_required(VERSION 3.27)
project(tinker)

set(CMAKE_CXX_STANDARD 17)
enable_testing()

find_package(GTest CONFIG REQUIRED)
find_package(glog CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

include_directories(.)

add_library(exercises exercise/sort.cpp
        exercise/unique_ptr.h
        exercise/Shape.h
        exercise/Circle.cpp
        exercise/Circle.h
        exercise/shared_ptr.h
        exercise/tp.h
        exercise/LruCache.cpp
        exercise/LruCache.h)
target_link_libraries(exercises PRIVATE fmt::fmt)

add_executable(tinker
        main.cpp
)
target_link_libraries(tinker PRIVATE exercises)

add_executable(tinker_unittest
        unittest/unittest_grammar.cpp
        unittest/unittest_sort.cpp)
target_link_libraries(tinker_unittest PRIVATE GTest::gtest GTest::gtest_main glog::glog fmt::fmt exercises)
