#include <stdio.h>
#include <stdlib.h>
#define N 4

// function that returns base^exponent
int power_func(int base, int exponent){
   int i;
   int answer = base; 
   for(i = 1; i < exponent; i++){
      answer *= base;
   }
   return(answer);
}

//------------------------------------ algorithm ------------------------------------------------//
// Does there exist a subset of array s.t. the sum of the subset equals value?
// Return 1 for TRUE and 0 for FALSE.
int SubsetSum(int* array, int value){
   int i, j;
   int range = power_func(2, N); // 2^N
   int** binary_array = (int**)malloc(range * sizeof(int*));
   int sum = 0;
   for(i = 0; i < range; i++){
      binary_array[i] = (int*)malloc(N*sizeof(int));
   }
   
   // construct binary table
   for(i = 0; i < range; i++){
      for(j = 0; j < N; j++){
         int num1 = power_func(2, j+1);
         int num2 = num1/2;
         if((i%num1) >= num2){
            binary_array[i][j] = 1;
         }
         else{
            binary_array[i][j] = 0;
         }
         sum += (array[j] * binary_array[i][j]);
      }
      if(sum == value){
         return(1);
      }
      sum = 0;
   }
   return(0);   
}

//---------------------algorithm-------------------------//
// Can array be split into 2 subsets where their cumulative sums are equal?
// Return 1 for TRUE and 0 for FALSE.
int EqualPartition(int* array){
   int i;
   int SUM = 0;
   int half_SUM = 0;
   for(i = 0; i < N; i++){
      SUM += array[i];
   }

   half_SUM = SUM/2;

   // if half the cumulative sum is odd, return FALSE.
   if((half_SUM % 2) != 0){
      return 0;
   }

   return(SubsetSum(array, half_SUM));
}


int main(){
   int array[N] = {5, 2, 0, -3};
   int number = 3;
   int boolean_value = EqualPartition(array);
   if(boolean_value == 1){
      printf("TRUE\n");
   }
   else{
      printf("FALSE\n");
   }   
}
