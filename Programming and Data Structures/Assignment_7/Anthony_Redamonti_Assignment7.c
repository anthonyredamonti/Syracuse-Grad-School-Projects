// Anthony Redamonti
// 8-21-2020
// This is Assignment 7 for Week 7 written in C. Questions 1, 2, 3, 4, and bonus are answered.

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// ------------------------------ STRUCTS ------------------------------------//

typedef struct listNode {
   int value;
   struct listNode* next;
} Node;

typedef struct list{
   Node* head;
} List;

typedef struct stack_array{
   int top;       // index of the element at the top of the stack  
   int size;      // size of the array
   int* array;    // pointer to (first element of) array
} Stack_Array;

typedef struct stack_list{
   List list;     // list contains first and second node addresses
} Stack_List;

typedef struct queue_list{
   List list;
} Queue_List;

// ----------------------- removeEveryOtherNode FUNCTION ----------------------------//

void removeEveryOtherNode(List list){

   // if the list is empty then return
   if(list.head == NULL){
      return;
   }
   // if the list only has one node then return
   if(list.head->next == NULL){
      return;
   }

   Node* pointer = list.head->next;
   int odd = 0;
   Node* original_first_node_address = list.head;

   while(pointer != NULL){
      pointer = list.head->next;
      list.head->next = pointer->next;
      free(pointer);
      list.head = list.head->next;
      if(list.head == NULL){
         list.head = original_first_node_address;
         return;
      }
      pointer = list.head->next;
   }
   list.head = original_first_node_address;
}

// ----------------------------- STACK ARRAY FUNCTIONS --------------------------------//

// copy array1 into array2
void copy_array(int* array1, int size_of_array1, int* array2, int size_of_array2){
   if(size_of_array1 > size_of_array2){
      printf("array1 is bigger than array2 and therefore cannot be copied.\n");
      return;
   }
   for(int i = 0; i < size_of_array1; i++){
      array2[i] = array1[i];
   }
}

void push_stack_array(Stack_Array* stack, int value){

   stack->top++; // -1 + 1 = 0 for first element in array
   
   // if no more room, create new array double in size
   if(stack->top == stack->size){
      int temp_size = stack->size * 2;
      int* array_temp = (int*)(malloc(temp_size*(sizeof(int))));
      copy_array(stack->array, stack->size, array_temp, temp_size);
      free(stack->array);
      stack->array = array_temp;
      stack->size = temp_size;
   }

   // push value on top of stack
   stack->array[stack->top] = value;
}

void pop_stack_array(Stack_Array* stack){
   if(stack->top == -1){
      printf("stack array already empty\n");
      return;
   }
   stack->top--;
}

// ----------------------------- STACK LIST FUNCTIONS --------------------------------//

