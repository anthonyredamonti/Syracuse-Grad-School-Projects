// Anthony Redamonti
// 7-24-2020
// This is Assignment 3 for Week 3 written in C. Questions 1, 2, 3, and bonus are answered.

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct Point {
int x, y;
};

// function and variable declarations
int secondLargest(int A[], int N);
int* createArray(int size);
double distance(struct Point* p1, struct Point* p2);
void reAssign(int** pointer);
int i, j, value;
int globalVariable = 50;

// Assuming no duplicate elements
int secondLargest(int A[], int N){
   // using insertionSort algorithm to sort array
   for(i = 1; i < N; i++){
      j = i;
      value = A[i];
      while(j>0 && A[j-1]>value){
         A[j]=A[j-1];
         j--;
      }
      A[j] = value;
   }
   return(A[N-2]); // return second element in sorted list
}

// Use malloc to create an array of "size" in length
int* createArray(int size){
   int* array = (int*) malloc(size * sizeof(int));
   return(array);
}

// calculate the distance between two points
double distance(struct Point* p1, struct Point* p2){
   // calculate the difference between x and y of each point
   int x1minusx2 = (p1->x) - (p2->x);
   int y1minusy2 = (p1->y) - (p2->y);
   
   // square the difference. Result is type double
   double x1minx2pow2 = pow(x1minusx2,2); 
   double y1miny2pow2 = pow(y1minusy2,2); 
   
   // squareroot of sum is result
   double sum = x1minx2pow2 + y1miny2pow2;
   double squareroot = sqrt(sum);
   return(squareroot);
}

// Have to point to the memory location of the pointer, so double pointer is needed
void reAssign(int** pointer)
{
   *pointer = NULL;
   *pointer = &globalVariable;
}

int main() {

   // test the secondLargest function that sorts the array and selects the second largest value
   int arr[] = {1, 3, 6, 2, -5, 0};
   int size_of_array = (sizeof(arr)/sizeof(int));
   printf("The elements in the unsorted array are: ");
   for(i = 0; i < size_of_array; i++){
      printf("%d ", arr[i]);
   }
   printf("\n");
   int second_largest = secondLargest(arr, size_of_array);
   printf("The second largest element in the array is: %d\n", second_largest);

   // test the createArray function
   int size_of_new_array = 20;
   int* new_array = createArray(size_of_new_array); // uses malloc
   for (i = 0; i < size_of_new_array; i++){
      new_array[i] = i;
      printf("new_array[%d] = %d\n", i, new_array[i]);
   }
   free(new_array); // free up the dynamically allocated memory in heap

   // test the distance function
   struct Point point_1 = {9, 32};
   struct Point point_2 = {100, 12};
   struct Point* pointer_to_point_1 = &point_1;
   struct Point* pointer_to_point_2 = &point_2;
   double distance_between_points = distance(pointer_to_point_1, pointer_to_point_2);
   printf("The distance between {%d, %d} and {%d, %d} is %f\n", pointer_to_point_1->x, pointer_to_point_1->y, pointer_to_point_2->x, pointer_to_point_2->y, distance_between_points);

   // test the reAssign function
   int* ptr = &size_of_new_array;
   int** ptr_to_ptr = &ptr;
   printf("The pointer is pointing to %d at address %d\n", *ptr, ptr);
   reAssign(ptr_to_ptr);
   printf("After reassignment the pointer is pointing to global variable %d at address %d\n", *ptr, ptr);
   
   return 0;
}

/*

The terminal in Visual Studio Code reads the following:

The elements in the unsorted array are: 1 3 6 2 -5 0
The second largest element in the array is: 3
new_array[0] = 0
new_array[1] = 1
new_array[2] = 2
new_array[3] = 3
new_array[4] = 4
new_array[5] = 5
new_array[6] = 6
new_array[7] = 7
new_array[8] = 8
new_array[9] = 9
new_array[10] = 10
new_array[11] = 11
new_array[12] = 12
new_array[13] = 13
new_array[14] = 14
new_array[15] = 15
new_array[16] = 16
new_array[17] = 17
new_array[18] = 18
new_array[19] = 19
The distance between {9, 32} and {100, 12} is 93.171884
The pointer is pointing to 20 at address 6422184
After reassignment the pointer is pointing to global variable 50 at address 4210696

*/