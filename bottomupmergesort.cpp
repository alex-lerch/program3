// simple C++ program to read in an array of longs, sort
// the array using bottom up mergesort 
// and then write the sorted data to a file
// By Mary Elaine Califf and _______

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
using namespace std;

// read the file into the vector
void readFile(vector<long>& arr, char* fileName);

// write the vector to the file
void writeFile(const vector<long>& arr, char* fileName);

// sort the vector using bottom up mergesort
void mergesort(vector<long>& arr);

// add any function prototypes for any additional functions here


// do not modify the main function -- you must complete/modify the methods below
int main(int argc, char** argv) {

    if (argc < 3) {
        cout << "Usage: " << argv[0] << " infile outfile\n";
        exit(1);
    }
    char* inFileName = argv[1];
    char* outFileName = argv[2];
    vector<long> theArray;

    readFile(theArray, inFileName);

    mergesort(theArray);

    writeFile(theArray, outFileName);

    return 0;
}

void readFile(vector<long>& arr, char* fileName)
{
    // your code here
}

void writeFile(const vector<long>& arr, char* fileName)
{
    // your code here
}


void mergesort(vector<long>& arr)
{

    // your code here
}

// any additional function implementations go here
