// simple C++ program to read in an array of longs, sort
// the array using heapsort, and then write the sorted data
// to a file
// By Mary Elaine Califf and Alex Lerch

/*------------------------------------------------------------------------------*
 *   included libraries                                                         *
 *------------------------------------------------------------------------------*/
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;


/*------------------------------------------------------------------------------*
 *   definitions                                                                *
 *------------------------------------------------------------------------------*/
#define HEAP_SIZE arr[0]


/*------------------------------------------------------------------------------*
 *   function declarations                                                      *
 *------------------------------------------------------------------------------*/
// read the file into the vector (starting at index 1)
void readFile(vector<long>& arr, char* fileName);

// write the vector to the file (starting at index 1)
void writeFile(const vector<long>& arr, char* fileName);

// sort the vector using heapsort (data starts at index 1)
void heapsort(vector<long>& arr);

// turns any 1 based array into a max heap using the heapify algorithm
void maxHeapify(std::vector<long>& arr);

// move the item at parentIndex down into its correct spot within the array
void percolateDown(std::vector<long>& arr, int parentIndex);

// helper function for percolateDown. determines how many children the parent index has
int calculateNumChildren(const std::vector<long>& arr, int parentIndex);

// helper function for percolate down that swaps the two numbers in the vector
void swapNums(std::vector<long>& arr, int firstIndex, int secondIndex);

// helper function for percolate down. finds which of the parent's children has the largest value
int findLargestChildIndex(const std::vector<long>& arr, int firstChildIndex, int secondChildIndex);

// moves the max value to the end of the array and treats it as no longer in the heap
void deleteMax(std::vector<long>& arr);


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
  vector<long> theArray;
  
  readFile(theArray, inFileName);

  heapsort(theArray);
  
  writeFile(theArray, outFileName);

  return 0;
} // end of main


/*------------------------------------------------------------------------------*
 *   function definitions                                                       *
 *------------------------------------------------------------------------------*/

// read the file into the vector (starting at index 1)
void readFile(vector<long>& arr, char* fileName)
{
  // variables used
  std::ifstream infile; // the file that we are reading from
  long currentNum; // the current number that we are working with from the file

  // open the file
  infile.open(fileName);

  /* add the values from the file to the array */
  // initialize index to hold the size
  arr.push_back(0);

  // fill array with values from the infile, incrementing the size along the way
  while (infile >> currentNum) {
    arr.push_back(currentNum);
    HEAP_SIZE++;
  }

  // close the file
  infile.close();
}



// write the vector to the file (starting at index 1)
void writeFile(const vector<long>& arr, char* fileName)
{
  // variables used
  std::ofstream outfile; // the file that we are writing to

  // open the outfile
  outfile.open(fileName);

  // write the array to the file
  for (int arrIndex = 1; arrIndex < arr.size(); arrIndex++) {
    outfile << arr[arrIndex] << "\n";
  }

  // close the file
  outfile.close();
}



// sort the vector using heapsort (data starts at index 1)
void heapsort(vector<long>& arr) {

  // build a max heap with heapify algorithm
  maxHeapify(arr);

  // delete max value swapping it to the end
  while (HEAP_SIZE > 0) {
    deleteMax(arr);
  }

}



// turns any 1 based array into a max heap using the heapify algorithm
void maxHeapify(std::vector<long>& arr) {

  // for each parent from (the size of the array)/2 down to the first parent(root)
  for (int arrIndex = HEAP_SIZE/2; arrIndex >= 1; arrIndex--) {
    percolateDown(arr, arrIndex);
  }

}  



// move the item at parentIndex down into its correct spot within the array
void percolateDown(std::vector<long>& arr, int parentIndex) {

  // variables used
  int numChildren; // the number of children that the parent index has
  int firstChildIndex = parentIndex * 2; // the index that the first child would be at
  int secondChildIndex = (parentIndex * 2) + 1; // the index that the second child would be at
  int largestChildIndex; // the index of the highest value child of parent

  // calculate how many children the parent index has
  numChildren = calculateNumChildren(arr, parentIndex);

  /* determine which index has the child with the largest value */
  switch (numChildren) {
      case 1:
          // the largest child must be the first child
          largestChildIndex = firstChildIndex;
          break;
      case 2:
          // find which child is of greater value
          largestChildIndex = findLargestChildIndex(arr, firstChildIndex, secondChildIndex);
          break;
  }

  // if we need to swap
  if (numChildren > 0 && arr[parentIndex] < arr[largestChildIndex]) {
      swapNums(arr, parentIndex, largestChildIndex);
      // in case we still need to percolate down
      percolateDown(arr, largestChildIndex);
  }

}



// helper method for percolateDown. determines how many children the parent index has
int calculateNumChildren(const std::vector<long>& arr, int parentIndex) {

    // if the second child of the parent exists
    if ( ( (parentIndex * 2) + 1 ) <= HEAP_SIZE ) {
        return 2;
    }
    // if only the first child of the parent exists
    else if ( (parentIndex * 2) <= HEAP_SIZE) {
        return 1;
    }
    // the parent doesn't have any children
    else {
        return 0;
    }

}



// helper function for percolate down that swaps the two numbers in the vector
void swapNums(std::vector<long>& arr, int firstIndex, int secondIndex) {

    long temp = arr[firstIndex];
    arr[firstIndex] = arr[secondIndex];
    arr[secondIndex] = temp;

}



// helper function for percolate down. finds which of the parent's children has the largest value
int findLargestChildIndex(const std::vector<long>& arr, int firstChildIndex, int secondChildIndex) {

    // if the first child is a larger or equal value to the second child
    if (arr[firstChildIndex] >= arr[secondChildIndex]) {
        return firstChildIndex;
    }
    // the second child is larger
    else {
        return secondChildIndex;
    }

}



// moves the max value to the end of the array and treats it as no longer in the heap
void deleteMax(std::vector<long>& arr) {

  // swap the first item and last item currently still in the heap
  swapNums(arr, 1, HEAP_SIZE);

  // decrement the size of the heap
  HEAP_SIZE--;

  // move the new root to the correct place within the heap
  percolateDown(arr, 1);
  
}