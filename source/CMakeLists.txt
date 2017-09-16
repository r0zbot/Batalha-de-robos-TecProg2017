cmake_minimum_required(VERSION 3.8)
project(source)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        instr.h
        maq.c
        maq.h
        motor.c
        pilha.c
        pilha.h)

add_executable(source ${SOURCE_FILES})