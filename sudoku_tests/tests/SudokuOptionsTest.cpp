// Copyright 2017 Timothy Oltjenbruns

#include <fstream>
#include <SudokuOptions.hpp>
#include "gtest/gtest.h"

TEST(SudokuOptionsTest, SolveEasy133) {
  Sudoku puzzle;
  Sudoku solution;
  std::ifstream file;
  file.open("../../puzzles/easy/133.pzl.txt");
  ASSERT_TRUE(file.is_open());
  file >> puzzle;
  file.close();
  file.open("../../puzzles/easy/133.sol.pzl.txt");
  ASSERT_TRUE(file.is_open());
  file >> solution;
  file.close();
  SudokuOptions solved(puzzle);
  EXPECT_EQ(55, solved.solve());
  EXPECT_EQ(0, solved.diff(solution));
}

TEST(SudokuOptionsTest, SolveEasy134) {
  Sudoku puzzle;
  Sudoku solution;
  std::ifstream file;
  file.open("../../puzzles/easy/134.pzl.txt");
  ASSERT_TRUE(file.is_open());
  file >> puzzle;
  file.close();
  file.open("../../puzzles/easy/134.sol.pzl.txt");
  ASSERT_TRUE(file.is_open());
  file >> solution;
  file.close();
  SudokuOptions solved(puzzle);
  EXPECT_EQ(53, solved.solve());
  EXPECT_EQ(0, solved.diff(solution));
}
