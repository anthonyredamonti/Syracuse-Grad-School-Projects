#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int* algorithm(int* array, int n){
   if(n < 2){
      return(array);
   }

   int i;
   int flag = 1;             // used to tell which temporary array holds the subsequence with the highest range.
                             // (1 for array1 ; 2 for array2)
   int index = 0;            // used to parse original array
   int second_index = 0;     // used to parse subsequences
   int array1_length = 0;    // length of subsequence
   int array2_length = 0;
   int array1_value = 0;     // range of subsequence
   int array2_value = 0;
   int* array1 = (int*)malloc(n*sizeof(int)); // stores subsequence
   int* array2 = (int*)malloc(n*sizeof(int));

   if(index == n-2){
      return(array); // original array is only 2 elements, so return it.
   }

   // first iteration fills array1 and array2

   // if the first two elements are equal, put them in array1
   if(array[index] == array[index+1]){
      while((index < n-1)&&(array[index] == array[index+1])){
         array1[index] = array[index];
         array1_length++;
         index++;
      }
   }

   // if all elements in the original array are equal, return it.
   if(index >= n-1){
      return(array);
   }

   // Not all elements are equal. Load array1 and array2.
   // If sequence is decreasing, enter here.
   if(array[index] >= array[index+1]){
      while((index < n-1)&&(array[index] >= array[index+1])){
         array1[index] = array[index];
         array1_length++;
         index++;
      }
      array1[index] = array[index];
      array1_length++;

      array1_value = array1[0] - array1[array1_length-1];
      
      if(index >= n-1){
         return(array); // if no more elements in original array, return.
      }
      
      // if there is a second sequence, it will be increasing. Use array2
      while((index < n-1)&&(array[index] <= array[index+1])){
         array2[second_index] = array[index];
         array2_length++;
         index++;
         second_index++;
      }
      array2[second_index] = array[index];
      array2_length++;

      array2_value = array2[array2_length-1] - array2[0];

      if(array1_value > array2_value){
         if(index >= n-1){ // if there are no more unscanned elements in original array, 
                           // and array1 has greater range than array2, free array2 and return array1.
            free(array2);
            return(array1);
         }
         flag = 1; // array1 is holding higher range. Do not change array1.
      }
      else{
         if(index >= n-1){
            free(array1);
            return(array2);
         }
         flag = 2; // array2 is holding higher range. Do not change array2.
      }
   }
   
   // Not all elements are equal. Load array1 and array2.
   // If sequence is increasing, enter here.
   else{
      while((index < n-1)&&(array[index] <= array[index+1])){
         array1[index] = array[index];
         array1_length++;
         index++;
      }
      array1[index] = array[index];
      array1_length++;

      array1_value = array1[array1_length-1] - array1[0];

      if(index >= n-1){
         return(array); // handles [5, 5, 3]
      }

      while((index < n-1)&&(array[index] >= array[index+1])){
         array2[second_index] = array[index];
         array2_length++;
         index++;
         second_index++;
      }
      array2[second_index] = array[index];
      array2_length++;

      array2_value = array2[0] - array2[array2_length-1];

      if(array1_value > array2_value){
         if(index >= n-1){
            free(array2);
            return(array1);
         }
         flag = 1; // array1 is holding higher range. Do not change array1.
      }
      else{
         if(index >= n-1){
            free(array1);
            return(array2);
         }
         flag = 2; // array2 is holding higher range. Do not change array2.
      }
   }
   
   while(index < n-1){
      // do not edit array1.
      if(flag == 1){
         // if the sequence is increasing, continue in that direction.
         if(array[index] <= array[index+1]){
            second_index = 0;
            array2_length = 0;
            while((index < n-1)&&(array[index] <= array[index+1])){
               array2[second_index] = array[index];
               array2_length++;
               index++;
               second_index++;
            }
            array2[second_index] = array[index];
            array2_length++;
            array2_value = array2[array2_length-1] - array2[0];
         }
         // if the sequence is decreasing, continue in that direction.
         else{
            second_index = 0;
            array2_length = 0;
            while((index < n-1)&&(array[index] >= array[index+1])){
               array2[second_index] = array[index];
               array2_length++;
               index++;
               second_index++;
            }
            array2[second_index] = array[index];
            array2_length++;
            array2_value = array2[0] - array2[array2_length-1];
         }
         // if array2 has greater range, set flag to 2.
         if(array2_value > array1_value){
            flag = 2;
         }
      }
      // do not edit array2.
      else{
         // if the sequence is increasing, continue in that direction.
         if(array[index] <= array[index+1]){
            second_index = 0;
            array1_length = 0;
            while((index < n-1)&&(array[index] <= array[index+1])){
               array1[second_index] = array[index];
               array1_length++;
               index++;
               second_index++;
            }
            array1[second_index] = array[index];
            array1_length++;
            array1_value = array1[array1_length-1] - array1[0];
         }
         // if the sequence is decreasing, continue in that direction.
         else{
            second_index = 0;
            array1_length = 0;
            while((index < n-1)&&(array[index] >= array[index+1])){
               array1[second_index] = array[index];
               array1_length++;
               index++;
               second_index++;
            }
            array1[second_index] = array[index];
            array1_length++;

            array1_value = array1[0] - array1[array1_length-1];
         }
         // if array1 has greater range, set flag to 1.
         if(array1_value > array2_value){
            flag = 1;
         }
      }
   }

   if(flag == 1){
      free(array2);
      return(array1);
   }
   else{
      free(array1);
      return(array2);
   }
}

int main(){
   clock_t beginning, end;
   int i;
   int array[7] = {2, -3, 0, 5, -2, -5, -1}; 
   int n = 7;
   for(i = 0; i < n; i++){
      array[i]= i;
   }
   
   printf("original array: [");
   for(i = 0; i < n-1; i++){
      printf("%d, ", array[i]);
   }
   printf("%d]\n", array[n-1]);
   
   beginning = clock();
   int* new_array = algorithm(array, n);
   end = clock();

   double runtime = ((double)(end - beginning))/CLOCKS_PER_SEC;
   
   int new_n = 3;
   printf("new array: [");
   for(i = 0; i < new_n-1; i++){
      printf("%d, ", new_array[i]);
   }
   printf("%d]\n", new_array[new_n-1]);
   printf("Runtime: %f\n", runtime);

}