#include <time.h>
#include <stdio.h>

int getrand(int n){
   int random_number = rand()%n;
   random_number++; // start at 1 and include n
   return(random_number);
}

double algorithm(int n){

   int i, j;
   clock_t beginning, end;

   int* array1 = (int*)malloc(n*sizeof(int));
   int* array2 = (int*)malloc(n*sizeof(int));

   for(i = 0; i < n; i++){
      array1[i] = getrand(n);
      array2[i] = getrand(n);
   }

   int number_of_zeroes = 0;
   beginning = clock();

   for(i = 0; i < n; i++){
      for(j = 0; j < n; j++){
         if(array1[i] == array2[j]){
            array2[j] = 0;
            number_of_zeroes++;
         }
      }
   }

   end = clock();
   double runtime = ((double)(end - beginning))/CLOCKS_PER_SEC;
   return(runtime);
}

int main(){
   int i;
   double runtime;
   srand(time(NULL));

   for(i = 10; i <= 10000; i*=10){
      runtime = algorithm(i);
      printf("n: %d, runtime: %f\n", i, runtime);
   }
}