#include <stdio.h>
#define N 7
  
void swap(int *a, int *b) {
   int tmp = *a;
   *a = *b;
   *b = tmp;
}

void Make_Wiggly(int* array){
   int i; 
   for(i = 1; i < N; i++){
      if(((i%2==0)&&(array[i] > array[i-1])) // if even, make sure array[i] <= array[i-1]
      ||((i%2==1)&&(array[i] < array[i-1]))){ // if odd, make sure array[i] >= array[i-1]
         swap(&array[i], &array[i-1]);
      }
   }
}

void print_array(int* array, int n){
   for (int i = 0; i < n; ++i){
      printf("%d ", array[i]);
   }
   printf("\n");
}

int main(){
   int array[N] = {11, 34, 35, 5, 16, 10, 1};
   printf("Original array:\n");
   print_array(array, N);
   Make_Wiggly(array);
   printf("Wiggly array:\n");
   print_array(array, N);
}
