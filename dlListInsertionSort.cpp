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

// add any function prototypes for any additional functions here


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

    // open the input file for us to read
    infile.open(fileName);

    // read the file
    while (infile >> currentNum) {
        // process currentNum
        if (!head) { // if list is empty
            head = new Node(currentNum, nullptr, nullptr);
            currentNode = head;
        }
        else { // list is not empty
            currentNode->next = new Node(currentNum, nullptr, currentNode->prev);
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
    if (head) {
        currentNode = head;
        while (currentNode) {
            outfile << currentNode->getDataVal() << "\n";
            currentNode = currentNode->next;
        }
    }
}

void insertionSort(Node*& head)
{
    // your code here
}

// implementation code for any additional functions here

