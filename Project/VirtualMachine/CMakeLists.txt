cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)

project(VirtualMachine)
#set(TEST_TARGET Tests)

#
# MAIN DIRECTORIES
#
set(BINARY_DIR  ${CMAKE_SOURCE_DIR}/bin)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(LIB_DIR     ${CMAKE_SOURCE_DIR}/lib)
set(SOURCE_DIR  ${CMAKE_SOURCE_DIR}/src)
set(TEMP_DIR    ${CMAKE_SOURCE_DIR}/temp)
#set(TEST_DIR    ${CMAKE_SOURCE_DIR}/test)

include_directories(${INCLUDE_DIR})
include_directories(${LIB_DIR})
include_directories(${SOURCE_DIR})
include_directories(${TEMP_DIR})
#include_directories(${TEST_DIR})

#
# GENERAL DEPENDENCIES
#
#add_subdirectory(${LIB_DIR}/gtest)
#include_directories(${LIB_DIR}/gtest/googletest/include)

file(GLOB_RECURSE HEADER_FILES  ${INCLUDE_DIR}/*.h)
file(GLOB_RECURSE LIBRARY_FILES ${LIB_DIR}/*.hpp)
file(GLOB_RECURSE SOURCE_FILES  ${SOURCE_DIR}/*.cpp)
#file(GLOB_RECURSE TEST_FILES    ${TEST_DIR}/*.cpp)

set(SOURCE_TESTS ${SOURCE_FILES})
list(REMOVE_ITEM SOURCE_TESTS ${SOURCE_DIR}/main.cpp)

#
# OUTPUT PATHS
#
set(EXECUTABLE_OUTPUT_PATH ${BINARY_DIR})
set(LIBRARY_OUTPUT_PATH    ${LIB_DIR})

if(WIN32)
    set(GCC_CXX_FLAGS ${GCC_CXX_FLAGS} "-static-libgcc -static-libstdc++ -static")
endif()

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES} ${LIBRARY_FILES})
#add_executable(${TEST_TARGET} EXCLUDE_FROM_ALL ${SOURCE_TESTS} ${HEADER_FILES} ${LIBRARY_FILES} ${TEST_FILES})

#target_link_libraries(${TEST_TARGET} gtest gtest_main)
