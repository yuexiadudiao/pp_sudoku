cmake_minimum_required(VERSION 2.8)
project(sudoku)

add_definitions(-std=c++11 -O3 -march=native)

set(${BINARY_OUTPUT_PATH} ${PROJECT_BINARY_DIR}/bin)

include_directories(
${PROJECT_SOURCE_DIR}/include
)

add_executable(test
src/test.cpp
)
