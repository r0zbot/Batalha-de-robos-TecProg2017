cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)

project(VirtualMachine)

#
# MAIN DIRECTORIES
#
set(BINARY_DIR  ${CMAKE_SOURCE_DIR}/bin)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(LIB_DIR     ${CMAKE_SOURCE_DIR}/lib)
set(SOURCE_DIR  ${CMAKE_SOURCE_DIR}/src)
set(TEMP_DIR    ${CMAKE_SOURCE_DIR}/temp)
set(TEST_DIR    ${CMAKE_SOURCE_DIR}/test)

include_directories(${INCLUDE_DIR})
include_directories(${LIB_DIR})
include_directories(${SOURCE_DIR})
include_directories(${TEMP_DIR})
include_directories(${TEST_DIR})

#
# GENERAL DEPENDENCIES
#
file(GLOB HEADER_FILES ${INCLUDE_DIR}/*.h)
file(GLOB SOURCE_FILES ${SOURCE_DIR}/*.cpp)
file(GLOB TEST_FILES   ${TEST_DIR}/*.cpp)

#
# OUTPUT PATHS
#
set(EXECUTABLE_OUTPUT_PATH ${BINARY_DIR})
set(LIBRARY_OUTPUT_PATH    ${LIB_DIR})

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})
