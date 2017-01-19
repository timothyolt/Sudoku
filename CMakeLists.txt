cmake_minimum_required(VERSION 3.6)
project(Sudoku)

set(CMAKE_CXX_STANDARD 11)

add_executable(run_sudoku main.cpp)

include_directories(sudoku)

add_subdirectory(sudoku)
add_subdirectory(sudoku_tests)

target_link_libraries(run_sudoku sudoku)