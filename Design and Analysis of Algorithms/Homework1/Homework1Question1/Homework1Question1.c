#include <time.h>

double algorithm(int n){
   clock_t beginning, end;
   int a, b;
   int count = 12345;
   
   beginning = clock();
   for(a = 1; a < n; a++){
      for(b = a+1; b < n; b++){
         count *= 1;
         //printf("a: %d, b: %d ", a, b);
      }
   }
   end = clock();
   double runtime = ((double)(end - beginning))/CLOCKS_PER_SEC;
   return(runtime);
}

int main(){
   int i;
   double runtime;
   for(i = 10; i <= 10000; i*=10){
      runtime = algorithm(i);
      printf("n: %d, runtime: %f\n", i, runtime);
   }
}