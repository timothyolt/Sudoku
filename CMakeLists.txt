cmake_minimum_required(VERSION 3.6)
project(Sudoku)

set(CMAKE_CXX_STANDARD 11)

if(CMAKE_BUILD_TYPE STREQUAL "Coverage")
    if(NOT CMAKE_COMPILER_IS_GNUCXX)
        MESSAGE(FATAL_ERROR "Gcc compiler required for coverage results")
    endif()
    # disable optimization and enable coverage
    set(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
    set(CMAKE_C_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
endif()

add_executable(run_sudoku main.cpp)

include_directories(sudoku)

add_subdirectory(sudoku)
add_subdirectory(sudoku_tests)

target_link_libraries(run_sudoku sudoku)