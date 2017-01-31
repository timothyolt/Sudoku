// Copyright 2nullptr17 Timothy Oltjenbruns

#include "SudokuOptions.hpp"
#include <assert.h>
#include <algorithm>
#include <iostream>

SudokuOptions::ValueNode::~ValueNode()  {
  if (next == nullptr) return;
  while ((next = remove(next)) != nullptr) continue;
}

SudokuOptions::ValueNode* SudokuOptions::ValueNode::remove(SudokuOptions::ValueNode* target) {
  assert(target != nullptr);
  // Store next node to return
  ValueNode* next = target->next;
  // Prevent deleting its children
  target->next = nullptr;
  delete target;
  return next;
}

SudokuOptions::SudokuOptions() :
  Sudoku(),
  _options {
     {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
     {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
     {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
     {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
     {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
     {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
     {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
     {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
     {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
  }  { }

SudokuOptions::SudokuOptions(const Sudoku& copy) :
    Sudoku(copy),
    _options {
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
    }  { }

SudokuOptions::~SudokuOptions() {
  for (auto row(0); row < 9; ++row) {
    for (auto column(0); column < 9; ++column) {
     ValueNode* node(_options[row][column]);
     if (node == nullptr) continue;
     node->~ValueNode();
     delete node;
    }
  }
}

void SudokuOptions::add(Sudoku::size_t row, Sudoku::size_t column, Sudoku::value_t value) {
  assert(row >= 0 && row < 9);
  assert(column >= 0 && column < 9);
  assert(value > 0 && value <= 9);
  _options[row][column] = new ValueNode(value, _options[row][column]);
}

bool SudokuOptions::remove(Sudoku::size_t row, Sudoku::size_t column, Sudoku::value_t value) {
  assert(row >= 0 && row < 9);
  assert(column >= 0 && column < 9);
  assert(value > 0 && value <= 9);
  ValueNode* cursor(_options[row][column]);
  if (cursor == nullptr) return false;
  // If the first node is the target
  if (cursor->value == value) {
    _options[row][column] = ValueNode::remove(_options[row][column]);
    return true;
  }
  // Traverse to the node before the target value (or the last node)
  while (cursor->next != nullptr && cursor->next->value != value)
    cursor = cursor->next;
  // Target value not found
  if (cursor->next == nullptr) return false;
  cursor->next = ValueNode::remove(cursor->next);
  return true;
}

int SudokuOptions::removeOptionsRow(Sudoku::size_t row, Sudoku::value_t value) {
  assert(row >= 0 && row < 9);
  assert(value > 0 && value <= 9);
  int removed(0);
  for (auto column(0); column < 9; ++column)
    if (remove(row, column, value))
      ++removed;
  return removed;
}

int SudokuOptions::removeOptionsColumn(Sudoku::size_t column, Sudoku::value_t value) {
  assert(column >= 0 && column < 9);
  assert(value > 0 && value <= 9);
  int removed(0);
  for (auto row(0); row < 9; ++row)
    if (remove(row, column, value))
      ++removed;
  return removed;
}

int SudokuOptions::removeOptionsGrid(Sudoku::size_t grid, Sudoku::value_t value) {
  assert(grid >= 0 && grid < 9);
  assert(value > 0 && value <= 9);
  auto rowOffset((grid / 3) * 3);
  auto columnOffset((grid % 3) * 3);
  int removed(0);
  for (auto i(0); i < 9; ++i)
    if (remove(rowOffset + i / 3, columnOffset + i % 3, value))
      ++removed;
  return removed;
}

int SudokuOptions::removeOptionsGrid(Sudoku::value_t row, Sudoku::value_t column, Sudoku::value_t value) {
  return removeOptionsGrid((row / 3 * 3) + column / 3, value);
}

bool SudokuOptions::finalize(Sudoku::size_t row, Sudoku::size_t column) {
  assert(row >= 0 && row < 9);
  assert(column >= 0 && column < 9);
  assert(_puzzle[row][column] == 0);
  ValueNode* option(_options[row][column]);
  // assert(option != nullptr && option->value != 0 && option->next == nullptr);
  if (option == nullptr || option->value == 0)
    return false;
  value_t value(option->value);
  // Rules 8-10: If an option is the only instance of a value possible
  if (option->next != nullptr) {
    ValueNode* node = option;
    while (node != nullptr) {
      value = node->value;
      if (soloOptionsRow(row, value))
        break;
      if (soloOptionsColumn(column, value))
        break;
      if (soloOptionsGrid(row, column, value))
        break;
      if (node->next == nullptr) return false;
      node = node->next;
    }
    delete _options[row][column];
    _options[row][column] = nullptr;
  }
  // Rule 5-7: remove other related options when finalizing
  removeOptionsRow(row, value);
  removeOptionsColumn(column, value);
  removeOptionsGrid(row, column, value);
  _puzzle[row][column] = value;
  // Remove placed option from row, column, grid
  return true;
}

int SudokuOptions::solve() {
  // Generate initial options
  for (int row(0); row < 9; ++row)
    for (int column(0); column < 9; ++column)
      if (get(row, column) == 0)
        for (int value(1); value <= 9; ++value)
          // Rules 1-3: only one available option for this position
          // Rules 7-9: If an option is the only instance of a value possible
          if (!containsRow(row, value) &&
              !containsColumn(column, value) &&
              !containsGrid(row, column, value))
            add(row, column, value);
  // Iteratively finalize until no more placements are yielded
  int placed(0), placedI(0);
  do {
    placed += placedI;
    placedI = 0;
    for (int row(0); row < 9; ++row)
      for (int column(0); column < 9; ++column)
        // Rule 4-6: remove other related options when finalizing
        if (get(row, column) == 0 && finalize(row, column))
          ++placedI;
  } while (placedI != 0);
  return placed;
}

bool SudokuOptions::containsOptions(Sudoku::size_t row, Sudoku::size_t column, Sudoku::value_t value) const {
  assert(row >= 0 && row < 9);
  assert(column >= 0 && column < 9);
  assert(value > 0 && value <= 9);
  ValueNode* cursor(_options[row][column]);
  // Traverse to the node of the target value (or one past the last node)
  while (cursor != nullptr && cursor->value != value)
    cursor = cursor->next;
  return cursor != nullptr;
}

bool SudokuOptions::soloOptionsRow(Sudoku::size_t row, Sudoku::value_t value) const {
  assert(row >= 0 && row < 9);
  assert(value >= 0 && value <= 9);
  // Linear search a row
  int count(0);
  // TODO(timothyolt): short-circuit
  for (auto column(0); column < 9; column++)
    if (containsOptions(row, column, value))
      ++count;
  return count == 1;
}

bool SudokuOptions::soloOptionsColumn(Sudoku::size_t column, Sudoku::value_t value) const {
  assert(column >= 0 && column < 9);
  assert(value >= 0 && value <= 9);
  // Linear search a column
  int count(0);
  // TODO(timothyolt): short-circuit
  for (auto row(0); row < 9; row++)
    if (containsOptions(row, column, value))
      ++count;
  return count == 1;
}

bool SudokuOptions::soloOptionsGrid(Sudoku::size_t grid, Sudoku::value_t value) const {
  assert(grid >= 0 && grid < 9);
  assert(value >= 0 && value <= 9);
  // Linear search a grid
  // Wrap search top to bottom
  int count(0);
  // TODO(timothyolt): short-circuit
  auto rowOffset((grid / 3) * 3);
  auto columnOffset((grid % 3) * 3);
  for (auto i(0); i < 9; i++)
    if (containsOptions(rowOffset + i / 3, columnOffset + i % 3, value))
      ++count;
  return count == 1;
}
bool SudokuOptions::soloOptionsGrid(Sudoku::size_t row, Sudoku::size_t column, Sudoku::value_t value) const {
  return soloOptionsGrid((row / 3 * 3) + column / 3, value);
}
