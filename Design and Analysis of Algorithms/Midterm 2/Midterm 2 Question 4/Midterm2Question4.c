#include <stdio.h>
#include <stdlib.h>

#define N 12 // number of activities

typedef struct stack_array{
   int top;       // index of the element at the top of the stack  
   int size;      // size of the array
   int* array;    // pointer to (first element of) array
} Stack_Array;

// ----------------------------- STACK ARRAY FUNCTIONS --------------------------------//
// copy array1 into array2
void copy_array(int* array1, int size_of_array1, int* array2, int size_of_array2){
   if(size_of_array1 > size_of_array2){
      printf("array1 is bigger than array2 and therefore cannot be copied.\n");
      return;
   }
   for(int i = 0; i < size_of_array1; i++){
      array2[i] = array1[i];
   }
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

//---------------------------------- RECURSIVE GREEDY ALGORITHM --------------------------------------//

int recursive_greedy_algorithm(int* start_times, int* finish_times, int index, int count){
   Stack_Array stack_array; 
   stack_array.size = N;
   Stack_Array* pntr = &stack_array;      
   int j;
   int new_count;
   
   count++; // increment activity counter
   int max_count = count;

   stack_array.top = -1; // signifies an empty stack
   stack_array.array = (int*)(malloc(stack_array.size * sizeof(int)));

   // fill stack with eligible activities
   for(j = 0; j < N; j++){
      if(finish_times[index] <= start_times[j]){
         push_stack_array(pntr, j);
      }
   }

   // while stack is not empty
   while(stack_array.top != -1){
      index = pntr->array[pntr->top]; // pop next eligible activity off the stack
      pop_stack_array(pntr);
      new_count = recursive_greedy_algorithm(start_times, finish_times, index, count);
      if(new_count > max_count){
         max_count = new_count;
      }
   }
   
   free(pntr->array); // free stack from memory
   return(max_count);
}

//------------------------------------ GREEDY ALGORITHM ------------------------------------------------//
// Return the maximum number of activities able to be performed by a single person.
int greedy_algorithm(int* start_times, int* finish_times){
   Stack_Array stack_array; 
   stack_array.size = N;
   Stack_Array* pntr = &stack_array;      
   int i, j, count;
   int index;
   int max_count = 1;
   
   // execute the process for each activity
   for(i = 0; i < N; i++){
      stack_array.top = -1; // signifies an empty stack
      stack_array.array = (int*)(malloc(stack_array.size * sizeof(int)));
      count = 1; 

      // fill stack with eligible activities
      for(j = 0; j < N; j++){
         if(finish_times[i] <= start_times[j]){
            push_stack_array(pntr, j);
         }
      }

      // while stack is not empty, call the recursive function
      while(stack_array.top != -1){
         index = pntr->array[pntr->top];
         pop_stack_array(pntr);
         count = recursive_greedy_algorithm(start_times, finish_times, index, 1);
         if(count > max_count){
            max_count = count;
         }
      }
      free(pntr->array); // free stack from memory
   }
   return(max_count);
}

int main(){
   int start_times[N] =  {1, 3, 2, 6, 6, 8, 4, 4, 9,  10, 2, 7};
   int finish_times[N] = {6, 5, 7, 8, 9, 9, 7, 7, 12, 14, 5, 10}; 
   int max_number_activities = greedy_algorithm(start_times, finish_times);
   printf("Maximum Number of Activities: %d\n", max_number_activities);   
}
