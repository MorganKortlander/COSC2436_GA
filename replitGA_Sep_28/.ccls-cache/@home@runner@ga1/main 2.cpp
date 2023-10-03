// Muhammad Raza
// ga1

#include "ArgumentManager.h"
#include "ga1.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
  ArgumentManager am(argc, argv);
  /*const string input = am.get("input");
  const string command = am.get("command");
  const string output = am.get("output");*/

  ifstream inFile("input1.txt");
  //ifstream commandFile(command);
  //ofstream outFile(output);

  identity list;
  list.processInput(inFile);


  inFile.close();
  //outFile.close();
}