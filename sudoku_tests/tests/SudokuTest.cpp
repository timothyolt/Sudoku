// Copyright 2017 Timothy Oltjenbruns

#include <Sudoku.hpp>
#include "gtest/gtest.h"

class SudokuTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    _sudoku = Sudoku();
  }
  Sudoku _sudoku;
};

TEST_F(SudokuTest, Get) {
  // Test get function
  // All values should be zero, we have a blank puzzle
  for (auto i(0u); i < 9; ++i)
    for (auto j(0u); j < 9; ++j)
      ASSERT_EQ(0, _sudoku.get(i, j));
}

// Array bounds testing
TEST_F(SudokuTest, Set_ArrayBounds) {
  // Set all values to 9
  for (auto i(0u); i < 9; ++i)
    for (auto j(0u); j < 9; ++j)
      _sudoku.set(i, j, 9);
  // Make sure those values are actually 9
  for (auto i(0u); i < 9; ++i)
    for (auto j(0u); j < 9; ++j)
      ASSERT_EQ(9, _sudoku.get(i, j));
}

// Value bounds testing
TEST_F(SudokuTest, Set_ValueBounds) {
  for (auto i(0u); i < 9; ++i) {
    for (auto j(0u); j < 9; ++j) {
      ASSERT_DEATH(_sudoku.set(i, j, 10), "");
      ASSERT_DEATH(_sudoku.set(i, j, -1), "");
    }
  }
}

TEST_F(SudokuTest, ContainsRow) {
  for (auto i(0); i < 9; ++i) {
    for (auto j(0); j < 9; ++j) {
      ASSERT_DEATH(_sudoku.set(i, j, 10), "");
      ASSERT_DEATH(_sudoku.set(i, j, -1), "");
    }
  }
}
