#include <stdio.h>
#define N 4

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

//------------------------------------ is_Bipartite algorithm ------------------------------------------------//
// Return 1 for TRUE. 0 for FALSE.
int is_Bipartite(int* array[N][N]){
   int i;

   // initialize Queue   
   Queue_List queue_list1;
   queue_list1.list.head = NULL;
   Queue_List** head_address_queue_list = &queue_list1.list.head;

   int color_matrix[N]; // 0 = RED. 1 = BLUE. -1 = UNASSIGNED.

   for(i = 0; i < N; i++){
      color_matrix[i] = -1; // assign values of -1 to each node meaning "UNASSIGNED".
   }

   color_matrix[0] = 0; // assign index 0 with RED. 
   enqueue_list(head_address_queue_list, 0); // enqueue first vertex.

   while(*head_address_queue_list != NULL){ // while queue is not empty
      int index = dequeue_list(head_address_queue_list);
      printf("Index: %d\n", index);
      // all vertices connected to this vertex
      for(i = index + 1; i < N; i++){ // because it is undirected, only need to search half of matrix
      // also do not need to compare array[i][i] because all diagonal elements are zero.
         if(array[index][i] == 1){ // there is a connection 
            if(color_matrix[i] == -1){ // color is UNASSIGNED, so assign a color
               if(color_matrix[index] == 0){color_matrix[i] = 1;} // assign opposite color
               else{color_matrix[i] = 0;}
               enqueue_list(head_address_queue_list, i); // enqueue first vertex.
               continue;
            }
            // If color matches, return 0 (FALSE) meaning the graph is not bipartite
            if(color_matrix[i] == color_matrix[index]){
               int free_the_memory = dequeue_list(head_address_queue_list);
               while(free_the_memory != -5){ // special value meaning the list is completely empty
                  free_the_memory = dequeue_list(head_address_queue_list);
               }
               return 0; // FALSE (not bipartite)
            }
         }
      }
   }
   return 1; // return TRUE meaning the graph is bipartite.
}

int main(){

   int array[N][N] = {{0, 1, 0, 1}, {1, 0, 1, 0}, {0, 1, 0, 1}, {1, 0, 1, 0}};  // adjacency matrix
   int is_bipartite = is_Bipartite(array);
   printf("Is Bipartite: ");
   if(is_bipartite == 1){
      printf("YES\n");
   }
   else{
      printf("NO\n");
   }
}