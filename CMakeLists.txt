cmake_minimum_required(VERSION 3.28)
project(Assembler C)

set(CMAKE_C_STANDARD 90)

add_executable(Assembler main.c
        util.c
        main.h
        pre_proc.c
        linkedlist.c
        linkedlist.h
        hashtable.c
        hashtable.h
        pre_proc.h
        pre_proc.h
        util.h
        first_pass.c
        first_pass.h
        error_handle.c
        error_handle.h
)
