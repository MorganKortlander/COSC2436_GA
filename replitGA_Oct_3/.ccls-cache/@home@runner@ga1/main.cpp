// Muhammad Raza
// ga1

#include "ArgumentManager.h"
#include "ga1.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// check that 2 files opened correctly--function is defined below main
bool filesOpened(std::ifstream &ifs, std::ofstream &ofs);
// check that 3 files opened correctly--function is defined below main
bool filesOpened(std::ifstream &ifs, std::ofstream &ofs, std::ifstream &cmd);

int main(int argc, char *argv[]) {
  ArgumentManager am(argc, argv);
  /*const string input = am.get("input");
  const string command = am.get("command");
  const string output = am.get("output");*/

  ifstream inFile("input1.txt");
  // ifstream commandFile(command);
  ofstream outFile("output1.txt");

  // checks that files are actually open. Returns error code 1 if they are not
  // and closes stream.
  if (!filesOpened(inFile, outFile)) {
    return 1;
  }

  identity list;
  list.processInput(inFile);
  list.selectionSort();
  list.print(outFile);
  
  

  inFile.close();
  // outFile.close();
}

bool filesOpened(std::ifstream &ifs, std::ofstream &ofs) {
  bool opened = true;
  if (!ofs.is_open()) {
    std::cerr << "failed to open output file." << std::endl;
    opened = false;
    ofs.close();
  }
  if (!ifs.is_open()) {
    std::cerr << "failed to open input file." << std::endl;
    opened = false;
    ifs.close();
  }
  return opened;
}

bool filesOpened(std::ifstream &ifs, std::ofstream &ofs, std::ifstream &cmd) {
  bool opened = true;
  if (!ofs.is_open()) {
    std::cerr << "failed to open output file." << std::endl;
    opened = false;
    ofs.close();
  }
  if (!ifs.is_open()) {
    std::cerr << "failed to open input file." << std::endl;
    opened = false;
    ifs.close();
  }
  if (!cmd.is_open()) {
    std::cerr << "failed to open command file." << std::endl;
    opened = false;
    cmd.close();
  }
  return opened;
}