#ifndef GA1_H
#define GA1_H
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

struct node
{
  string barName = ""; // is this even needed?
  int decodedID = 0;
  node *next = nullptr;
  bool guilty = false;
  std::string strID = "";

  // for debugging: outputs our node infos
  void printnode()
  {
    /* print("\nNode info:\nLocation"); */
    /*     print(this);
        print("barname");
        print(this->barName)*/
    std::cout << "decID\t" << this->decodedID << std::endl;
    std::cout << "next\t" << this->next << std::endl;
    std::cout << "guilty\t" << std::boolalpha << this->guilty << std::endl;
    std::cout << "strID\t" << this->strID << std::endl;
  }
};

class identity
{

private:
  node *head;
  bool guiltyPresent;
  bool innocentPresent;

protected:
  //  checks for dupe numbers
  bool isDuplicate(node *check, node *against)
  {
    if (check->strID == against->strID)
      return true;
    return false;
  }
  void removeNode(node *&toDel);

  void swap(node *a, node *b);
  std::string decode(std::string toDec);
  void decode(std::string &toDec, std::string::iterator previous);

public:
  identity() : head(nullptr), guiltyPresent(false), innocentPresent(false) {}
  void processInput(ifstream &inFile);
  bool isEmpty()
  {
    if (head == nullptr)
      return true;
    return false;
  } //'nuff said
  node *getHead() const { return head; }
  void cullTheGuilty();
  void addNode(string bN, int dID, std::string stringid);

  void selectionSort();
  void print(ofstream &out);

  // outputs all current nodes to terminal: for deugging pre-filtering
  void printRaw(node *p, int count = 0)
  {
    if (p != nullptr)
    {
      std::cout << "\n#" << count++ << std::endl;
      p->printnode();
      p = p->next;
      printRaw(p, count);
    }
  }

  ~identity();
};

#endif