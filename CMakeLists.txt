cmake_minimum_required(VERSION 3.6)
project(Sudoku)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake-modules-sonar")

if(CMAKE_BUILD_TYPE STREQUAL "Analysis")
    include(SonarAnalysis)
    ADD_TARGET_SONAR("Analysis" "sudoku" "sudoku_tests" "sudoku_tests/tests/run_tests")
endif()

add_executable(run_sudoku main.cpp)

include_directories(sudoku)

add_subdirectory(sudoku)
add_subdirectory(sudoku_tests)

target_link_libraries(run_sudoku sudoku)