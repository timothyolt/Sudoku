// Copyright 2017 Timothy Oltjenbruns

#include <iostream>
#include <fstream>
#include <Sudoku.hpp>

int main() {
  std::cout << "Hello, World!" << std::endl;
  Sudoku a;
  std::string name;
  std::ofstream file;

  bool done(false);

  while (!done) {
    try {
      std::cin >> a;
      std::cout << a << std::endl;
      std::cout <<  "Name this puzzle: ";
      std::cin >> name;
      file.open(name + ".pzl.txt");
      file << a << std::endl;
      file.close();
      std::cout << "Wrote puzzle to '" + name + ".pzl.txt'!" << std::endl;
      done = true;
    } catch (std::exception& e) {
      std::cout << e.what() << std::endl;
      std::cout << "Restarting puzzle input." << std::endl;
    }
  }
  return 0;
}
