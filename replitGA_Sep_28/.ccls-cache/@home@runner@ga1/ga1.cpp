#include "ga1.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// self-explanatory
void identity::removeNode(node *&toDel) {
  if (!isEmpty() && (toDel != nullptr)) {
    if (head == toDel)
      head = toDel->next;
    toDel->barName = "";
    toDel->decodedID = 0;
    toDel->next = nullptr;
    delete toDel;
    toDel = nullptr;
  } else
    std::cerr << "Warning: removal called on nullptr." << std::endl;
}

// takes input stream and spits out nodes 
//FIXME: we need leading 0's in the ID's!!!
void identity::processInput(
    ifstream &inFile) { // needs further implementation and may need fixing

  std::string line = "";
  std::string barName = ""; // need to preserve barname between loops

  while (getline(inFile >> std::ws, line)) {
    // no need for erase parts of this function. Just use
    // getline(inFile>>std::ws,line). Also handles empty files! -Morgan
    /* line.erase(remove(line.begin(), line.end(), '\n'), line.end());
    line.erase(remove(line.begin(), line.end(), '\r'), line.end());
    line.erase(remove(line.begin(), line.end(), ' '), line.end()); */

    // receive bar
    if (line == "Bar1" || line == "Bar2") {
      barName = line;
      continue; // restart loop with current bar recognized
    }
    // edge case: no bar given yet
    else if (barName == "") {
      std::cerr << "Warning, no bar declared!" << std::endl;
      continue;
    } else {
      std::string encodedID = line;
      std::string decodedID = "";
      decodedID = decode(encodedID);
      addNode(barName, stoi(decodedID)); // //FIXME: potential issue with leading 0's causing interpretation as OCTAL integers
    }
  }
}
// void identity::insertAtEnd(std::string barName, std::string decodedID) {}

// helper function that prepends a node
void identity::addNode(string bN, int dID) {
  node *temp = new node;
  temp->barName = bN;
  temp->decodedID = dID;
  temp->next = nullptr;

  temp->next = head;
  head = temp;
}
/* void identity::insertAtEnd(string bN, int dID) {
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
} */
/* void identity::insertAtPos(string bN, int dID, int pos) {
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
} */
/* void identity::removeAtBeg() {
  if (head == nullptr) {
    return;
  }
  node *temp = head;
  head = head->next;
  delete temp;
} */
/* void identity::removeAtEnd() {
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
} */
/* void identity::removeAtPos(int pos) {
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
} */

// helper function for sorting. Does not include guilty data member since it
// should be false for them all when it is called
void identity::swap(node *a, node *b) {

  std::swap(b->barName, a->barName);

  int swapID = 0;
  swapID = a->decodedID;
  a->decodedID = b->decodedID;
  b->decodedID = swapID;

  node *temp = a->next;
  a->next = b->next;
  b->next = temp;
}

// sorts all nodes within the identity class object
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

// calls sort, removes dupes, flags guilty
void identity::cullTheGuilty() {
  if (isEmpty() || head->next == nullptr) // case: empty or singular list
    return;
  selectionSort();

  // average case: more than one node
  node *curr = head;
  node *nextNode = curr->next;

  while (nextNode != nullptr) {
    // case: dupes. Flag current to guilty and jump nextNode
    if (isDuplicate(curr, nextNode)) {
      curr->guilty = true;
      curr->next = nextNode->next;
      removeNode(nextNode);
      nextNode = curr->next;
    }
    // case: not dupes
    else {
      nextNode = nextNode->next;
      curr = curr->next;
    }
  }
}

void identity::print(ofstream &out) { // FIXME: implement
  if (isEmpty())                      // case: empty list
    return;
  cullTheGuilty();                 
}

// Overload that accepts a string and an iterator from its first instance of a
// '('. Since the string in this overloaded function is a reference, any
// changes made during recursive calls should carry over
void identity::decode(std::string &toDec, std::string::iterator previous) {
  char openChar = '(';
  char closeChar = ')';

  // find opening (, if any left. Variable  previous receives a +1 offset to
  // address since the iterator is pointing to the last ( detected
  std::string::iterator opening = std::find_if(
      previous + 1, toDec.end(), [openChar](char i) { return i == openChar; });
  if (opening != toDec.end()) {
    decode(toDec, opening);
  }

  // find closing )
  std::string::iterator closing =
      std::find_if(previous + 1, toDec.end(),
                   [closeChar](char i) { return i == closeChar; });

  opening = previous; // just for my sanity, reused the var name

  // pull out part to be reversed. Variable closing is technically a
  // "beginning" iterator, so it doesn't need +1 offset, since "ending
  // iterators" are expected go one element past the last one !!!.

  // std::cout << "String before: " << toDec << std::endl;
  std::string toReverse(opening + 1, closing);
  // std::cout << "Going to reverse: " << toReverse << std::endl;
  std::reverse(toReverse.begin(), toReverse.end());
  // std::cout << "Reverse out: " << toReverse << std::endl;

  // stick it back in, overwriting where there was ( ). !!! now we have the
  // opposite situation with needing the +1 on closing, instead of opening.

  toDec.replace(opening, closing + 1, toReverse);
  // std::cout << "String after replacement: " << toDec << std::endl;
}

// Base function that accepts a string to decode. Should make a local copy of
// the string, so you need to assign a new decoded string to result. Calls the
// overloaded version if it finds a '('
std::string identity::decode(std::string toDec) {
  char openChar = '(';
  char closeChar = ')';

  // find opening (, if any
  std::string::iterator opening = std::find_if(
      toDec.begin(), toDec.end(), [openChar](char i) { return i == openChar; });
  if (opening != toDec.end()) {
    decode(toDec, opening);
  }
  return toDec;
}

identity::~identity() {
  while (!isEmpty()) {
    node *toDel = head; // keep node 2b deleted
    head = head->next;
    removeNode(toDel);
  }
}