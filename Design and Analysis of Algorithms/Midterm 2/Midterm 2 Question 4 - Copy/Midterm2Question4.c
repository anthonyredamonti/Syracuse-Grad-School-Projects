#include <stdio.h>
#include <stdlib.h>

#define N 12 // number of activities

//-----------STRUCTS------------//

typedef struct listActivity {
   int start_time;
   int finish_time;
   struct listNode* prev;
   struct listNode* next;
} Activity;

typedef struct list{
   Activity* head;
} List;

//--------------LIST FUNCTIONS---------------//

// push activities on a list.
void push_list(List** head, int start_time, int finish_time){
   Activity* new_activity = NULL;
   Activity* last_activity = NULL;
   new_activity = (Activity*)(malloc(sizeof(Activity)));
   new_activity->start_time = start_time;
   new_activity->finish_time = finish_time;
   new_activity->next = NULL;
   new_activity->prev = NULL;

   // if list is empty insert new node at the head. 
   if(*head == NULL){//if address for head node is NULL
      *head = new_activity;
      return;
   }

   // start at the head looking for the last node, then insert new node after it.
   last_activity = *head;
   while(last_activity->next!=NULL){
      last_activity = last_activity->next;
   }
   last_activity->next = new_activity;
   new_activity->prev = last_activity;
}

void remove_list(Activity** activity1){

   Activity* act1 = *activity1;
   printf("removing finish time %d\n", act1->finish_time);

   if((act1->prev == NULL)&&(act1->next == NULL)){
      free(act1);
      return;
   }
   Activity* act2;
   if(act1->prev == NULL){
      act2 = act1->next;
      act2->prev = NULL;
      free(act1);
      return;
   }
   if(act1->next == NULL){
      act2 = act1->prev;
      act2->next = NULL;
      free(act1);
      return;
   }
   Activity* act3;
   act2 = act1->prev;
   act3 = act1->next;
   act2->next = act3;
   act3->prev = act2;
   free(act1);
   return;
}

//------------------------------------ GREEDY ALGORITHM ------------------------------------------------//
// Return the maximum number of activities able to be performed by a single person.
int greedy_algorithm(int* start_times, int* finish_times){
   int i, activity_count;
   int lowest_index = 0; // initialize index of activity with the lowest finish time.
   int difference = 0;

   // push activities into doubly linked list
   List list_1;
   list_1.head = NULL;
   List** head_address = &list_1.head;
   for(int i = 0; i < N; i++){
      push_list(head_address, start_times[i], finish_times[i]);
   }

   Activity* lowest_activity = *head_address;
   Activity* walk_list = *head_address;

   // find the activity with the lowest possible finish time
   while(walk_list->next!=NULL){
      if(walk_list->finish_time < lowest_activity->finish_time){
         lowest_activity = walk_list;
         //walk_list = walk_list->next;
         //printf("lowest: %d\n", lowest_activity->finish_time);
         //remove_list(&lowest_activity);
         //continue;
      }
      walk_list = walk_list->next;
   }

   remove_list(&lowest_activity);

   //lowest_activity = *head_address;
   walk_list = *head_address;

   // find the activity with the lowest possible finish time
   while(walk_list->next!=NULL){
      printf("list: %d\n", walk_list->finish_time);
      walk_list = walk_list->next;
   }
   printf("list: %d\n", walk_list->finish_time);

   return(activity_count);
}

int main(){
   int start_times[N] =  {1, 3, 2, 6, 6, 8, 4, 4, 9,  10, 2, 7};
   int finish_times[N] = {6, 5, 7, 8, 9, 9, 7, 7, 12, 14, 5, 10}; 
   int max_number_activities = greedy_algorithm(start_times, finish_times);
   printf("Maximum Number of Activities: %d\n", max_number_activities);   
}
