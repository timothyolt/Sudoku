// Copyright 2nullptr17 Timothy Oltjenbruns

#include "SudokuOptions.hpp"
#include <assert.h>

SudokuOptions::ValueNode::~ValueNode()  {
  if (next == nullptr) return;
  while ((next = remove(next)) != nullptr) continue;
}

SudokuOptions::ValueNode *SudokuOptions::ValueNode::remove(SudokuOptions::ValueNode *target) {
  assert(target != nullptr);
  ValueNode* next = target->next;
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

void SudokuOptions::remove(Sudoku::size_t row, Sudoku::size_t column, Sudoku::value_t value) {
  assert(row >= 0 && row < 9);
  assert(column >= 0 && column < 9);
  assert(value > 0 && value <= 9);
  ValueNode* cursor(_options[row][column]);
  if (cursor == nullptr) return;
  // If the first node is the target
  if (cursor->value == value) {
    _options[row][column] = ValueNode::remove(_options[row][column]);
    return;
  }
  // Traverse to the node before the target value (or the last node)
  while (cursor->next != nullptr && cursor->next->value != value)
    cursor = cursor->next;
  // Target value not found
  if (cursor->next == nullptr) return;
  cursor->next = ValueNode::remove(cursor->next);
}

void SudokuOptions::finalize(Sudoku::size_t row, Sudoku::size_t column) {
  assert(row >= 0 && row < 9);
  assert(column >= 0 && column < 9);
  ValueNode* option(_options[row][column]);
  assert(option != nullptr && option->value != 0 && option->next == nullptr);
  assert(_puzzle[row][column] == 0);
  _puzzle[row][column] = option->value;
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
