
cmake_minimum_required(VERSION 3.10)

project(Syntax)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Operator operator.cpp)
add_executable(Condition condition.cpp)