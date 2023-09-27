#include "ga1.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

identity::identity() { head = nullptr; }

void identity::processInput(
    ifstream &inFile) { // needs further implementation and may need fixing
  string line;
  string barName;
  while (getline(inFile, line)) {
    line.erase(remove(line.begin(), line.end(), '\n'), line.end());
    line.erase(remove(line.begin(), line.end(), '\r'), line.end());
    line.erase(remove(line.begin(), line.end(), ' '), line.end());

    string temp = "";
    string barName = "";
    string encodedID = "";
    int decodedID = 0;

    istringstream iss(line);

    iss >> temp;

    if (temp == "Bar1" || temp == "Bar2") {
      barName = temp;
    } else {
      encodedID = temp;
    }
    if (encodedID != "")
      decodedID = identity::decodeID(encodedID);
    // cout << barName << endl;
  }
  identity::insertAtEnd(barName, decodedID);
}
int identity::decodeID(const string &encoded) { // implement
  // cout << encoded << endl;
  int result;

  return 1;
}
void identity::insertAtBeg(string bN, int dID) {
  node *temp = new node;
  temp->barName = bN;
  temp->decodedID = dID;
  temp->next = nullptr;

  temp->next = head;
  head = temp;
}
void identity::insertAtEnd(string bN, int dID) {
  node *temp = new node;
  temp->barName = bN;
  temp->decodedID = dID;
  temp->next = nullptr;

  if (head == nullptr) {
    head = temp;
    return;
  }
  node *curr = head;
  while (curr->next != nullptr) {
    curr = curr->next;
  }
  curr->next = temp;
}
void identity::insertAtPos(string bN, int dID, int pos) {
  node *temp = new node;
  temp->barName = bN;
  temp->decodedID = dID;
  temp->next = nullptr;

  if (head == nullptr && pos == 0) {
    head = temp;
    return;
  } else if (head != nullptr && pos == 0) {
    identity::insertAtBeg(bN, dID);
  }

  node *curr = head;
  node *prev = nullptr;
  for (int i = 0; i < pos; i++) {
    if (curr == nullptr) {
      return;
    }
    prev = curr;
    curr = curr->next;
  }
  prev->next = temp;
  temp->next = curr;
}
void identity::removeAtBeg() {
  if (head == nullptr) {
    return;
  }
  node *temp = head;
  head = head->next;
  delete temp;
}
void identity::removeAtEnd() {
  if (head == nullptr) {
    return;
  } else if (head->next == nullptr) {
    node *temp = head;
    head = nullptr;
    delete temp;
    return;
  }
  node *curr = head;
  node *prev = nullptr;
  while (curr->next != nullptr) {
    prev = curr;
    curr = curr->next;
  }
  prev->next = nullptr;
  delete curr;
}
void identity::removeAtPos(int pos) {
  if (head == nullptr) {
    return;
  } else if (pos == 0) {
    node *temp = head;
    head = head->next;
    delete temp;
  }
  node *prev = nullptr;
  node *curr = head;
  for (int i = 0; i < pos; i++) {
    if (curr == nullptr) {
      return;
    }
    prev = curr;
    curr = curr->next;
  }
  prev->next = curr->next;
  delete curr;
}
void identity::swap(node *a, node *b) {
  node *temp = new node;
  temp->barName = a->barName;
  temp->decodedID = a->decodedID;

  a->barName = b->barName;
  a->decodedID = b->decodedID;

  b->barName = temp->barName;
  b->decodedID = temp->decodedID;

  delete temp;
}
void identity::selectionSort() {
  node *curr = head;
  while (curr != nullptr) {
    node *minNode = curr;
    node *nextNode = curr->next;
    while (nextNode != nullptr) {
      if (nextNode->decodedID < minNode->decodedID) {
        minNode = nextNode;
      }
      nextNode = nextNode->next;
    }

    identity::swap(curr, minNode);
    curr = curr->next;
  }
}
void identity::print(ofstream &out) { // implement
}