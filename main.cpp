// Jon Zivku, jzivku, jonzivku@me.com, main.cpp, Quicksort A03
// Status: Working/Tested
/* Quicksort is deceptively complex. No matter how many times I would walk
 through partition I still wasnt quite able to visualize it. Ran into some
 issues when I put in hoare - I forgot to update the function calls, and ended
 up in an infinite loop, and then with an array that wasn't sorted. I think I
 could've worked a little more carefully. Cool things: I wrote my first bash
 script; to get the runtime of all of the test cases for medianOf3. 
 */

#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

using std::vector;
void quickSort(vector<int> &A, int size, bool flag);
// wrapper function for quickSort.
// pre-cond: a vector<int> A of size size, runs hoare version if flag is true
// postcond: A is now sorted

void quickSortL(vector<int> &A, int p, int r);
// part of Lomuto method
// recursive function quickSort for sorting all or part of a vector<int>
// pre-cond: a vector<int> A, lower bound p and upper bound r,
// postcond: A has been sorted in range p to r

int partitionL(vector<int> &A, int p, int r);
// Lomuto method for partitioning
// sorts A, selecting a pivot of A in range p to r. all elements in the range
// are rearranged such that elements greater than the pivot are past the pivot
// in range, and elements lesser are before the pivot.
// pre-cond: vector<int> A, lower bound p and upper bound r.
// postcond: the range p-r in A has been rearranged as in the description.
//           the index of the pivot element is returned

void quickSortH(vector<int> &A, int p, int r);
// part of Hoare method.
// recursive function quickSort for sorting all or part of a vector<int>
// pre-cond: a vector<int> A, lower bound p and upper bound r,
// postcond: A has been sorted in range p to r

int partitionH(vector<int> &A, int left, int right);
// Hoare method for partitioning
// pre-cond: say some stuff here
// postcond: other stuff here

void swap(vector<int> &A, int i, int j);
// pre-cond: vector<int> A, valid indecies of A i and j.
// postcond: the values in A at i and j have been swapped

int medianOf3(vector<int> &A, int left, int center, int right);
// pre-cond: vector<int> A, valid indecies of A left, center and right.
// postcond: returns the index of the median value of A[left,center, right]

int main(int argc,char *argv[]){
  // check for commandline argument and set hoareFlag
  bool hoareFlag = false;
  if(argc == 2 && std::string(argv[1]) == "-h")
    hoareFlag = true;  

  // make & fill the container
  std::vector<int> sortMe;
  int temp;
  while(std::cin >> temp)
    sortMe.push_back(temp);
  
  //sort the container
  int size = sortMe.size();
  quickSort(sortMe, size, hoareFlag);
  
  //print the sorted container, ascending order, '0' padded. (social sec)
  for(int i = 0; i < size; i++)
    std::cout << std::setw(9) << std::setfill('0') << sortMe[i] << std::endl;
  
  return 0;
}

void quickSort(vector<int> &A, int size, bool hoareFlag){
  if(!hoareFlag)
    quickSortL(A, 0, size-1);
  else if(hoareFlag)
    quickSortH(A, 0, size-1);  
}


void quickSortL(vector<int> &A, int left, int right){
  if(left < right){
    int pivot = partitionL(A, left, right);
    quickSortL(A, left, pivot-1);
    quickSortL(A, pivot+1, right);
  }
}

void quickSortH(vector<int> &A, int left, int right){
  if(left < right){
    int pivot = partitionH(A, left, right);
    quickSortH(A, left, pivot);
    quickSortH(A, pivot+1, right);
  }
}

int partitionL(vector<int> &A, int left, int right){
  if(right - left > 10){ // increase this value to increase median of three,
    // use 1 or greater, since thats when you have an array of 3 elements
    swap(A, medianOf3(A, left, (left + (right - left)/2), right), right);
  }
  int key = A[right]; // last element becomes pivot/key
  int i = left - 1; // index of lower range
  for (int j = left; j < right; j++){
    if(A[j] <= key){
      i++;
      swap(A, i, j);
    }
  }
  swap(A, i+1, right);
  return i+1; // i+1 is the index of the new pivot
}

int partitionH(vector<int>& A, int left, int right){
  if(right - left > 15)
    swap(A, medianOf3(A, left, (left + (right - left)/2), right), left);
  int key = A[left];
  int i = left - 1;
  int j = right + 1;
  while(true){
    do{i = i + 1;} while (A[i] < key);
    do{j = j - 1;} while (A[j] > key);
    if(i >= j)
       return j;
    swap(A, i, j);
  }
}

int medianOf3(vector<int> &A, int left, int mid, int right){
  if (A[left] > A[mid] && A[left] > A[right]) // if left is greatest
    return A[mid] > A[right] ? mid : right;
  else if (A[mid] > A[left] && A[mid] > A[right]) // if middle is greatest
    return A[left] > A[right] ? left : right;
  else //else right is greatest
    return A[left] > A[mid] ? left : mid;
}
     
void swap(vector<int> &A, int i, int j){
  int temp = A[i];
  A[i] = A[j];
  A[j] = temp;
}	       
