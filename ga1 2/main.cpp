// Muhammad Raza
// ga1

#include "ArgumentManager.h"
#include "ga1.h"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// check that 2 files opened correctly--function is defined below main
// bool filesOpened(std::ifstream &ifs, std::ofstream &ofs);
// check that 3 files opened correctly--function is defined below main
// bool filesOpened(std::ifstream &ifs, std::ofstream &ofs, std::ifstream &cmd);

int main(int argc, char *argv[]) {
  ArgumentManager am(argc, argv);
  std::ifstream inFile(am.get("input"));
  std::ofstream outFile(am.get("output"));
  // const string commandFile = am.get("command");

  /* ifstream inFile("input2.txt");
  // ifstream commandFile(command);
  ofstream outFile("output2.txt"); */

  // checks that files are actually open. Returns error code 1 if they are not
  // and closes stream.
  /*  if (!filesOpened(inFile, outFile)) {
     return 1;
   } */

  if (!inFile.is_open())
    std::cerr << "Failed to open input" << std::endl;
  if (!outFile.is_open())
    std::cerr << "Failed to open output" << std::endl;
  identity list;

  // from C, writes all stdout to the specified file instead
  /* freopen("log.txt", "w", stdout); */

  list.processInput(inFile);
  /* std::cout << "\n\nAfter read:" << std::endl;
  list.printRaw(list.getHead()); */

  /* list.selectionSort();
  std::cout << "\n\nAfter sort:" << std::endl;
  list.printRaw(list.getHead()); */

  /* list.cullTheGuilty();
  std::cout << "\n\nAfter cull:" << std::endl;
  list.printRaw(list.getHead()); */

  list.print(outFile);

  inFile.close();
  outFile.close();
}

/* bool filesOpened(std::ifstream &ifs, std::ofstream &ofs) {
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
} */