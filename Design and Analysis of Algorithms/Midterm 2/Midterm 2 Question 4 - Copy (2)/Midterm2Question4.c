#include <stdio.h>
#include <stdlib.h>

#define N 12 // number of activities

void swap_elements(int** array, int index1, int index2){
   int* array1= *array;
   int temp = array1[index1];
   array1[index1] = array1[index2];
   array1[index2] = temp;
}

//------------------------------------ GREEDY ALGORITHM ------------------------------------------------//
// Return the maximum number of activities able to be performed by a single person.
int greedy_algorithm(int* start_times, int* finish_times){
   int i;
   int index_min = 0; // index at lowest finish time
   int count = 1;
   int** starttimes1 = &start_times;
   int** finishtimes1 = &finish_times;

   for(i = 1; i < N; i++){
      if(finish_times[i] < finish_times[index_min]){
         index_min = i;
      }
   }

   swap_elements(finishtimes1, index_min, N-1);
   swap_elements(starttimes1, index_min, N-1);
   printf("%d %d\n", start_times[N-count], finish_times[N-count]);

   index_min = -1;
   int activity_found = 0;

   for(i = 0; i < N-count; i++){
      // check for eligibility
      if(finish_times[N-count] <= start_times[i]){
         activity_found = 1;
         if(index_min == -1){
            index_min = i;
         }
         if(finish_times[i] < finish_times[index_min]){
            index_min = i;
         }
      }

      // end of this iteration
      if(i == N-count-1){
         if(activity_found == 0){
            return(count);
         }

         count++;
         swap_elements(finishtimes1, index_min, N-count);
         swap_elements(starttimes1, index_min, N-count);
         printf("%d %d\n", start_times[N-count], finish_times[N-count]);
         i = -1;
         activity_found = 0;
         index_min = -1;
      }
   }
   return(count);
}

int main(){
   int start_times[N] =  {1, 3, 2, 6, 6, 8, 4, 4, 9,  10, 2, 7};
   int finish_times[N] = {6, 5, 7, 8, 9, 9, 7, 7, 12, 14, 6, 10}; 
   int max_number_activities = greedy_algorithm(start_times, finish_times);
   printf("Maximum Number of Activities: %d\n", max_number_activities);   
}
