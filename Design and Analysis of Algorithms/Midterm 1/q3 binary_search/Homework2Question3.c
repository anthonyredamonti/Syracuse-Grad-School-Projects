#include <time.h>
#include <stdio.h>

// recursively split the input into 2 halves until either answer found or not found.
int binary_search(int* array, int left, int right){

   int range = right-left;
   int midpoint = left + (range/2);

   if(array[midpoint] == midpoint){ // if an answer is found, return it.
      return midpoint;
   }
   
   // if no answer has been found, return -1.
   // If the array cannot be split anymore, return.
   if(midpoint == left){ 
      return -1;
   }

   // if the index is greater than the value, do not look beyond the index.
   if(array[midpoint] < midpoint){
      return(binary_search(array, left, midpoint));
   }

   // if the index is less than the value, do not look before the index.
   if(array[midpoint] > midpoint){
      return(binary_search(array, midpoint, right));
   }
}

int main(){
   int i;
   int array[7] = {12, 7, 6, 3, -2, -5, -11};
   int n = 7;
   printf("original array: [");
   for(i = 0; i < n-1; i++){
      printf("%d, ", array[i]);
   }
   printf("%d]\n", array[n-1]);
   int index = binary_search(array, 0, n);
   printf("index: %d\n", index);
}