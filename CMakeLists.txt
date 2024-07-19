cmake_minimum_required(VERSION 3.28)
project(Assembler C)

set(CMAKE_C_STANDARD 90)

add_executable(Assembler main.c
        func1.c
        header.h)
