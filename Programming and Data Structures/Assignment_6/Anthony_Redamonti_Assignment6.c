// Anthony Redamonti
// 8-17-2020
// This is Assignment 6 for Week 6 written in C. Questions 1, 2, and 3 are answered.

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Elements in array will be the product of all elements in array excluding said element.
void Product_Recursion(int* array, int size_of_array, int currentIndex, int* temp_array){
   int j, product;
   
   // if first iteration, reallocate memory of temp_array to the heap.
   if(currentIndex == 0){
      temp_array = NULL;
      temp_array = (int*)malloc(size_of_array*sizeof(int));
   }

   // base case. Copy elements from temp_array to array and free the temp_array memory space.
   if(currentIndex == size_of_array){
      for(j = 0; j < size_of_array; j++){
         array[j] = *(temp_array+j);
      }
      free(temp_array);
      return;
   }

   product = 1;
   for(j = 0; j < size_of_array; j++){
      // exclude current element from product
      if(currentIndex == j){
         continue;
      }
      product *= array[j];
   }
   *(temp_array + currentIndex) = product;
   Product_Recursion(array, size_of_array, currentIndex+1, temp_array);
}

// a^b using recursion
int Power_Recursion(int a, int b){
   if(b == 0){
      return 1;
   }
   return(a * Power_Recursion(a,b-1));
}

void swap_chars(char array[], int i, int j){
   char temp = array[i];
   array[i] = array[j];
   array[j] = temp;
}

void PrintCharArray(char array[]){
   printf("%s\n", array);
}

// find all of the permutations of the string by calling this function recursively and increasing the index argument.
void Print_String_Permutations(char ch[], int size_minus_one, int index){
   int i;
   
   // base case
   if(index == size_minus_one-1){
      PrintCharArray(ch);
      return;
   }

   // begin recursively calling in a loop. 
   for(i = index; i < size_minus_one; i++){
      
      // no need to swap same index.
      if(index!=i){
         swap_chars(ch, index, i);
      }
      
      Print_String_Permutations(ch, size_minus_one, index+1);
      
      // second swap is needed to return array to previous form for next iteration.
      if(index!=i)
      {
         swap_chars(ch, index, i);
      }
   }
}

void PrintArray(int* array, int number_of_elements_to_print){
      int i;
      for(i = 0; i < number_of_elements_to_print; i++){
      printf("%d ", array[i]);
   }
   printf("\n");
}

int main() {

   // Test Product_Recursion function
   int array1[] = {1, 2, 3, 4, 5};
   int size_of_array1 = (sizeof(array1)/sizeof(int));
   printf("Array before product recursion: ");
   PrintArray(array1, size_of_array1);
   int* garbage_array[2];
   Product_Recursion(array1, size_of_array1, 0, garbage_array); // always set the third argument to 0.
   printf("Array after product recursion: ");
   PrintArray(array1, size_of_array1);

   // Test Power_Recursion function
   int base = 2;
   int exponent = 4;
   int test = Power_Recursion(base, exponent); // 16
   printf("Base %d raised to the %d power is: %d\n", base, exponent, test);

   // Test Print_String_Permutations function
   char char_array[4] = "ABC";
   printf("The permutations of string %s are:\n", char_array);
   int size_of_char_array = sizeof(char_array)/sizeof(char_array[0]);
   Print_String_Permutations(char_array, size_of_char_array-1, 0);

   return 0;
}

/*

The terminal in Visual Studio Code reads the following:

Array before product recursion: 1 2 3 4 5
Array after product recursion: 120 60 40 30 24
Base 2 raised to the 4 power is: 16
The permutations of string ABC are:
ABC
ACB
BAC
BCA
CBA
CAB

*/