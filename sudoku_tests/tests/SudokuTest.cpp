// Copyright 2017 Timothy Oltjenbruns

#include <Sudoku.hpp>
#include "gtest/gtest.h"

TEST(SudokuTest, TestBasic) {
  Sudoku a = Sudoku();
  Sudoku b = Sudoku();
  EXPECT_EQ(a, b);
}
