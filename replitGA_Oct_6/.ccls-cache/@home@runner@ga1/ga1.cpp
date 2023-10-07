
#include "ga1.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// removes a node amd moves up the head is necessary
void identity::removeNode(node *&toDel) {
  if (toDel != nullptr) {
    if (head == toDel)
      head = toDel->next;
    toDel->barName = "";
    toDel->decodedID = 0;
    toDel->next = nullptr;
    toDel->strID = "";
    delete toDel;
    toDel = nullptr;
  } else
    std::cerr << "Warning: removeNode() called on nullptr." << std::endl;
}

// takes input stream and spits out nodes
void identity::processInput(
    ifstream &inFile) { // needs further implementation and may need fixing

  std::string line = "";
  std::string barName = ""; // need to preserve barname between loops

  while (getline(inFile >> std::ws, line)) {
    // no need for erase parts of this function. Just use
    // getline(inFile>>std::ws,line). Also handles empty files! -Morgan
    line.erase(remove(line.begin(), line.end(), '\n'), line.end());
    line.erase(remove(line.begin(), line.end(), '\r'), line.end());
    line.erase(remove(line.begin(), line.end(), ' '), line.end());
    // just kidding... apparently getline can grab spaces at the end of a line
    // - Morgan

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
      string encodedID = line;
      string decodedID = "";
      decodedID = decode(encodedID);
      addNode(barName, stoi(decodedID),
              decodedID); // takes in integer for comparison and string for
                          // printing and duplicate checking causing
                          // interpretation as OCTAL integers
    }
  }
}

// helper function that prepends a node
void identity::addNode(string bN, int dID, std::string stringid) {
  node *temp = new node;
  temp->barName = bN;
  temp->decodedID = dID;
  temp->next = nullptr;
  temp->strID = stringid;
  temp->next = head;
  head = temp;
  //  cout << temp->strID<<endl; Debugging test
}

// helper function for sorting. Does not include guilty data member since it
// should be false for them all when it is called
void identity::swap(node *a, node *b) {

  std::swap(b->barName, a->barName);
  std::swap(b->strID, a->strID);

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
      // case: same integer value, but one has a string value with leading 0.
      // Picks shorter string to sort first
      if ((nextNode->decodedID == minNode->decodedID) &&
          (nextNode->strID.size() < minNode->strID.size())) {
        minNode = nextNode;
      } else if (nextNode->decodedID < minNode->decodedID) {
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
  if (isEmpty() || head->next == nullptr) { // case: empty or singular list
    return;
  }

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

void identity::print(ofstream &out) { // Gabriel Rivas
  if (isEmpty()) {                    // case: empty list
    return;
  }
  node *cur = new node;
  cur = head;

  // The following code is to debug.
  /* while(cur->next != nullptr){
     cout << cur->strID<< endl;
     cur = cur->next;
   }
   */
  cullTheGuilty();
  out << "Guilty:" << endl; // start pf guilty ids

  node *temp = new node; // creat temporary node
  temp = head;           // Set temp to head;

  while (temp->next != nullptr) { // Output all guilty ids
    if (temp->guilty == true) {   // if guilty is true output id
      out << temp->strID << endl; // output id
    }
    temp = temp->next; // Move to next node
  }

  out << "Innocent:" << endl; // start of inocent ids

  temp = head;                    // Go back to begining of linked list
  while (temp->next != nullptr) { // outout all innocent ids
    if (temp->guilty == false) {  // check if innoncent
      out << temp->strID << endl; // output id if innocent
    }
    temp = temp->next; // Move to next node
  }
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
// overloaded version of it finds a '('
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
    // head = head->next;
    removeNode(toDel);
  }
}