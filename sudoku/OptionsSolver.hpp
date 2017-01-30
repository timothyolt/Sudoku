// Copyright 2017 Timothy Oltjenbruns

#ifndef SUDOKU_OPTIONSSOLVER_HPP_
#define SUDOKU_OPTIONSSOLVER_HPP_

#include "Sudoku.hpp"
class OptionsSolver {
 public:
  static Sudoku solve(const Sudoku& puzzle);
};

#endif  // SUDOKU_OPTIONSSOLVER_HPP_
