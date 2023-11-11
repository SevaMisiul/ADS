cmake_minimum_required(VERSION 3.26)
project(Treelab)

set(CMAKE_CXX_STANDARD 23)

add_executable(Treelab src/task.cpp)

add_executable(Test tests/test.cpp)

target_include_directories(Treelab PRIVATE src)

target_include_directories(Test PRIVATE src)