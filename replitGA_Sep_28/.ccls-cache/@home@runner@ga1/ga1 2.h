#ifndef GA1_H
#define GA1_H
#include <iostream>
using namespace std;

struct node {
  string barName;
  int decodedID;
  node *next;
};

class identity {
private:
  node *head;

public:
  identity();
  void processInput(ifstream &inFile);
  int decodeID(const string &encoded);
  void insertAtBeg(string bN, int dID);
  void insertAtEnd(string bN, int dID);
  void insertAtPos(string bN, int dID, int pos);
  void removeAtBeg();
  void removeAtEnd();
  void removeAtPos(int pos);
  void swap(node *a, node *b);
  void selectionSort();
  void print(ofstream &out);
};

#endif