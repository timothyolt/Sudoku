// Copyright 2017 Timothy Oltjenbruns

#include "Sudoku.hpp"
#include <assert.h>
#include <algorithm>

Sudoku::Sudoku() :
    _puzzle {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
    }  { }

void Sudoku::set(Sudoku::size_t row, Sudoku::size_t column, Sudoku::value_t value) {
  assert(row >= 0 && row < 9);
  assert(column >= 0 && column < 9);
  assert(value >= 0 && value <= 9);
  _puzzle[row][column] = value;
}

Sudoku::value_t Sudoku::get(Sudoku::size_t row, Sudoku::size_t column) const {
  assert(row >= 0 && row < 9);
  assert(column >= 0 && column < 9);
  return _puzzle[row][column];
}

bool Sudoku::containsRow(Sudoku::size_t row, Sudoku::value_t value) const {
  assert(row >= 0 && row < 9);
  assert(value >= 0 && value <= 9);
  // Linear search a row
  for (auto i(0); i < 9; i++)
    if (_puzzle[row][i] == value)
      return true;
  return false;
}

bool Sudoku::containsColumn(Sudoku::size_t column, Sudoku::value_t value) const {
  assert(column >= 0 && column < 9);
  assert(value >= 0 && value <= 9);
  // Linear search a column
  for (auto i(0); i < 9; i++)
    if (_puzzle[i][column] == value)
      return true;
  return false;
}

bool Sudoku::containsGrid(Sudoku::size_t grid, Sudoku::value_t value) const {
  assert(grid >= 0 && grid < 9);
  assert(value >= 0 && value <= 9);
  // Linear search a grid
  // Wrap search top to bottom
  auto rowOffset(grid % 3);
  auto columnOffset(grid / 3);
  for (auto i(0); i < 9; i++)
    if (_puzzle[rowOffset + i % 3][columnOffset + i / 3] == value)
      return true;
  return false;
}

bool Sudoku::equal(const Sudoku& other) const {
  for (auto i(0); i < 9; i++)
    if (!std::equal(_puzzle[i], _puzzle[i] + 9, other._puzzle[i]))
      return false;
  return true;
}

bool Sudoku::operator==(const Sudoku& other) const {
  return equal(other);
}
