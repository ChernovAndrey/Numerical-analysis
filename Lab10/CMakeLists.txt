cmake_minimum_required(VERSION 3.8)
project(Lab10)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp Equations.h Params.h Solve.h Var.h helping Method.h solveSystem SolveSingular.h MethodSingular.h)
add_executable(Lab10 ${SOURCE_FILES})