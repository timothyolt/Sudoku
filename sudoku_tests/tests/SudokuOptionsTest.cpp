// Copyright 2017 Timothy Oltjenbruns

#include <SudokuOptions.hpp>
#include <fstream>
#include "gtest/gtest.h"

class SudokuOptionsTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    _sudoku = SudokuOptions();
  }
  virtual void TearDown() {
    _sudoku.~SudokuOptions();
  }
  SudokuOptions _sudoku;
};

TEST_F(SudokuOptionsTest, SolveEasy133) {
  Sudoku puzzle;
  std::ifstream file;
  file.open("../../puzzles/easy/133.pzl.txt");
  ASSERT_TRUE(file.is_open());
  file >> puzzle;
  file.close();
  std::cout << puzzle << std::endl;
  SudokuOptions solved(puzzle);
  solved.solve();
  std::cout << solved << std::endl;
}
