// simple C++ program to read in an array of longs, sort
// the array using bottom up mergesort 
// and then write the sorted data to a file
// By Mary Elaine Califf and Alex Lerch

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
    // variables used
    ifstream infile; // the file that we are reading from
    long currentNum; // the current num that we are grabbing from the input file

    // open the file for us to read
    infile.open(fileName);

    // read the file
    while (infile >> currentNum) {
        // process the number
        arr.push_back(currentNum);
    }

    // close the file
    infile.close();
}

void writeFile(const vector<long>& arr, char* fileName)
{
    // variables used
    ofstream outfile; // the name of the output file we are printing to

    // open the output file for us to write to
    outfile.open(fileName);

    // write the list of longs to the outfile
    for (long num : arr) {
        outfile << num << "\n";
    }

    // close the output file
    outfile.close();
}


void mergesort(vector<long>& arr)
{

    // your code here
}

// any additional function implementations go here
