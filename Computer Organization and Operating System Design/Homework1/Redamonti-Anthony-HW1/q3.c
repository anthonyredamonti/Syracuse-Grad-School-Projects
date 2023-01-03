// Anthony Redamonti
// 10-9-2020
//
// Please use the gcc compiler to complile this file.
// After navigating to the correct project folder, the following commands were
// performed via the terminal on a Linux (Ubuntu) operating system to compile
// and run the program:
//
// gcc ./q3.c -o q3
// ./q3 5
//
// output:
// 0: 1
// 1: 1
// 2: 2
// 3: 3
// 4: 5
// 5: 8
//
// Unix platform is supported. No Windows specific libraries or functions were used.
//
// The following is my solution to question 3 from homework 1.
// The user will supply a command line argument in the form of an integer (call it "N").
// The program will iteratively print all of the fibonacci numbers up to and including 
// the N'th fibonacci number.
// 
// I implemented a stack in the form of an array. When the fibonacci function is called, the 
// N'th fibonacci number is calculated (and returned) and is the last element in the array.
// The main function iteratively calls the fibonacci function (as required in the problem description)
// and prints out all of the fibonacci numbers until reaching (and including) the N'th fibonacci number.
//

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// ------------------------------ STRUCTS ------------------------------------//

typedef struct stack_array{
   int top;       // index of the element at the top of the stack  
   int size;      // size of the array
   int* array;    // pointer to (first element of) array
} Stack_Array;

// ----------------------------- STACK ARRAY FUNCTIONS --------------------------------//

// copy array1 into array2
void copy_array(int* array1, int size_of_array1, int* array2, int size_of_array2){
   if(size_of_array1 > size_of_array2){
      //printf("array1 is bigger than array2 and therefore cannot be copied.\n");
      return;
   }
   for(int i = 0; i < size_of_array1; i++){
      array2[i] = array1[i];
   }
}

void PrintArray(int* array, int number_of_elements_to_print){
      int i;
      for(i = 0; i < number_of_elements_to_print; i++){
      printf("%d ", array[i]);
   }
   printf("\n");
}

void push_stack_array(Stack_Array* stack, int value){
   stack->top++; // -1 + 1 = 0 for first element in array
   // if no more room, create new array double in size
   if(stack->top == stack->size){
      int temp_size = stack->size * 2;
      int* array_temp = (int*)(malloc(temp_size*(sizeof(int))));
      copy_array(stack->array, stack->size, array_temp, temp_size);
      free(stack->array);
      stack->array = array_temp;
      stack->size = temp_size;
   }
   // push value on top of stack
   stack->array[stack->top] = value;
}

void pop_stack_array(Stack_Array* stack){
   if(stack->top == -1){
      printf("stack array already empty\n");
      return;
   }
   stack->top--;
}

//-------------------------- fibonacci function---------------------//

int fibonacci(int n){
   if((n == 0)||(n == 1)){
      return 1;
   }
   int answer = 0;
   
   Stack_Array array1;
   array1.size = 10;
   array1.top = -1; // empty 
   array1.array = (int*)(malloc(array1.size * sizeof(Stack_Array))); // store in heap
   Stack_Array* pntr = &array1;
   push_stack_array(pntr, 1);
   push_stack_array(pntr, 1);
   
   for(int i = 1; i < n-1; i++){
      int value = array1.array[i] + array1.array[i-1];
      push_stack_array(pntr, value);
   }
   answer = array1.array[n-1]; // correct fibonacci number
   free(array1.array); // free memory in heap
   return(answer);
}

int main(int argc, char *argv[]) { 
   if(argc == 2){
      char* a = argv[1];
      int N = atoi(a); // convert the string to an integer
      for(int i = 0; i < N+1; i++){
         int fib_i = fibonacci(i+1);
         printf("%d: %d\n", i, fib_i);
      }
   }
   else if(argc > 2){
      //printf("Please only enter one integer as an argument.\n");
   }
   else{
      //printf("Please enter at least one integer as an argument.\n");
   }
   return 0;
}
