cmake_minimum_required(VERSION 3.27)
project(tinker)

set(CMAKE_CXX_STANDARD 17)
enable_testing()
find_package(GTest CONFIG REQUIRED)
find_package(glog CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

include_directories(.)

add_executable(tinker
        main.cpp
        exercise/sort.cpp
        exercise/sort.h
)
target_link_libraries(tinker PRIVATE fmt::fmt)

add_executable(tinker_unittest unittest/unittest_grammar.cpp)
target_link_libraries(tinker_unittest PRIVATE GTest::gtest GTest::gtest_main glog::glog fmt::fmt-header-only)
