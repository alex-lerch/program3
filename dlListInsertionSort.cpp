// simple C++ program to build a doubly linked list from a file of longs,
// sort the list using insertion sort, and then write the sorted data
// to a file
// By Mary Elaine Califf and Alex Lerch

#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;

//The Node struct is set up so you physically cannot change the data value after creating the object.
//Do not change this. You must only modify the pointer values when moving nodes.
struct Node
{
    private:
        long dataVal;
    public:
        Node* next;
        Node* prev;

        Node(long data = 0, Node* nextPtr = nullptr, Node* prevPtr = nullptr)
            : dataVal(data), next(nextPtr), prev(prevPtr) {}
        
        //Getter for public access of the dataVal
        long getDataVal() const { return dataVal; }
};

typedef Node* NodePtr;

// read the file into the linked list
void readFile(Node*& head, char* fileName);

// write the linked list to the file
void writeFile(Node* head, char* fileName);

// sort the linked list using an insertion sort following the standard algorithm
// for an array adapted to a doubly linked list
void insertionSort(Node*& head);

// removes the pointer from the list and fixes the pointers of the two adjacent nodes
void removePtr(NodePtr prev, NodePtr nodeToSort, NodePtr next);

// inserts the node to sort in between prev and next
void insert(NodePtr prev, NodePtr nodeToSort, NodePtr next);

// do not modify the main function -- you must complete the empty methods below
int main(int argc, char** argv) {

    if (argc < 3) {
        cout << "Usage: " << argv[0] << " infile outfile\n";
        exit(1);
    }
    char* inFileName = argv[1];
    char* outFileName = argv[2];
    Node* head = nullptr;

    readFile(head, inFileName);

    insertionSort(head);

    writeFile(head, outFileName);

    // clear out the list memory
    Node* temp = head;
    while (head)
    {
        head = head->next;
        delete temp;
        temp = head;
    }

    return 0;
}

void readFile(Node*& head, char* fileName)
{
    // variables used
    ifstream infile; // the file that we are reading from
    long currentNum; // the current num that we are grabbing from the input file
    NodePtr currentNode; // the node of the list we are currently looking at
    NodePtr prevNode; // the previous node to currentNode

    // open the input file for us to read
    infile.open(fileName);

    // read the file
    while (infile >> currentNum) {
        // process currentNum
        if (!head) { // if list is empty
            head = new Node(currentNum, nullptr, nullptr);
            currentNode = head;
            prevNode = head;
        }
        else { // list is not empty
            currentNode->next = new Node(currentNum, nullptr, prevNode);
            prevNode = prevNode->next;
            currentNode = currentNode->next;
        }
    }

    // close the file
    infile.close();
}

void writeFile(Node* head, char* fileName)
{
    // variables used
    ofstream outfile; // the name of the output file we are printing to
    NodePtr currentNode; // the current node in the list that we are looking at

    // open the output file for us to write to
    outfile.open(fileName);

    // write the list of longs to the file
    currentNode = head;
    while (currentNode) {
        outfile << currentNode->getDataVal() << "\n";
        currentNode = currentNode->next;
    }
}

void insertionSort(Node*& head)
{
    //asl debug
    std::cout << "in insertionSort()" << std::endl;

    // variables used
    NodePtr outerPtr; // the pointer that is used to point at the node that we are going to try and sort
    NodePtr innerPtr; // the pointer that is used to compare with the outer pointer to see if we need to keep going through the list
    NodePtr prev; // the node that is previous to the node to be sorted
    NodePtr next; // the node that is directly after the node to be sorted
    NodePtr nodeToSort; // the node that is meant to be sorted

    // go through entire list

    //asl debug
    std::cout << "head = " << head->getDataVal() << std::endl;

    outerPtr = head->next;

    //asl debug
    std::cout << "outerPtr = " << outerPtr->getDataVal() << std::endl;

    while (outerPtr) {

        //asl debug
        std::cout << "\n\n\nin while(outerPtr)" << std::endl;

        nodeToSort = outerPtr;

        //asl debug
        std::cout << "nodeToSort = " << nodeToSort->getDataVal() << std::endl;

        innerPtr = outerPtr;

        //asl debug
        std::cout << "innerPtr->prev = " << innerPtr->prev->getDataVal() << std::endl;

        while ( (innerPtr->prev) && ( nodeToSort->getDataVal() < innerPtr->prev->getDataVal() ) ) {
            innerPtr = innerPtr->prev;

            //asl debug
            std::cout << "innerPtr = " << innerPtr->getDataVal() << std::endl;
        }
        if (innerPtr != nodeToSort) {
            // remove nodeToSort from the list, fixing pointers
            prev = nodeToSort->prev;
            next = nodeToSort->next;

            //asl debug 
            std::cout << "entering removePtr(" << prev->getDataVal() << ", " << nodeToSort->getDataVal() << ", " << next->getDataVal() << ")" << std::endl;

            removePtr(prev, nodeToSort, next);

            //asldebug
            bool nxt = false;
            bool prv = false;
            if (nodeToSort->prev) {prv = true;}
            if (nodeToSort->next) {nxt = true;}
            std::cout << "nodeToSort next = " << !nxt << ", prev = " << !prv << std::endl;

            // insert
            prev = innerPtr->prev;
            next = innerPtr;

            //asl debug
            //std::cout << "entering insert(" << prev->getDataVal() << ", " << nodeToSort->getDataVal() << ", " << next->getDataVal() << ")" << std::endl;

            insert(prev, nodeToSort, next);
        }

        // update outerPtr to next item
        outerPtr = outerPtr->next;
    }
}

// removes the pointer from the list and fixes the pointers of the two adjacent nodes
void removePtr(NodePtr prev, NodePtr nodeToSort, NodePtr next) {
    // remove node to sort from the list
    nodeToSort->next = nullptr;
    nodeToSort->prev = nullptr;

    // fix the pointers of the two adjacent nodes
    if (prev) {
        prev->next = next;
    }

    if (next) {
        next->prev = prev;
    }
}


// inserts the node to sort in between prev and next
void insert(NodePtr prev, NodePtr nodeToSort, NodePtr next) {
    if (prev) {
        prev->next = nodeToSort;
    }
    nodeToSort->prev = prev;
    nodeToSort->next = next;

    if (next) {
        next->prev = nodeToSort;
    }
}