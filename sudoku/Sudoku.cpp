// Copyright 2017 Timothy Oltjenbruns

#include "Sudoku.hpp"
#include <assert.h>
#include <algorithm>
#include <iostream>

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

Sudoku::Sudoku(const Sudoku &copy) {
  for (auto i(0); i < 9; i++)
    std::copy(copy._puzzle[i], copy._puzzle[i] + 9, _puzzle[i]);
}

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
  for (auto column(0); column < 9; column++)
    if (_puzzle[row][column] == value)
      return true;
  return false;
}

bool Sudoku::containsColumn(Sudoku::size_t column, Sudoku::value_t value) const {
  assert(column >= 0 && column < 9);
  assert(value >= 0 && value <= 9);
  // Linear search a column
  for (auto row(0); row < 9; row++)
    if (_puzzle[row][column] == value)
      return true;
  return false;
}

bool Sudoku::containsGrid(Sudoku::size_t grid, Sudoku::value_t value) const {
  assert(grid >= 0 && grid < 9);
  assert(value >= 0 && value <= 9);
  // Linear search a grid
  // Wrap search top to bottom
  auto rowOffset((grid / 3) * 3);
  auto columnOffset((grid % 3) * 3);
  for (auto i(0); i < 9; i++)
    if (_puzzle[rowOffset + i / 3][columnOffset + i % 3] == value)
      return true;
  return false;
}

bool Sudoku::containsGrid(Sudoku::size_t row, Sudoku::size_t column, Sudoku::value_t value) const {
  return containsGrid((row / 3 * 3) + column / 3, value);
}

int Sudoku::diff(const Sudoku& other) const {
  int diff(0);
  for (auto row(0); row < 9; ++row)
    for (auto column(0); column < 9; ++column)
      if (get(row, column) != 0 && other.get(row, column) != 0
          && get(row, column) != other.get(row, column))
        ++diff;
  return diff;
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

std::ostream &operator<<(std::ostream &os, const Sudoku &sudoku) {
  for (auto row(0); row < 9; row++) {
    // Stream a horizontal rule every 3 rows
    if (row % 3 == 0)
      Sudoku::streamHRule(os, 25);
    for (auto column(0); column < 9; column++) {
      // Stream a vertical rule every 3 columns
      if (column % 3 == 0)
        os << "| ";
      // Stream the puzzle values themselves
      os << sudoku.get(row, column) << ' ';
      // Stream final vertical rule
      if (column == 8)
        os << '|';
    }
    os << std::endl;
    // Stream final horizontal rule
    if (row == 8)
      Sudoku::streamHRule(os, 25);
  }
  return os;
}

void Sudoku::streamHRule(std::ostream &os, int length) {
  for (auto column(0); column < length; column++)
    os << '-';
  os << std::endl;
}

std::istream &operator>>(std::istream &is, Sudoku &sudoku) {
  // 126 chosen as a reasonable max line size
  // a line should contain either no numbers or exactly 9 numbers, and up to 13 * 9 junk characters
  char line[126];
  int numLine[9];
  int row = 0;
  int n = 0;
  while (row < 9) {
    // clear line array with non-digits
    for (auto i(0); i < 126; i++)
      line[i] = 'x';
    is.getline(line, 126);
    n = 0;
    // filer out junk
    for (auto i(0); i < 126; i++)
      if (isdigit(line[i]))
        // offset char to digit
        numLine[n++] = line[i] - '0';
    // range checking
    if (n == 0) continue;
    if (n < 9) throw std::underflow_error("Too few digits on a line. Must be exactly 0 or 9.");
    if (n > 9) throw std::overflow_error("Too many digits on a line. Must be exactly 0 or 9.");
    if (n == 9) {
      // set sudoku line
      for (auto column(0); column < 9; column++)
        sudoku.set(row, column, numLine[column]);
      row++;
    }
  }
  return is;
}
