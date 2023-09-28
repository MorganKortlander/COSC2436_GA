#ifndef GA1_H
#define GA1_H
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

struct node {
  string barName = ""; // is this even needed?
  int decodedID = 0;
  node *next = nullptr;
  bool guilty = false;
  std::string ID = "";
};

class identity {
private:
  node *head;

protected:
  // checks for dupe numbers
  bool isDuplicate(node *check, node *against) {
    if (check->decodedID == against->decodedID)
      return true;
    return false;
  }
  void removeNode(node *&toDel);
  void cullTheGuilty();
  void swap(node *a, node *b);
  std::string decode(std::string toDec);
  void decode(std::string &toDec, std::string::iterator previous);

public:
  identity() { head = nullptr; };
  void processInput(ifstream &inFile);
  bool isEmpty() {
    if (head == nullptr)
      return true;
    return false;
  } //'nuff said'

  void addNode(string bN, int dID);
  // no need for these
  // void insertAtEnd(string bN, int dID);
  // void insertAtPos(string bN, int dID, int pos);
  // void removeAtBeg();
  // void removeAtEnd();
  // void removeAtPos(int pos);

  void selectionSort();
  void print(ofstream &out);

  ~identity();
};

#endif