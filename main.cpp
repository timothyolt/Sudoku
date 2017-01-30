// Copyright 2017 Timothy Oltjenbruns

#include <unistd.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <Sudoku.hpp>
#include <OptionsSolver.hpp>

int help() {
  std::cout
    << "Sudoku solver, Tim Oltjenbruns\n"
    << "Usage: run_sudoku [program]\n"
    << "Programs:\n"
    << "\thelp: Show this help info\n"
    << "\twrite: Create a new puzzle and output to a file\n"
    << "\tplay puzzleName: Run the solver on puzzle named puzzleName\n"
    << std::endl;
  return 0;
}

int write() {
  Sudoku a;
  std::string name;
  std::ofstream file;

  while (true) {
    try {
      std::cin >> a;
      std::cout << a << std::endl;
      std::cout <<  "Name this puzzle: ";
      std::cin >> name;
      file.open(name + ".pzl.txt");
      file << a << std::endl;
      file.close();
      std::cout << "Wrote puzzle to '" + name + ".pzl.txt'!" << std::endl;
      return 0;
    } catch (std::exception& e) {
      std::cout << e.what() << std::endl;
      std::cout << "Restarting puzzle input." << std::endl;
    }
  }
}

int play(char* filename) {
  Sudoku puzzle;
  std::ifstream file;
  file.open(std::string(filename) + ".pzl.txt");
  if (!file.is_open()) {
    std::cout << "File not found." << std::endl;
    return 0;
  }
  file >> puzzle;
  file.close();
  std::cout << puzzle << std::endl;
  Sudoku solved = OptionsSolver::solve(puzzle);
  std::cout << solved << std::endl;
  return 0;
}

int menuInput();

int menuParse(int argCount, char** args) {
  if (argCount == 0)
    return menuInput();
  for (auto i(0); i < argCount; i++) {
    std::string argString(args[i]);
    if (argString.compare("help") == 0 || argString.compare("--help") == 0 || argString.compare("-h") == 0)
      return help();
    if (argString.compare("write") == 0 || argString.compare("--write") == 0 || argString.compare("-w") == 0)
      return write();
    if ((argString.compare("play") == 0 || argString.compare("--play") == 0 || argString.compare("-p") == 0)
        && i + 1 < argCount)
      return play(args[i + 1]);
    if (argString.compare("menu") == 0 || argString.compare("--menu") == 0 || argString.compare("-m") == 0)
      return menuInput();
  }
  return menuInput();
}

int menuInput() {
  std::cout << "Shall we play a game?" << std::endl;
  char input[256];
  std::cin.getline(input, 256);
  std::string inputString(input);
  if (inputString.find("thermonuclear") != std::string::npos ||
      inputString.find("Thermonuclear") != std::string::npos ) {
    std::cout << "I'm sorry Dave, I'm afraid I can't do that." << std::endl;
    sleep(1);
    std::cout << "If one reference wasn't enough, two should be sufficient." << std::endl;
    return 0;
  }
  int argCount = static_cast<int>(std::count(inputString.begin(), inputString.end(), ' ') + 1);
  char** args = new char*[argCount];
  std::istringstream inputStream(inputString);
  std::string temp;
  for (auto i(0); i < argCount; i++) {
    inputStream >> temp;
    char* arg = new char[temp.length() + 1];
    std::snprintf(arg, temp.length() + 1, temp.c_str());
    args[i] = arg;
  }
  int r = menuParse(argCount, args);
  for (auto i(0); i < argCount; i++)
    delete[] args[i];
  delete[] args;
  return r;
}

int main(int argCount, char* args[]) {
  return menuParse(argCount, args);
}
