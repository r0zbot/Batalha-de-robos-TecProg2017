cmake_minimum_required(VERSION 3.8)
project(VirtualMachine)

set(CMAKE_CXX_STANDARD 11)

#enable_testing()

include_directories("include")
include_directories("src")

set(SOURCE_FILES
        src/instruction.cpp
        src/machine.cpp)

set(HEADER_FILES
        include/instruction.h
        include/machine.h
        include/code.h)

#TODO: Implementar testes unitários usando CMake e CTest
#set(TEST_FILES
#        test/test_main.cpp)
#
#add_test(VirtualMachineTest test_main.exe arg1 arg2)

add_executable(VirtualMachine src/main.cpp ${SOURCE_FILES} ${HEADER_FILES})
add_executable(VirtualMachineTest test/test_main.cpp ${SOURCE_FILES} ${HEADER_FILES})