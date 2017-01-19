cmake_minimum_required(VERSION 3.6)
project(sudoku)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(sudoku_run main.cpp ${SOURCE_FILES})

include_directories(sudoku)

add_subdirectory(sudou)
add_subdirectory(sudoku_tests)

target_link_libraries(sudoku_run sudoku_tests)