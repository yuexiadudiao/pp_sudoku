cmake_minimum_required(VERSION 2.8)
project(sudoku)

add_definitions(-std=c++11 -w -O3 -march=native)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(testcase src/test.cpp)

add_executable(sudoku_pp src/sudoku_pp.cpp)

add_executable(sigsolver src/single_solver.cpp)

add_executable(sigloopsolver src/single_loop_solver.cpp)

#compare algorithem - dlx
add_executable(sudoku_dlx compare_algorithm/sudoku_dlx.cpp)

#compare algorithem - bf
add_executable(sudoku_bf compare_algorithm/sudoku_bf.cpp)
