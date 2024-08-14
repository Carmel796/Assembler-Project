cmake_minimum_required(VERSION 3.28)
project(Assembler C)

set(CMAKE_C_STANDARD 90)

add_executable(Assembler Sources/main.c
        Sources/util.c
        Headers/main.h
        Sources/pre_proc.c
        Sources/linkedlist.c
        Headers/linkedlist.h
        Sources/hashtable.c
        Headers/hashtable.h
        Headers/pre_proc.h
        Headers/pre_proc.h
        Headers/util.h
        Sources/first_pass.c
        Headers/first_pass.h
        Sources/error_handle.c
        Headers/error_handle.h
        Sources/second_pass.c
        Headers/second_pass.h
)
