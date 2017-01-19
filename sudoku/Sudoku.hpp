// Copyright 2017 Timothy Oltjenbruns

#ifndef SUDOKU_SUDOKU_HPP_
#define SUDOKU_SUDOKU_HPP_

/// A Sudoku puzzle
class Sudoku {
 public:
  typedef unsigned int size_t;
  typedef int value_t;

 protected:
  /// @brief 9 by 9 array storing the puzzle state
  /// Values are stored left to right then top to bottom and default to 0
  value_t _puzzle[9][9];

 public:
  /// Instantiates a Sudoku @p _puzzle with every value marked as unset (0)
  Sudoku();

  /// Set @p _puzzle value for specified position
  /// @param[in] row [0...8] Top to bottom
  /// @param[in] column [0...8] Left to right
  /// @param[in] value [0...9] Sudoku value to set.
  ///            0 represents a default or unset value.
  void set(size_t row, size_t column, value_t value);

  /// Get @p _puzzle value for specified position
  /// @param[in] row [0...8] Top to bottom
  /// @param[in] column [0...8] Left to right
  /// @returns   Sudoku value at specified position.
  ///            0 represents a default or unset value.
  value_t get(size_t row, size_t column) const;

  /// Searches a row of the @p _puzzle for a value
  /// @param[in] row [0...8] Top to bottom, indicating row to search
  /// @param[in] value [0...9] Sudoku value to search for.
  ///            0 represents a default or unset value.
  /// @returns   Whether the @p value was found in the @p row
  bool containsRow(size_t row, value_t value) const;

  /// Searches a column of the @p _puzzle for a value
  /// @param[in] column [0...8] Left to right, indicating column to search
  /// @param[in] value [0...9] Sudoku value to search for.
  ///            0 represents an default or unset value.
  /// @returns   Whether the @p value was found in the @p column
  bool containsColumn(size_t column, value_t value) const;

  /// Searches a grid of the @p _puzzle for a value
  /// @param[in] grid [0...8] Left to right then top to bottom, indicating grid to search
  /// @param[in] value [0...9] Sudoku value to search for.
  ///            0 represents an default or unset value.
  /// @returns   Whether the @p value was found in the @p grid
  bool containsGrid(size_t grid, value_t value) const;

  /// Determines if this @p _puzzle contains the same values as the other @p _puzzle
  /// @param[in] other Reference to another puzzle
  /// @returns Whether the other @p _puzzle's values match this one's
  bool equal(const Sudoku& other) const;

  /// Determines if this @p _puzzle contains the same values as the other @p _puzzle
  /// @param[in] other Reference to another puzzle
  /// @returns Whether the other @p _puzzle's values match this one's
  bool operator==(const Sudoku& other) const;
};

#endif  // SUDOKU_SUDOKU_HPP_
