#include <stdio.h>
#include <stdlib.h>
#define N 10
#define M 6

//------------------------------------ algorithm ------------------------------------------------//
// Return the length of the longest common substring.
int algorithm(char* string1, char* string2){
   int i, j;
   int array[N][M];
   
   int max_value = 0;

   // fill in 0 or 1 for first row
   for(i = 0; i < 1; i++){
      for(j = 0; j < M; j++){
         if(string1[i] == string2[j]){
            array[i][j] = 1;
            max_value = 1;
         }
         else{
            array[i][j] = 0;
         }
      }
   }

   // fill in 0 or 1 for first column
   for(i = 1; i < N; i++){
      for(j = 0; j < 1; j++){
         if(string1[i] == string2[j]){
            array[i][j] = 1;
            max_value = 1;
         }
         else{
            array[i][j] = 0;
         }
      }
   }

   // fill in rest of array
   for(i = 1; i < N; i++){
      for(j = 1; j < M; j++){
         if(string1[i] == string2[j]){
            array[i][j] = array[i-1][j-1] + 1;
            if(array[i][j] > max_value){
               max_value = array[i][j];
            }
         }
         else{
            array[i][j] = 0;
         }
      }
   }

   return(max_value);
}

int main(){
   char string1[N] = {'a', 'p', 'p', 'l', 'e', 's', 'a', 'u', 'c', 'e'};
   char string2[M] = {'l', 'e', 's', 'a', 'z', 'z'};   
   int length = algorithm(string1, string2);
   printf("Length of the longest common substring: %d\n", length);
}