void push_stack_list(Stack_List** head, int value){
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

void pop_stack_list(Stack_List** head){
   if(*head == NULL){
      printf("Can not pop. List is already empty\n");
      return;
   }
   Node* last_node = NULL;
   Node* second_to_last_node = NULL;
   last_node = *head;
   if(last_node->next == NULL){
      free(last_node);
      *head = NULL;
      return;
   }
   second_to_last_node = last_node;
   last_node = last_node->next;
   while(last_node->next!=NULL){
      second_to_last_node = last_node;
      last_node = last_node->next;
   }
   free(last_node);
   second_to_last_node->next = NULL;
}

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

void dequeue_list(List** head){
   if(*head == NULL){
      printf("Can not dequeue. Queue list is already empty\n");
      return;
   }
   Node* temp = NULL;
   temp = *head;
   *head = temp->next;
   free(temp);
}

//--------------MISCELLANEOUS FUNCTIONS---------------//

// push nodes on a list.
void push_list(List** head, int value){
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

// This function prints the contents of a linked list
void printList(List list) 
{
   if(list.head == NULL){
      printf("Could not print. Head node pointer is NULL (List is empty)\n");
      return;
   } 
   Node* head = list.head;
   while (list.head->next != NULL){ 
      printf("%d ", list.head->value); 
      list.head = list.head->next; 
   } 
   printf("%d\n", list.head->value);
   list.head = head;
}

void PrintArray(int* array, int number_of_elements_to_print){
      int i;
      for(i = 0; i < number_of_elements_to_print; i++){
      printf("%d ", array[i]);
   }
   printf("\n");
}

// sort a linked list
void sortList(List** head){
   if(*head == NULL){
      printf("Cannot sort empty list.\n");
      return;
   }
   Node* original_head_address = *head;
   if(original_head_address->next == NULL){
      printf("List has only one Node.\n");
      return;
   }

   // determine the size of the list.
   Node* counting_node = *head;
   int count = 1;
   while(counting_node->next != NULL){
      counting_node = counting_node->next;
      count++;
   }
   
   Node* new_node = NULL;
   Node** head_new_node = &new_node;
   Node* head_outerloop = *head;
   Node* min = NULL;
   Node* head_innerloop = NULL;
   Node* behind_min = NULL;
   int outer_loop_counter = 0;
   int inner_loop_counter = 0;
   int index_of_min = 0;

   while(outer_loop_counter != count){
      outer_loop_counter++;
      min = head_outerloop;
      head_innerloop = head_outerloop;
      while(head_innerloop->next!=NULL){
         inner_loop_counter++;
         // if the next node's value is smaller than the min value, the min will be the next node.
         if(head_innerloop->next->value < min->value){
            behind_min = head_innerloop;
            min = head_innerloop->next;
            index_of_min = inner_loop_counter;
         }
         head_innerloop = head_innerloop->next;
      }

      // push the min onto the new list
      push_stack_list(head_new_node, min->value);

      // if first node is lowest index in search range, there is no previous node.
      if(index_of_min == 0){
         Node* temp = NULL;
         temp = head_outerloop;
         head_outerloop = temp->next;
         free(temp);
      }
      // the min was not the first node in the search range, so the previous node exists.
      else{
         behind_min->next = min->next;
         free(min);
      }
      index_of_min = 0;
      inner_loop_counter = 0; // reset the index and inner loop counter variables to zero.
   }
   *head = **&head_new_node; // link the head of the new list with the head of the original list.
}

int main() {

// -------------- Test removeEveryOtherNode function ---------------- //

   printf("testing removeEveryOtherNode function\n");

   List list_1;
   list_1.head = NULL;
   List** head_address = &list_1.head;
   for(int i = 0; i < 7; i++){
      push_list(head_address, i);
   }
   printf("Original Odd Numbered List Before Removing Every Other Node\n");
   printList(list_1);

   removeEveryOtherNode(list_1);
   printf("Altered List\n");
   printList(list_1);
   printf("\n");

   List list_2;
   list_2.head = NULL;
   List** head_address2 = &list_2.head;
   for(int i = 0; i < 10; i++){
      push_list(head_address2, i);
   }
   printf("Original Even Numbered List Before Removing Every Other Node\n");
   printList(list_2);

   removeEveryOtherNode(list_2);
   printf("Altered List\n");
   printList(list_2);
   printf("\n");

// ------------------ Test Stack Array Functions ----------------------- //
   Stack_Array array1;
   array1.size = 10;
   array1.top = -1; // empty 
   array1.array = (int*)(malloc(array1.size * sizeof(Stack_Array)));
   Stack_Array* pntr = &array1;
   
   printf("Pushing 5 Nodes to Stack Array\n");
   
   for(int i = 0; i < 5; i++){
      push_stack_array(pntr, i);
   }
   PrintArray(array1.array, array1.top+1);
   
   printf("Popping 3 Nodes from Stack Array\n");
   for(int i = 0; i < 3; i++){
      pop_stack_array(pntr);
   }
   PrintArray(array1.array, array1.top+1);

   printf("Pushing 5 Nodes to Stack Array\n");
   for(int i = 0; i < 5; i++){
      push_stack_array(pntr, i);
   }

   PrintArray(array1.array, array1.top+1);

// ------------------ Test Stack List Functions ----------------------- //

   Stack_List stack_list_1;
   stack_list_1.list.head = NULL;
   Stack_List** head_address_stack_list = &stack_list_1.list.head;
   printf("Pushing to 5 Nodes to Stack List\n");
   for(int i = 0; i < 5; i++){
      push_stack_list(head_address_stack_list, i);
   }
   printList(stack_list_1.list);
   printf("Popping 3 Nodes from Stack List\n");
   for(int i = 0; i < 3; i++){
      pop_stack_list(head_address_stack_list);
   }
   printList(stack_list_1.list);
   printf("Pushing 5 Nodes to Stack List\n");
   for(int i = 0; i < 5; i++){
      push_stack_list(head_address_stack_list, i);
   }
   printList(stack_list_1.list);

// ---------------- Test Queue List Functions -------------------------- //

   Queue_List queue_list1;
   queue_list1.list.head = NULL;
   Queue_List** head_address_queue_list = &queue_list1.list.head;
   printf("Enqueueing 5 Nodes to Queue List\n");
   for(int i = 0; i < 5; i++){
      enqueue_list(head_address_queue_list, i);
   }
   printList(queue_list1.list);
   printf("Dequeueing 2 Nodes to Queue List\n");
   for (int i = 0; i < 2; i++){
      dequeue_list(head_address_queue_list);
   }
   printList(queue_list1.list);
   printf("Enqueueing 5 Nodes to Queue List\n");
   for(int i = 0; i < 5; i++){
      enqueue_list(head_address_queue_list, i);
   }
   printList(queue_list1.list);

//------------------------- Test Sorting Function ----------------------------//

   printf("Original Unsorted List\n");
   printList(stack_list_1.list);

   sortList(head_address_stack_list);
   printf("Sorted List\n");
   printList(stack_list_1.list);
   
   return 0;
}

/*

testing removeEveryOtherNode function
Original Odd Numbered List Before Removing Every Other Node
0 1 2 3 4 5 6
Altered List
0 2 4 6

Original Even Numbered List Before Removing Every Other Node
0 1 2 3 4 5 6 7 8 9
Altered List
0 2 4 6 8

Pushing 5 Nodes to Stack Array
0 1 2 3 4
Popping 3 Nodes from Stack Array
0 1
Pushing 5 Nodes to Stack Array
0 1 0 1 2 3 4
Pushing to 5 Nodes to Stack List
0 1 2 3 4
Popping 3 Nodes from Stack List
0 1
Pushing 5 Nodes to Stack List
0 1 0 1 2 3 4
Enqueueing 5 Nodes to Queue List
0 1 2 3 4
Dequeueing 2 Nodes to Queue List
2 3 4
Enqueueing 5 Nodes to Queue List
2 3 4 0 1 2 3 4
Original Unsorted List
0 1 0 1 2 3 4
Sorted List
0 0 1 1 2 3 4

*/