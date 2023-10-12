// simple C++ program to read in an array of longs, sort
// the array using heapsort, and then write the sorted data
// to a file
// By Mary Elaine Califf and Alex Lerch

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

// read the file into the vector (starting at index 1)
void readFile(vector<long>& arr, char* fileName);

// write the vector to the file (starting at index 1)
void writeFile(const vector<long>& arr, char* fileName);

// sort the vector using heapsort (data starts at index 1)
void heapsort(vector<long>& arr);

// add any function prototypes for any additional functions here

// do not modify the main function -- you must complete the empty methods below
int main(int argc, char** argv) {

  if (argc < 3) {
    cout << "Usage: " << argv[0] << " infile outfile\n";
    exit(1);
  }
  char* inFileName = argv[1];
  char* outFileName = argv[2];
  vector<long> theArray;
  
  readFile(theArray, inFileName);

  heapsort(theArray);
  
  writeFile(theArray, outFileName);

  return 0;
}

void readFile(vector<long>& arr, char* fileName)
{
  // variables used
  std::ifstream infile; // the file that we are reading from
  long currentNum; // the current number that we are working with from the file

  // open the file
  infile.open(fileName);

  // add the values from the file to the array
  while (infile >> currentNum) {
    arr.push_back(currentNum);
  }

  // close the file
  infile.close();
}

void writeFile(const vector<long>& arr, char* fileName)
{
  // variables used
  std::ofstream outfile; // the file that we are writing to

  // open the outfile
  outfile.open(fileName);

  // write the array to the file
  for (long num : arr) {
    outfile << num << "\n";
  }

  // close the file
  outfile.close();
}

void heapsort(vector<long>& arr)
{
  // your code here
}

// implementation code for any additional functions here
  
