cmake_minimum_required(VERSION 3.8)
project(Lab3)

set(CMAKE_CXX_STANDARD 17)


set(SOURCE_FILES main.cpp Grid.h UniformGrid.h Interpolate.h Lagrange.h functions.h ChebyshevGrid.h)
add_executable(Lab3 ${SOURCE_FILES})