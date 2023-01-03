#include <stdio.h>
#include <stdlib.h>
#define N 7

//------------------------------------ algorithm ------------------------------------------------//
// Return the contiguous subsequence with the largest sum.
int* algorithm(int* array){
   int* sub_sequence = (int*)malloc(N*sizeof(int));
   int i;
   int starting_index = 0;
   int next_starting_index = 0;
   int ending_index = 0;
   int cumulative_sum = 0;
   int max_sum = 0;

   for(i = 0; i < N; i++){
      cumulative_sum += array[i]; // {1, 2, -5, -5, -5}
      if(cumulative_sum < 0){
         next_starting_index = i+1; // skip index that makes cumulative sum negative
         cumulative_sum = 0;   // reset the cumulative sum
         continue;
      }
      if(max_sum <= cumulative_sum){ // if the maximum sum is <= cumulative sum,
         starting_index = next_starting_index;
         max_sum = cumulative_sum;   // make the new max sum = cumulative sum.
         ending_index = i; // The ending index of the subsequence.
      }
   }
   int j = 0;
   for(i = starting_index; i <= ending_index; i++){
      sub_sequence[j++] = array[i];
   }
   return(sub_sequence);
}

int main(){
   int i;
   int array[N] = {1,2,-5, -5, -5,1,1};//  {5, 15, -30, 10, -5, 40, 10};
   int* largest_sum_of_contiguous_sub_sequence = algorithm(array);
   int sub_sequence_size = 2;
   printf("Subsequence: [");
   for(i = 0; i < sub_sequence_size-1; i++){
      printf("%d, ", largest_sum_of_contiguous_sub_sequence[i]);
   }
   printf("%d]\n", largest_sum_of_contiguous_sub_sequence[sub_sequence_size-1]);
}
