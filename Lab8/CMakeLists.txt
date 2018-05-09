cmake_minimum_required(VERSION 3.8)
project(Lab8)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp Equations.h Params.h Solve.h Var.h helping)
add_executable(Lab8 ${SOURCE_FILES})