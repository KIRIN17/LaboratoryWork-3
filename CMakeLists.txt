cmake_minimum_required(VERSION 3.17)
project(GoogleTests)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

add_executable(GoogleTests main.cpp Tests/BinaryTree.cpp Tests/BinaryTree.h Tests/test.cpp)
target_link_libraries(GoogleTests gtest gtest_main)
