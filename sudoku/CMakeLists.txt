cmake_minimum_required(VERSION 3.6)
project(sudoku)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Sudoku.hpp SudokuOptions.hpp Sudoku.cpp SudokuOptions.cpp OptionsSolver.cpp OptionsSolver.hpp)

add_library(sudoku STATIC ${SOURCE_FILES})