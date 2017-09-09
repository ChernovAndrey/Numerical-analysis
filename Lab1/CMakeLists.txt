cmake_minimum_required(VERSION 3.6)
project(Lab1)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp gauss.cpp sourceMatrices.cpp workWithConsole.cpp workWithConsole.h sourceMatrices.h gauss.h QR.cpp QR.h)
add_executable(Lab1 ${SOURCE_FILES})