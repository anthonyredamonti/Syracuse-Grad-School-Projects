#include <stdio.h>
#include <stdlib.h>
#define N 4

int Backtracking_algorithm(int* array, int value, int index){
   int i, answer;
   for(i = index; i < N; i++){
      if(value - array[i] == 0){
         return(1);
      }
   }
   if(index+1 < N){
      if(value-array[index] > 0){
         return Backtracking_algorithm(array, value-array[index], index+1);
      }
      if(value-array[index] < 0){
         return Backtracking_algorithm(array, value, index+1);
      }
   }
   return(0);
}

int main(){
   int array[N] = {1, 0, 1, 1};
   int number = 3;
   int answer = Backtracking_algorithm(array, number, 0);
   if(answer == 1){
      printf("Sum found.\n");
   }
   else{
      printf("Sum not found.\n");
   }
}
