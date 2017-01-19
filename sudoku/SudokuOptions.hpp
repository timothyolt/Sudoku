// Copyright 2017 Timothy Oltjenbruns

#ifndef SUDOKU_SUDOKUOPTIONS_HPP_
#define SUDOKU_SUDOKUOPTIONS_HPP_

#include "Sudoku.hpp"

class SudokuOptions : Sudoku {
 private:
  /// Node for creating a linked list of @p _options at a @p _puzzle position
  class ValueNode {
   public:
    Sudoku::value_t value;
    ValueNode* next;

    /// Creates a node with @p value and @p next
    ValueNode(value_t value, ValueNode* next) :
        value(value),
        next(next) {}

    /// Removes and frees all child nodes
    ~ValueNode();

    /// Remove node and free memory in place
    /// @param[in] target [not null] Node to remove and delete
    /// @returns The node held by @p next on @p target
    static ValueNode* remove(ValueNode* target);
  };

  /// Array holding linked lists of @p value_t corresponding to positions of @p _puzzle
  ValueNode* _options[9][9];

 public:
  /// Creates a blank Sudoku puzzle with empty @p options
  SudokuOptions();

  /// Removes and deletes all options
  ~SudokuOptions();

  /// Add puzzle value to the options for specified position.
  /// @post If the value already exists in the options, a duplicate will not be added.
  /// @param[in] row [0...8] Top to bottom
  /// @param[in] column [0...8] Left to right
  /// @param[in] value [1...9] Sudoku value to add.
  void add(size_t row, size_t column, value_t value);

  /// Remove puzzle value from the options for specified position
  /// @post If the value does not exist in the options, nothing will happen.
  /// @param[in] row [0...8] Top to bottom
  /// @param[in] column [0...8] Left to right
  /// @param[in] value [1...9] Sudoku value to remove.
  void remove(size_t row, size_t column, value_t value);

  /// Copies the single @p option at a location and sets it to the value on the @p puzzle
  /// @pre There must only be only one option at the location.
  /// @pre The value at the location must be unset or default (0).
  /// @param[in] row [0...8] Top to bottom
  /// @param[in] column [0...8] Left to right
  void finalize(size_t row, size_t column);

  /// Searches a row of the puzzle for a value
  /// @param[in] row [0...8] Top to bottom
  /// @param[in] column [0...8] Left to right
  /// @param[in] value [1...9] Sudoku value to search for.
  /// @returns   Whether the @p value was found in the @p _options at @p row and @p column
  bool containsOptions(size_t row, size_t column, value_t value) const;
};

#endif  // SUDOKU_SUDOKUOPTIONS_HPP_
