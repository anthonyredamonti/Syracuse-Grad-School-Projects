// Anthony Redamonti
// 10-9-2020
//
// Please use the gcc compiler to complile this file.
// After navigating to the correct project folder, the following commands were
// performed via the terminal on a Linux (Ubuntu) operating system to compile
// and run the program:
//
// gcc ./q4.c -o q4
// ./q4
//
// output:
// A = [1,2,3,4,5,6,7,8,9]
// B = [9,8,7,6,5,4,3,2,1]
// O = [10,10,10,10,10,10,10,10,10] 
//
// Unix platform is supported. No Windows specific libraries or functions were used.
//
// The following is my solution to question 4 from homework 1.
// The program simply adds two hardcoded arrays together.
// The "output" array stores the sum of array A and array B. 
// All of the arrays are the same size. 
// Array A, array B and array O (output) are printed out.
//

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void arrayAddition(int A[], int B[], int N, int output[]){
   for(int i=0; i < N; i++){
      output[i] = A[i] + B[i];
   }
}

void PrintArray(int* array, int number_of_elements_to_print){
      int i;
      printf("[");
      for(i = 0; i < number_of_elements_to_print-1; i++){
      printf("%d,", array[i]);
   }
   printf("%d]\n", array[number_of_elements_to_print-1]);
}

int main() { 

   int A[9] = {1,2,3,4,5,6,7,8,9};
   int B[9] = {9,8,7,6,5,4,3,2,1};
   
   printf("A = ");
   PrintArray(A, 9);
   printf("B = ");
   PrintArray(B, 9);

   int* output = (int*)(malloc(9*(sizeof(int*)))); // allocate memory on the heap
   arrayAddition(A, B, 9, output);
   printf("O = ");
   PrintArray(output, 9);
   free(output); // free up the memory on the heap

   return 0;
}
