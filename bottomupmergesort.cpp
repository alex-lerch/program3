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

// merge the two logical arrays
void merge(vector<long>& arr, vector<long>& tempVector, int leftArrayIndex, int rightArrayIndex, int rightArrayEnd);


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
    // temporary vector used to help sort the logical arrays
    std::vector<long> tempVector(arr.size());

    // the size of the logical arrays to sort
    int sizeOfSortedArrays = 1;

    // while we still have logical arrays to sort
    while (sizeOfSortedArrays < arr.size()) {

        // the start index for the left logical array to be sorted
        int leftArrayIndex = 0;

        // check for real group
        while ( leftArrayIndex < (arr.size() - sizeOfSortedArrays) ) {
            
            // calculate the start index for the right array
            int rightArrayIndex = leftArrayIndex + sizeOfSortedArrays;

            // calculate the end index for the right array
            int rightArrayEnd;
            if ( arr.size() < (rightArrayIndex + (sizeOfSortedArrays - 1)) ) {
                rightArrayEnd = arr.size();
            }
            else {
                rightArrayEnd = rightArrayIndex + (sizeOfSortedArrays - 1);
            }

            //asl debug
            std::cout << "size of sorted arrays = " << sizeOfSortedArrays << std::endl;

            // merge the two logical arrays
            merge(arr, tempVector, leftArrayIndex, rightArrayIndex, rightArrayEnd);

            // move start index for the left array to the next unsorted logical array
            leftArrayIndex += 2 * sizeOfSortedArrays;
        }

        // update the size of sorted arrays
        sizeOfSortedArrays *= 2;
    }
}


// merge the two logical arrays
void merge(vector<long>& arr, vector<long>& tempVector, int leftArrayIndex, int rightArrayIndex, int rightArrayEnd) {

    //asl debug
    std::cout << "leftArrayIndex = " << leftArrayIndex << ", rightArrayIndex = " << rightArrayIndex << ", rightArrayEnd = " << rightArrayEnd << "\n\n" << std::endl;

    // variables used
    int leftArrayEnd = rightArrayIndex - 1;
    int tempPosition = leftArrayIndex;
    int numElements = rightArrayEnd - leftArrayIndex + 1;

    //
    while (leftArrayIndex <= leftArrayEnd && rightArrayIndex <= rightArrayEnd) {
        
        //
        if (arr[leftArrayIndex] <= arr[rightArrayIndex]) {
            
            //
            tempVector[tempPosition++] = arr[leftArrayIndex++];
        }
        else {

            //
            tempVector[tempPosition++] = arr[rightArrayIndex++];
        }
    }

    //
    while (leftArrayIndex <= leftArrayEnd) {

        //asl debug
        if (arr[leftArrayIndex] == 0) {
            std::cout << "arr[" << leftArrayIndex << "] == 0 from leftArrayIndex" << std::endl;
        }

        tempVector[tempPosition++] = arr[leftArrayIndex++];
    }

    //
    while (rightArrayIndex <= rightArrayEnd) {

        //asl debug
        if (arr[rightArrayIndex] == 0) {
            std::cout << "arr[" << rightArrayIndex << "] == 0 from rightArrayIndex" << std::endl;
        }

        tempVector[tempPosition++] = arr[rightArrayIndex++];
    }

    // copy tempVector back to arr. needs to be fixed so that copy doesn't occur for final program
    for (int i = 0; i < numElements; ++i, --rightArrayEnd) {
        arr[rightArrayEnd] = tempVector[rightArrayEnd];
    }
}
