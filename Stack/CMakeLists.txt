cmake_minimum_required(VERSION 3.20)
project(Stack)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Stack
        Main.cpp
        Math_expression.h
        TStack.h)

