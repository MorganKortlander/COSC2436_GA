#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>

struct node
{
    std::string name;
    int age;
    int deposit;
    int numDrinks;
    node *next = nullptr;
};

class LL
{
private:
    node *head;
    node *sortedHead;
    node *sortedTail;
    int credentialCount;

protected:
    node *createNode(
        std::string nodeName,
        int nodeAge,
        int nodeDeposit,
        int nodeDrinks,
        node *following = nullptr);
    void removeNode(node *&toDel);
    void moveOn(node *&currNode);
    bool isDuplicate(node *currNode, node *addNode);
    void updateNode(
        node *indexNode,
        node *sourceNode)
    {
        indexNode->deposit = sourceNode->deposit;
        indexNode->numDrinks = sourceNode->numDrinks;
    }

public:
    LL()
    {
        head = nullptr;
        sortedHead=nullptr;
        sortedTail=nullptr;
        credentialCount = 0;
    }
    int compare(node *x, node *y, std::string attribute);
    bool isEmpty();
    void printHead();
    void outputNodes(std::ostream &os, node *cur = nullptr);
    void Add( // looks good
        int index,
        std::string nodeName,
        int nodeAge,
        int nodeDeposit,
        int nodeDrinks,
        node *following = nullptr);
    void addNew(
        std::string nodeName,
        int nodeAge,
        int nodeDeposit,
        int nodeDrinks,
        node *following = nullptr);
    void Remove(std::string, std::string);
    void Sort(std::string, std::ostream* os=nullptr, int counter=0);
    void getaddr();
    void getaddr(std::ostream &os);
    void printHead(std::ostream &os);
    ~LL();
};

/* */