cmake_minimum_required(VERSION 3.6)
project(Sudoku)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Sudoku/main.cpp Sudoku/Sudoku.cpp Sudoku/Sudoku.hpp Sudoku/SudokuOptions.cpp Sudoku/SudokuOptions.hpp)
add_executable(Sudoku ${SOURCE_FILES})