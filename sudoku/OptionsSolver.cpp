// Copyright 2017 Timothy Oltjenbruns

#include <iostream>
#include "OptionsSolver.hpp"
#include "SudokuOptions.hpp"

Sudoku OptionsSolver::solve(const Sudoku& puzzle) {
  SudokuOptions optionsPuzzle(puzzle);
  int placed(0);
  for (int row = 0; row < 9; ++row) {
    for (int column = 0; column < 9; ++column) {
      if (optionsPuzzle.get(row, column) == 0) {
        for (int value = 1; value <= 9; ++value) {
          if (!optionsPuzzle.containsRow(row, value) &&
              !optionsPuzzle.containsColumn(column, value) &&
              !optionsPuzzle.containsGrid(row, column, value))
            optionsPuzzle.add(row, column, value);
        }
        if (optionsPuzzle.finalize(row, column))
          ++placed;
      }
    }
  }
  std::cout << "Placed " << placed << " numbers" << std::endl;
  return optionsPuzzle;
}
