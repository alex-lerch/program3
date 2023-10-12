#include <iostream>
#include <vector>


#define ARR_SIZE arr[0]

/* function declarations */

// move the item at parentIndex down into its correct spot within the array
void percolateDown(std::vector<long>& arr, int parentIndex);

// helper function for percolateDown. determines how many children the parent index has
int calculateNumChildren(const std::vector<long>& arr, int parentIndex);

// helper function for percolate down that swaps the two numbers in the vector
void swapNums(std::vector<long>& arr, int firstIndex, int secondIndex);

// helper function for percolate down. finds which of the parent's children has the largest value
int findLargestChildIndex(const std::vector<long>& arr, int firstChildIndex, int secondChildIndex);

// prints an array
void printArray(std::vector<long>& arr);


int main() {

    /* test percolateDown function */

    /* asl
    / test for no children 
    // create the vector with no children from parentIndex
    std::vector<long> arr = {1, 1};
    percolateDown(arr, 1);
    ARR_SIZE--;
    std::cout << "\nexpected array = [0, 1, ]\nactual array =   ";
    printArray(arr);
    std::cout << "\n";
    */

    /* asl
    // test for 1 child 
    // create vector with 1 child
    std::vector<long> arr = {2, 1, 5};
    percolateDown(arr, 1);
    // decrement the size of the heap
    ARR_SIZE--;
    std::cout << "\nexpected array = [1, 5, 1, ]\nactual array =   ";
    printArray(arr);
    std::cout << "\n";
    */

    /* asl
    // test for two children where left child should be swapped
    std::vector<long> arr = {3, 1, 5, 4};
    percolateDown(arr, 1);
    // decrement the size of the heap
    ARR_SIZE--;
    std::cout << "\nexpected array = [2, 5, 1, 4, ]\nactual array =   ";
    printArray(arr);
    std::cout << "\n";
    */

    /* asl
    // test for two children where right child should be swapped
    std::vector<long> arr = {3, 1, 4, 5};
    percolateDown(arr, 1);
    // decrement the size of the heap
    ARR_SIZE--;
    std::cout << "\nexpected array = [2, 5, 4, 1, ]\nactual array =   ";
    printArray(arr);
    std::cout << "\n";
    */

    /* asl
    // test for two children but no swaps
    std::vector<long> arr = {3, 5, 1, 4};
    percolateDown(arr, 1);
    // decrement the size of the heap
    ARR_SIZE--;
    std::cout << "\nexpected array = [2, 5, 1, 4, ]\nactual array =   ";
    printArray(arr);
    std::cout << "\n";
    */


    /* asl
    // test for two swaps where there are two children then just one child
    std::vector<long> arr = {6, 1, 4, 5, 2, 3, 6};
    percolateDown(arr, 1);
    // decrement the size of the heap
    ARR_SIZE--;
    std::cout << "\nexpected array = [5, 5, 4, 6, 2, 3, 1, ]\nactual array =   ";
    printArray(arr);
    std::cout << "\n";
    */

    
    /* asl */
    // test for two swaps both with two children
    std::vector<long> arr = {7, 1, 4, 5, 2, 3, 6, 8};
    percolateDown(arr, 1);
    // decrement the size of the heap
    ARR_SIZE--;
    std::cout << "\nexpected array = [6, 5, 4, 8, 2, 3, 6, 1, ]\nactual array =   ";
    printArray(arr);
    std::cout << "\n";

    /* asl */
    // test for when the array is empty

    
}

/* function definitions */

// move the item at parentIndex down into its correct spot within the array and decrement the size of the heap
void percolateDown(std::vector<long>& arr, int parentIndex) {

    // asl debug
    std::cout << "\n\nin percolateDown with parentIndex = " << parentIndex << " \nand arr = ";
    printArray(arr);
    std::cout << std::endl;

    // variables used
    int numChildren; // the number of children that the parent index has
    int firstChildIndex = parentIndex * 2; // the index that the first child would be at
    int secondChildIndex = (parentIndex * 2) + 1; // the index that the second child would be at
    int largestChildIndex; // the index of the highest value child of parent

    // calculate how many children the parent index has
    numChildren = calculateNumChildren(arr, parentIndex);

    // asl debug
    std::cout << "numChildren = " << numChildren << std::endl;

    /* */
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



// prints an array
void printArray(std::vector<long>& arr) {
    std::cout << "[";
    for (long num : arr) {
        std::cout << num << ", ";
    }
    std::cout << "]";
}



// helper method for percolateDown. determines how many children the parent index has
int calculateNumChildren(const std::vector<long>& arr, int parentIndex) {
    if ( ( (parentIndex * 2) + 1 ) <= ARR_SIZE ) {
        return 2;
    }
    else if ( (parentIndex * 2) <= ARR_SIZE) {
        return 1;
    }
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
    if (arr[firstChildIndex] >= arr[secondChildIndex]) {
        return firstChildIndex;
    }
    else {
        return secondChildIndex;
    }
}
