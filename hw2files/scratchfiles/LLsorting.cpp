// Protected Helper Functions
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

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
public:
    node *head;
    node *sortedHead;
    node *sortedTail;
    int credentialCount;

    void getaddr()
    {
        if (isEmpty())
        {
            std::cerr << "\nEmpty list, can't get anything!" << endl;
            return;
        }
        node *t = head;
        int count = 0;
        while (t != nullptr)
        {
            cout << "#" << count << "Address:\t " << t << endl;
            moveOn(t);
            count++;
        }
    }

    void getaddr(ostream &os)
    {
        node *t = head;
        int count = 0;
        while (t != nullptr)
        {
            os << "#" << count << "Address:\t " << t << endl;
            moveOn(t);
            count++;
        }
    }

    void updateNode(
        node *indexNode,
        node *sourceNode)
    {
        indexNode->deposit = sourceNode->deposit;
        indexNode->numDrinks = sourceNode->numDrinks;
    }

    LL()
    {
        head = nullptr;
        sortedHead = nullptr;
        sortedTail = nullptr;
        credentialCount = 0;
    }
    node *createNode(
        std::string nodeName,
        int nodeAge,
        int nodeDeposit,
        int nodeDrinks,
        node *following = nullptr)
    {
        node *addedNode = new node;
        addedNode->name = nodeName;
        addedNode->age = nodeAge;
        addedNode->deposit = nodeDeposit;
        addedNode->numDrinks = nodeDrinks;
        addedNode->next = following;
        credentialCount++;
        /* std::cout << "Created node with " << "[name: " << addedNode->name << "; age: " << addedNode->age << "; deposit: " << addedNode->deposit << "; number of drinks: " << addedNode->numDrinks << "]" << std::endl; */
        return addedNode;
    }

    // Removes a node. If node is current head, head is moved up to next node.
    void removeNode(node *&toDel)
    {
        if (!isEmpty() && (toDel != nullptr))
        {
            if (head == toDel)
                head = toDel->next;
            toDel->name = "";
            toDel->age = 0;
            toDel->deposit = 0;
            toDel->numDrinks = 0;
            toDel->next = nullptr;
            delete toDel;
            toDel = nullptr;
            credentialCount--;
        }
        else
            std::cerr << "Warning: removal called on nullptr." << std::endl;
    }

    // Moves to next node in sequential fashion. Stops if it is at a nullptr
    void moveOn(node *&mover)
    {
        if (mover != nullptr)
        {
            mover = mover->next;
        }
    }

    bool isDuplicate(node *currNode, node *addNode)
    {
        if ((currNode->name == addNode->name) && (currNode->age == addNode->age))
            return true;
        return false;
    }

    // Public Functions

    // Checks if there is a head node
    bool isEmpty()
    {
        if (head == nullptr)
            return true;
        return false;
    }

    // as per HW2 instructions
    void Add(
        int index,
        std::string nodeName,
        int nodeAge,
        int nodeDeposit,
        int nodeDrinks,
        node *following = nullptr)
    {
        if (index < 0)
        {
            std::cerr << "Negative index: out of range" << endl;
            return;
        }
        node *addedNode = createNode(
            nodeName,
            nodeAge,
            nodeDeposit,
            nodeDrinks,
            following);
        // case: empty list or insert at head/index0
        if (isEmpty() || index == 0)
        {
            if (!isEmpty())
                addedNode->next = head;
            head = addedNode;
        }

        else
        {
            node *preIndex = nullptr;
            node *nextNode = nullptr;
            node *tracker = head;
            int count = 0;
            // stop at end or if duplicate found
            while (tracker->next != nullptr && !isDuplicate(tracker, addedNode))
            {
                if (count == (index - 1))
                {
                    preIndex = tracker;
                    if (preIndex->next != nullptr)
                        nextNode = preIndex->next;
                }
                moveOn(tracker);
                count++;
            }
            // case: duplicate is found
            if (isDuplicate(tracker, addedNode))
            {
                updateNode(tracker, addedNode);
                removeNode(addedNode); // less efficient, maybe, but conciser
            }
            // case reached node before index
            else if (preIndex != nullptr)
            {
                preIndex->next = addedNode;
                if (nextNode != nullptr)
                    addedNode->next = nextNode;
            }
            // case index out of range; append it
            else
                tracker->next = addedNode;
        }
    }

    // simple append
    void addNew(
        std::string nodeName,
        int nodeAge,
        int nodeDeposit,
        int nodeDrinks,
        node *following = nullptr)
    {
        node *addedNode = createNode(
            nodeName,
            nodeAge,
            nodeDeposit,
            nodeDrinks,
            following);
        // case: empty list
        if (isEmpty())
        {
            head = addedNode;
            return;
        }
        // case head is there and only node
        node *tracker = head;
        // stop at end
        while (tracker->next != nullptr)
        {
            moveOn(tracker);
        }
        tracker->next = addedNode;
    }

    // Displays the info of the head node
    void printHead()
    {
        if (isEmpty())
        {
            std::cerr << "Empty: no head" << std::endl;
            return;
        }
        std::cout << "head info: \n"
                  << head << "\n"
                  << head->name << "\n"
                  << head->age << "\n"
                  << head->deposit << "\n"
                  << head->numDrinks << "\n"
                  << head->next << std::endl;
    }

    // writes the linked list to output file
    void outputNodes(std::ostream &os, node *cur)
    {
        if (isEmpty())
        {
            std::cerr << "Empty list" << std::endl;
            return;
        }
        if (cur == nullptr)
            cur = head;
        os << "name: \t" << cur->name << ";\tage: " << cur->age << "; deposit: " << cur->deposit << "; number: " << cur->numDrinks << std::endl;
        /*         std::cout << std::endl; */
        /*         std::cout << "[name: " << cur->name << "; age: " << cur->age << "; deposit: " << cur->deposit << "; number of drinks: " << cur->numDrinks << "]" << std::endl;
                std::cout << "wrote" << std::endl; */
        moveOn(cur);
        if (cur == nullptr)
            return;
        outputNodes(os, cur);
    }

    // Remove function asked for in HW
    void Remove(std::string attribute, std::string value)
    {
        if (isEmpty())
            return;
        node *preNode = nullptr;
        node *nextNode = nullptr;
        node *tracker = head;

        while (tracker != nullptr)
        {
            nextNode = tracker->next;
            if ((attribute == "name") && ((tracker->name) == value))
            {
                // cout << "name found" << endl;
                if (preNode != nullptr)
                    preNode->next = tracker->next;
                removeNode(tracker);
            }
            else if ((attribute == "age") && ((tracker->age) == stoi(value)))
            {
                // cout << "age found" << endl;
                if (preNode != nullptr)
                    preNode->next = tracker->next;
                removeNode(tracker);
            }
            else if ((attribute == "deposit") && (tracker->deposit) == stoi(value))
            {
                // cout << "deposit found" << endl;
                if (preNode != nullptr)
                    preNode->next = tracker->next;
                removeNode(tracker);
            }
            else if ((attribute == "number") && ((tracker->numDrinks) == stoi(value)))
            {
                // cout << "number of drinks found" << endl;
                if (preNode != nullptr)
                    preNode->next = tracker->next;
                removeNode(tracker);
            }
            else
                preNode = tracker;
            tracker = nextNode;
        }
    }

    int compare(node *x, node *y, std::string attribute)
    {
        char a;
        // std::cout << "comparing" << std::endl;
        if (attribute != "number")
            a = attribute[0];
        else
            a = 'u';
        switch (a)
        {
        case 'n':

            return (x->name).compare(y->name);
        case 'a':
            return x->age - y->age;
        case 'd':
            std::cout << "compare deposit result: " << x->deposit - y->deposit << std::endl;
            return x->deposit - y->deposit;
        case 'u':
            return x->numDrinks - y->numDrinks;
        default:
            std::cerr << "Invalid attribute" << std::endl;
            return 0;
        }
    }

    void Sort(std::string attribute, ostream &os)
    {
        if (isEmpty())
        {
            os << "Empty, all done" << std::endl;
            os << "head from " << head << "\nto " << sortedHead << endl;
            head = sortedHead;

            sortedHead = nullptr;

            /* os << "head now\t" << head << endl;
            os << "sortedhead now\t" << sortedHead << endl;
            os << "sortedtail was\t" << sortedHead << endl; */

            sortedTail = nullptr;
            return;
        }
        int count = 0;
        node *prevN = head;
        node *b4Sort = nullptr;
        node *toSort = head;
        node *nextN = nullptr;

        nextN = head->next;
        os << "Next up\t" << nextN << endl;

        os << "head addr\t" << head << endl;
        if (head->next != nullptr)
        {
            os << "next addr\t" << head->next << endl;
            if (head->next->next != nullptr)
            {
                os << "then addr\t" << head->next->next << '\n'
                   << endl;
            }
        }
        os << "Next: " << nextN << endl;
        if (nextN == nullptr)
            os << "next is null!" << endl;
        while (nextN != nullptr)
        {
            os << count++ << "addrs\t" << toSort << "\nAGAINST\t"
               << nextN << std::endl;
            if (compare(toSort, nextN, attribute) > 0) // > makes it ascending and preserve the order
            {
                /* os << "found one" << std::endl; */
                toSort = nextN;
                b4Sort = prevN;
            }
            prevN = nextN;

            os << "next\t" << nextN->next << "is a nullptr? " << std::boolalpha << (nextN->next == nullptr) << std::endl;

            // if (nextN->next == nullptr || nextN == nextN->next)
            //    done = true;

            nextN = nextN->next;
        }

        if (sortedHead == nullptr)
        {
            os << "First one!" << std::endl;
            os << "To add\t" << toSort << std::endl;
            sortedHead = toSort;
            sortedTail = toSort;
            /* os << "sortedtail was\t" << sortedHead << endl; */
        }

        if (b4Sort != nullptr)
        {
            os << "Trying to link b4sort" << endl;
            os << "@\t" << b4Sort << endl;
            /* if (b4Sort->next != nullptr)
            {
                os << "from\t" << b4Sort->next << endl;
            } */
            if (b4Sort->next->next != nullptr)
            {
                os << "\nto\t" << b4Sort->next->next << endl;
                b4Sort->next = b4Sort->next->next;
                os << "b4 sort linked from " << b4Sort->next << "\nto\n"
                   << b4Sort->next->next;
            }
        }

        // case: head is the one leaving
        if (toSort == head)
        {
            os << "Head was sorted" << std::endl;
            os << "H was\t" << head << std::endl;
            head = head->next;
            os << "H now\t" << head << std::endl;
            toSort->next = nullptr;
            /* os << "Adding\t" << toSort << std::endl; */
        }

        os << "added to tail" << std::endl;
        os << "moving from\t" << sortedTail << "\nto\n"
           << toSort << std::endl;
        toSort->next = nullptr;
        sortedTail->next = toSort;
        sortedTail = toSort;
        sortedTail->next = nullptr;

        /* os << "Next iteration of sorting..." << endl; */
        Sort(attribute, os);
    }
};

int main()
{
    LL clients;

    // creates the list
    if (true)
    {
        clients.addNew(
            "Rob", 34, 1234, 1);
        clients.addNew(
            "Ali", 23, 2345, 5);
        clients.addNew(
            "Kate", 27, 3456, 7);
        clients.addNew(
            "Sofia", 54, 1000, 6);
        clients.addNew(
            "Sofia", 64, 1000, 6);
        clients.addNew(
            "Tomas", 66, 4000, 7);
        clients.addNew(
            "Sofia", 24, 1000, 6);
        clients.addNew(
            "Jake", 39, 5000, 3);
        clients.addNew(
            "Sofia", 41, 1700, 6);
        clients.addNew(
            "Tom", 66, 4000, 3);
        clients.addNew(
            "Jakey", 39, 5000, 7);
    }

    ofstream ofs1("before.txt");
    clients.outputNodes(ofs1, clients.head);
    clients.getaddr(ofs1);
    ofs1.close();

    ofstream log("log.txt");

    clients.Sort("deposit", log);
    log.close();
    clients.getaddr();

    ofstream ofs2("after.txt");
    clients.outputNodes(ofs2, clients.head);
    clients.getaddr(ofs2);
    ofs2.close();
}