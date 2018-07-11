cmake_minimum_required(VERSION 3.10)
project(osexperiment)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXE_LINKER_FLAGS -static)

add_executable(lab2 lab2.cpp lab2_PCB.cpp)
add_executable(lab3_1 lab3_1.cpp)
add_executable(lab3_2 lab3_2.cpp)
add_executable(lab4_1 lab4_1.cpp)
add_executable(lab4_2 lab4_2.cpp)