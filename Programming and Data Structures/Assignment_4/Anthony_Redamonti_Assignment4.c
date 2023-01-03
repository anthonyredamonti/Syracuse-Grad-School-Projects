// Anthony Redamonti
// 8-2-2020
// This is Assignment 4 for Week 4 written in C. Questions 1 and 2 are answered.

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// function declarations
void setDifference(int* S, int countS, int* T, int countT, int** R, int* countR);
int properSubset(int* s, int counts, int* T, int countT);

// test setDifference function (S - T)
void setDifference(int* S, int countS, int* T, int countT, int** R, int* countR){
   int i, j;
   int match_found = 0;
   *countR = 0;

   // First we will determine the size of the result.
   for(i = 0; i < countS; i++){
      match_found = 0;
      for(j = 0; j < countT; j++){
         if(S[i]==T[j]){
            match_found = 1;
            break;
         }
      }
      if (match_found == 0){
            *countR += 1;
      }
   }
   
   // Create the new array in dynamically allocated memory using malloc
   *R = (int*) malloc(*countR * sizeof(int));
   
   // iterate through the sets again, but this time fill resulting array "R" with elements.
   *countR = 0;
   for(i = 0; i < countS; i++){
      match_found = 0;
      for(j = 0; j < countT; j++){
         if(S[i]==T[j]){
            match_found = 1;
            break;
         }
      }
      if (match_found == 0){
            *(*R+*countR) = S[i];
            *countR += 1;
      }
   }
}

// The properSubset function will determine if set "s" is a proper subset of set "T".
// It will return 0 for NO and 1 for YES.
int properSubset(int* s, int counts, int* T, int countT){
   int i, j;
   int size_of_s = counts;
   
   // check if there is at least one element in set T that is not in set s
   int at_least_one = 0;
   for(i = 0; i < countT; i++){
      int match_found = 0;
      for(j = 0; j < size_of_s; j++){
         if(T[i]==s[j]){
            match_found = 1;
            break;
         }
      }
      if (match_found == 0){
            at_least_one = 1; // at least one element in T is not in s
            break;
      }
   }

   if(at_least_one == 0){
      printf("There are no elements in T that are not in s. Therefore, s is not a proper subset of T.\n");
      return 0;
   }

   // check if all of the elements of set s are in set T (if s is a subset at all)
   for(i = 0; i < size_of_s; i++){
      int match_found = 0;
      for(j = 0; j < countT; j++){
         if(s[i]==T[j]){
            match_found = 1;
            break;
         }
      }
      if (match_found == 0){
            printf("There exists at least one element in s that is not in T. Therefore, s is not a subset of T.\n");
            return 0; 
      }
   }
   printf("s is a proper subset of T.\n");
   return 1;
}

void PrintArray(int* array, int number_of_elements_to_print){
      int i;
      for(i = 0; i < number_of_elements_to_print; i++){
      printf("%d ", array[i]);
   }
   printf("\n");
}

int main() {

   int i = 0;

   int array1[] = {1, 2, 3, 44, 10, 11};
   int array2[] = {1, 2, 3, 44};
   int size_of_array1 = (sizeof(array1)/sizeof(int));
   int size_of_array2 = (sizeof(array2)/sizeof(int));

   int array3[] = {1, 2, 4, 6, 10};
   int array4[] = {1, 2, 4, 6, 10};
   int size_of_array3 = (sizeof(array3)/sizeof(int));
   int size_of_array4 = (sizeof(array4)/sizeof(int));

   int array5[] = {1, 3, 5, 9, 10};
   int array6[] = {1, 4, 5, 65, 200, 10};
   int size_of_array5 = (sizeof(array5)/sizeof(int));
   int size_of_array6 = (sizeof(array6)/sizeof(int));

   int arrayresult = 0;
   int size = 0;
   int* array_result_ptr = &arrayresult;
   int** result = &array_result_ptr;
   int* size_of_result = &size;

   printf("The elements in the array1 are: ");
   PrintArray(array1, size_of_array1);
   printf("The elements in the array2 are: ");
   PrintArray(array2, size_of_array2);

   setDifference(array1, size_of_array1, array2, size_of_array2, result, size_of_result);
   printf("array1 - array2 = R.  The %d elements in R are: ", *size_of_result);
   PrintArray(*result, *size_of_result);
   free(*result);

   int is_proper_subset = properSubset(array2, size_of_array2, array1, size_of_array1);
   printf("Is array2 a proper subset of array1? 0 for NO and 1 for YES: %d\n", is_proper_subset);

   printf("\n");

   printf("The elements in the array3 are: ");
   PrintArray(array3, size_of_array3);
   printf("The elements in the array4 are: ");
   PrintArray(array4, size_of_array4);

   setDifference(array3, size_of_array3, array4, size_of_array4, result, size_of_result);
   printf("array3 - array4 = R.  The %d elements in R are: ", *size_of_result);
   PrintArray(*result, *size_of_result);
   free(*result);

   is_proper_subset = properSubset(array4, size_of_array4, array3, size_of_array3);
   printf("Is array4 a proper subset of array3? 0 for NO and 1 for YES: %d\n", is_proper_subset);

   printf("\n");

   printf("The elements in the array5 are: ");
   PrintArray(array5, size_of_array5);
   printf("The elements in the array6 are: ");
   PrintArray(array6, size_of_array6);

   setDifference(array5, size_of_array5, array6, size_of_array6, result, size_of_result);
   printf("array5 - array6 = R.  The %d elements in R are: ", *size_of_result);
   PrintArray(*result, *size_of_result);
   free(*result);

   is_proper_subset = properSubset(array6, size_of_array6, array5, size_of_array5);
   printf("Is array6 a proper subset of array5? 0 for NO and 1 for YES: %d\n", is_proper_subset);

   return 0;
}

/*

The terminal in Visual Studio Code reads the following:

The elements in the array1 are: 1 2 3 44 10 11
The elements in the array2 are: 1 2 3 44
array1 - array2 = R.  The 2 elements in R are: 10 11
s is a proper subset of T.
Is array2 a proper subset of array1? 0 for NO and 1 for YES: 1

The elements in the array3 are: 1 2 4 6 10
The elements in the array4 are: 1 2 4 6 10
array3 - array4 = R.  The 0 elements in R are:
There are no elements in T that are not in s. Therefore, s is not a proper subset of T.
Is array4 a proper subset of array3? 0 for NO and 1 for YES: 0

The elements in the array5 are: 1 3 5 9 10
The elements in the array6 are: 1 4 5 65 200 10
array5 - array6 = R.  The 2 elements in R are: 3 9
There exists at least one element in s that is not in T. Therefore, s is not a subset of T.
Is array6 a proper subset of array5? 0 for NO and 1 for YES: 0

*/