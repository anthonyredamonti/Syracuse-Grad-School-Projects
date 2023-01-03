#include <time.h>
#include <stdio.h>

int* algorithm(int* array, int n){
   if(n < 2){
      return(array);
   }

   int i;
   int index = 0;
   int max_value;

   int* array1 = (int*)malloc(n*sizeof(int));
   int* final_array;
   int array1_length = 0;
   int array1_value = 0;
   int second_index = 0;

   // first iteration fills array1 and array2

   // if the first two elements are equal, put them in array1
   if(array[index] == array[index+1]){
      while((index < n-1)&&(array[index] == array[index+1])){
         array1[index] = array[index];
         array1_length++;
         index++;
      }
   }
   if(index < n-1){
      if(array[index] > array[index+1]){
         while((index < n-1)&&(array[index] >= array[index+1])){
            array1[index] = array[index];
            array1_length++;
            index++;
         }
         array1[index] = array[index];
         array1_length++;
         array1_value = array1[0] - array1[array1_length-1];

         if(array1_value > max_value){
            max_value = array1_value;
         }
         else{
            free(array1);
         }
      }
   
      if(array[index] < array[index+1]){
         while((index < n-1)&&(array[index] <= array[index+1])){
            array1[index] = array[index];
            array1_length++;
            index++;
         }
         array1[index] = array[index];
         array1_length++;

         array1_value = array1[array1_length-1] - array1[0];

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
            free(array2);
            return(array1);
         }
         else{
            free(array1);
            return(array2);
         }
      }
   }
}

int main(){
   int i;
   int array[7] = {2, -3, 0, 5, -2, -5, -1}; 
   for(i = 0; i < 7; i++){
      printf("original array[%d] = %d\n", i, array[i]);
   }

   int* new_array = algorithm(array, 0, 7, 0);
   for(i = 0; i < 7; i++){
      printf("new array[%d] = %d\n", i, new_array[i]);
   }
}