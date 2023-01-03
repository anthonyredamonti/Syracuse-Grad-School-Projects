#include <stdio.h>
#include <stdlib.h>
#define N 6

// ------------------------------ STRUCTS ------------------------------------//

typedef struct listNode {
   int value;
   struct listNode* next;
} Node;

typedef struct list{
   Node* head;
} List;

typedef struct queue_list{
   List list;
} Queue_List;

// ----------------------------- QUEUE LIST FUNCTIONS --------------------------------//
void enqueue_list(List** head, int value){
   Node* new_node = NULL;
   Node* last_node = NULL;
   new_node = (Node*)(malloc(sizeof(Node)));
   new_node->value = value;
   new_node->next = NULL;
   // if list is empty insert new node at the head. 
   if(*head == NULL){//if address for head node is NULL
      *head = new_node;
      return;
   }
   // start at the head looking for the last node, then insert new node after it.
   last_node = *head;
   while(last_node->next!=NULL){
      last_node = last_node->next;
   }
   last_node->next = new_node;
}

int dequeue_list(List** head){
   if(*head == NULL){
      //printf("Can not dequeue. Queue list is already empty\n");
      return -5; // special value meaning the list is empty
   }
   Node* temp = NULL;
   temp = *head;
   int value = temp->value;
   *head = temp->next;
   free(temp);
   return(value);
}

//------------------------------------ find_Number_Of_Shortest_Paths algorithm ------------------------------------------------//
// Return 1 for TRUE. 0 for FALSE.
int find_Number_Of_Shortest_Paths(int* array[N][N], int vertex_1, int vertex_2){
   int i, minimum_distance, number_of_shortest_paths;

   // initialize Queue   
   Queue_List queue_list1;
   queue_list1.list.head = NULL;
   Queue_List** head_address_queue_list = &queue_list1.list.head;

   int distance_array[N];
   int has_been_queued[N];

   for(i = 0; i < N; i++){
      has_been_queued[i] = 0;
      distance_array[i] = 1000000000; // assign 1,000,000,000 (one billion) to represent infinity
   }

   minimum_distance = 1000000000; // initialize minimum distance with infinity
   number_of_shortest_paths = 0;

   distance_array[vertex_1] = 0; // initialize vertex_1 with distance 0
   enqueue_list(head_address_queue_list, vertex_1); // enqueue vertex_1.
   has_been_queued[vertex_1] = 1;

   while(*head_address_queue_list != NULL){ // while queue is not empty
      int index = dequeue_list(head_address_queue_list);
      printf("Index: %d\n", index);
      
      for(i = 0; i < N; i++){
         if(array[index][i] == 1){ // there is a connection 
            if(has_been_queued[i] == 1){continue;} // do not queue a vertex that has already been queued
            
            if(i == vertex_2){ // we have reached destination vertex.
               distance_array[i] = distance_array[index] + 1;
               if(distance_array[i] < minimum_distance){
                  minimum_distance = distance_array[i];
                  number_of_shortest_paths = 1; // reset shortest paths counter to 1
                  continue;
               }
               if(distance_array[i] == minimum_distance){ // if equal to current min, increment shortest paths counter.
                  number_of_shortest_paths += 1;
                  continue;
               }
               continue; // if there is a path but it's longer than current minimum, ignore it.
            }

            if(distance_array[i] == 1000000000){
               distance_array[i] = distance_array[index] + 1;
               enqueue_list(head_address_queue_list, i);
               has_been_queued[i] = 1;
               continue;
            }
         }
      }
   }

   return(number_of_shortest_paths);
}

int main(){

   int array[N][N] = {{0, 1, 0, 0, 0, 1}, 
                      {1, 0, 1, 0, 0, 0},
                      {0, 1, 0, 1, 0, 1}, 
                      {0, 0, 1, 0, 1, 0}, 
                      {0, 0, 0, 1, 0, 1}, 
                      {1, 0, 1, 0, 1, 0}};  // adjacency matrix

   int vertex_1 = 1;
   int vertex_5 = 5;

   int number_of_shortest_paths = find_Number_Of_Shortest_Paths(array, vertex_1, vertex_5);
   printf("Number of shortest paths: %d\n", number_of_shortest_paths);
}