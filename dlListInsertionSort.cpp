// simple C++ program to build a doubly linked list from a file of longs,
// sort the list using insertion sort, and then write the sorted data
// to a file
// By Mary Elaine Califf and Alex Lerch

/*------------------------------------------------------------------------------*
 *   included libraries                                                         *
 *------------------------------------------------------------------------------*/
#include <fstream>
#include <iostream>
#include <cstdlib>


/*------------------------------------------------------------------------------*
 *   namespaces                                                                 *
 *------------------------------------------------------------------------------*/
using namespace std;


/*------------------------------------------------------------------------------*
 *   private structs                                                            *
 *------------------------------------------------------------------------------*/
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


/*------------------------------------------------------------------------------*
 *   type definitions                                                           *
 *------------------------------------------------------------------------------*/
typedef Node* NodePtr;


/*------------------------------------------------------------------------------*
 *   function declarations                                                      *
 *------------------------------------------------------------------------------*/
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
void insert(NodePtr prev, NodePtr nodeToSort, NodePtr next, NodePtr& head);


/*------------------------------------------------------------------------------*
 *   main function                                                              *
 *------------------------------------------------------------------------------*/
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
} // end of main function


/*------------------------------------------------------------------------------*
 *   function definitions                                                       *
 *------------------------------------------------------------------------------*/
// read the file into the linked list
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



// write the linked list to the file
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



// sort the linked list using an insertion sort following the standard algorithm
void insertionSort(Node*& head)
{

    // variables used
    NodePtr outerPtr; // the pointer that is used to point at the node that we are going to try and sort
    NodePtr innerPtr; // the pointer that is used to compare with the outer pointer to see if we need to keep going through the list
    NodePtr prev; // the node that is previous to the node to be sorted
    NodePtr next; // the node that is directly after the node to be sorted
    NodePtr nodeToSort; // the node that is meant to be sorted

    /* go through entire list */
    outerPtr = head->next;

    while (outerPtr) {

        // check to see if outerPtr is already in the correct place
        if (outerPtr->getDataVal() < outerPtr->prev->getDataVal()) {

            // update which node we are sorting
            nodeToSort = outerPtr;

            // update which node will be checking the sorted portion of the list for the right location
            innerPtr = outerPtr->prev;

            // update which node we will be trying to sort next
            outerPtr = outerPtr->next;

            // pull out the node that needs to be sorted from the list
            // remove nodeToSort from the list, fixing pointers
            prev = nodeToSort->prev;
            next = nodeToSort->next;
            removePtr(prev, nodeToSort, next);

            // find the correct location for the nodeToSort
            while ( (innerPtr->prev) && ( nodeToSort->getDataVal() < innerPtr->prev->getDataVal() ) ) {
                innerPtr = innerPtr->prev;
            }

            // insert
            prev = innerPtr->prev;
            next = innerPtr;
            insert(prev, nodeToSort, next, head);

        }
        else { // outerPtr is already in the correct spot
            outerPtr = outerPtr->next;
        }
        
    }
}



// removes the pointer from the list and fixes the pointers of the two adjacent nodes
void removePtr(NodePtr prev, NodePtr nodeToSort, NodePtr next) {
    
    // remove node to sort from the list
    nodeToSort->next = nullptr;
    nodeToSort->prev = nullptr;

    // fix the pointers of the two adjacent nodes
    if (prev) { // if prev exists
        prev->next = next;
    }
    if (next) { // if next exists
        next->prev = prev;
    }
}



// inserts the node to sort in between prev and next
void insert(NodePtr prev, NodePtr nodeToSort, NodePtr next, NodePtr& head) {

    // if the previous node exists
    if (prev) {
        prev->next = nodeToSort;
    }

    // fix nodeToSort's prev and next pointers
    nodeToSort->prev = prev;
    nodeToSort->next = next;

    // if next node exists
    if (next) {
        next->prev = nodeToSort;
    }

    // if next is the head of the list
    if (next == head) {
        head = nodeToSort;
    }
}