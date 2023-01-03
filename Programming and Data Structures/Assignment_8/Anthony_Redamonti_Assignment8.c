// Anthony Redamonti
// 8-28-2020
// This is Assignment 8 for Week 8 written in C. Questions 1, 2 and 3 are answered.

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// ------------------------------ STRUCTS ------------------------------------//

// capacity is the actual size of the array in memory.
// size is the number of elements that are in use.
typedef struct Heap {
int* array;
int capacity;
int size;
} Heap;

typedef struct TreeNode {
   int value;
   struct TreeNode* left;
   struct TreeNode* right;
} TreeNode;

typedef struct Tree {
   TreeNode* root;
} Tree;

typedef struct listNode {
   int value;
   struct listNode* next;
} Node;

typedef struct list{
   Node* head;
   int size;
} List;

// ----------------------- isomorphic FUNCTION ----------------------------//

int isomorphic(Tree* tree1, Tree* tree2){

   if((tree1->root == NULL)||(tree2->root == NULL)){
      printf("One of the tree's roots is NULL");
      return 0;
   }

   List list1;
   List list2;
   list1.head = NULL;
   list2.head = NULL;
   List** ptrlist1 = &list1.head;
   List** ptrlist2 = &list2.head;

   helperFunction(&tree1->root, ptrlist1);
   helperFunction(&tree2->root, ptrlist2);

   list1.size = size_of_list(ptrlist1);
   list2.size = size_of_list(ptrlist2);
   int is_isomorphic = compare_lists(ptrlist1, ptrlist2);
   
   // free up the memory space of the list
   for(int i = 0; i < list1.size; i++){
      pop_list(ptrlist1);
   }
   for(int i = 0; i < list2.size; i++){
      pop_list(ptrlist2);
   }
   return (is_isomorphic);
}

void helperFunction(TreeNode* root, List** int_list){
   if(root == NULL){
      return;
   }
   if(root->left != NULL){
      push_list(int_list, 1); // 1 for left
      helperFunction(root->left, int_list);      
   }
   if(root->right != NULL){
      push_list(int_list, 2); // 2 for right
      helperFunction(root->right, int_list);      
   }
}

// ----------------------------- List FUNCTIONS --------------------------------//
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

void pop_list(List** head){
   if(*head == NULL){
      printf("Can not pop. List is already empty");
      return;
   }
   Node* last_node = NULL;
   Node* second_to_last_node = NULL;
   last_node = *head;
   if(last_node->next == NULL){
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

int size_of_list(List** head){
   if(*head == NULL){
      return 0;
   }
   int size = 1;
   Node* node = *head;
   while(node->next != NULL){
      node = node->next;
      size++;
   }
   return(size);
}

int compare_lists(List** head1, List** head2){
   if((*head1 == NULL)||(*head2 == NULL)){
      printf("One of the list's heads is NULL. Cound not compare lists.\n");   
      return 0;
   }

   Node* node1 = *head1;
   Node* node2 = *head2;
   // determine the size of the list.
   int size1 = size_of_list(head1);
   int size2 = size_of_list(head2);

   if(size1 != size2){
      printf("One binary tree has more nodes than the other.\n");
      return 0;
   }
   while((node1->next != NULL)||(node2->next != NULL)){
      if((node1->value) != (node2->value)){
         printf("While the trees have the same number of nodes, their structures are different.\n");
         return 0;
      }
      node1 = node1->next;
      node2 = node2->next;
   }
   if((node1->value) != (node2->value)){
      return 0;
   }
   printf("The two binary trees have the same structure.\n");
   return 1;
}

// ----------------------- isBinarySearchTree FUNCTION ----------------------------//
// Return 1 if the tree is a binary search tree.
// Return 0 otherwise
int isBinarySearchTree(Tree* tree) {
   if(tree->root == NULL)
   {
      printf("The tree's roots is NULL. Not a binary tree.");
      return 0;
   }
   int answer = recursive_is_binary_search_tree(tree->root);
   return(answer);
}

int recursive_is_binary_search_tree(TreeNode* root){
   List left_list;
   List right_list;
   left_list.head = NULL;
   right_list.head = NULL;
   List** ptrleftlist = &left_list.head;
   List** ptrrightlist = &right_list.head;
   int left_is_less = 0;
   int right_is_greater = 0;
   int left_is_present = 0;
   int right_is_present = 0;

   int value_of_root = root->value;

   if(root->left != NULL){
      left_is_present = 1;
      // create list with everything to the left of root
      push_list(ptrleftlist, root->left->value);
      // call function to get all values to left of root
      FindAllValues(root->left, ptrleftlist);
      // Are all the values to the left of the node less than its value? 1 for YES, 0 for NO.
      left_is_less = AreValuesInListLessThanValue(ptrleftlist, value_of_root);
      
      // determine the size of the list
      left_list.size = size_of_list(ptrleftlist);
      // free up the memory space of the list
      for(int i = 0; i < left_list.size; i++){
         pop_list(ptrleftlist);
      }
      
      if(left_is_less == 0){
         return 0;
      }
   }

   if(root->right != NULL){
      right_is_present = 1;
      // create list with everything to the right of root
      push_list(ptrrightlist, root->right->value);
      // call function to get all values to right of root
      FindAllValues(root->right, ptrrightlist);
      // Are all the values to the right of the node greater than its value? 1 for YES, 0 for NO.
      right_is_greater = AreValuesInListGreaterThanValue(ptrrightlist, value_of_root);

      // determine the size of the list
      right_list.size = size_of_list(ptrrightlist);
      // free up the memory space of the list
      for(int i = 0; i < right_list.size; i++){
         pop_list(ptrrightlist);
      }

      if(right_is_greater == 0){
         return 0;
      }
   }

   if((right_is_present == 1) && (left_is_present == 1)){
      return(recursive_is_binary_search_tree(root->left)*recursive_is_binary_search_tree(root->right));
   }
   if((right_is_present == 0) && (left_is_present == 1)){
      return(recursive_is_binary_search_tree(root->left));
   }
   if((right_is_present == 1) && (left_is_present == 0)){
      return(recursive_is_binary_search_tree(root->right));
   }
   return(1); // root is present and no children present
}

int AreValuesInListLessThanValue(List** head, int root_value){
   if(*head == NULL){
      return 0;
   }
   Node* node = *head;
   while(node->next != NULL){
      if(node->value >= root_value){
         return 0;
      }
      node = node->next;
   }
   if(node->value >= root_value){
      return 0;
   }
   return(1);
}

int AreValuesInListGreaterThanValue(List** head, int root_value){
   if(*head == NULL){
      return 0;
   }
   Node* node = *head;
   while(node->next != NULL){
      if(node->value <= root_value){
         return 0;
      }
      node = node->next;
   }
   if(node->value <= root_value){
      return 0;
   }
   return(1);
}

void FindAllValues(TreeNode* root, List** int_list){
   if(root == NULL){
      return;
   }
   if(root->left != NULL){
      push_list(int_list, root->left->value); 
      FindAllValues(root->left, int_list);      
   }
   if(root->right != NULL){
      push_list(int_list, root->right->value); 
      FindAllValues(root->right, int_list);      
   }
}

// ----------------------- removeMin FUNCTION ----------------------------//

// copy array1 into array2
void copy_array(int* array1, int size_of_array1, int* array2, int size_of_array2){
   if(size_of_array1 > size_of_array2){
      printf("array1 is bigger than array2 and therefore cannot be copied.");
      return;
   }
   for(int i = 0; i < size_of_array1; i++){
      array2[i] = array1[i];
   }
}

//swap two elements in array
void swap_array(int* array, int i, int j){
   int temp = array[i];
   array[i] = array[j];
   array[j] = temp;
}

void push_heap_array(Heap* heap, int value){
   
   // if no more room, create new array double in size
   if(heap->size == heap->capacity){
      int temp_size = heap->capacity * 2;
      int* array_temp = (Node*)(malloc(temp_size*(sizeof(Node))));
      copy_array(heap->array, heap->capacity, array_temp, temp_size);
      free(heap->array);
      heap->array = array_temp;
      heap->capacity = temp_size;
   }

   // push value on top of stack
   heap->array[heap->size] = value;
   heap->size++; // -1 + 1 = 0 for first element in array

}

// Remove the minimum value from the heap.
void removeMin(Heap* heap) {
   if(heap->size == 0){
      printf("stack array already empty\n");
      return;
   }
   int smallest = heap->array[0];
   for(int i = 0; i < heap->size; i++){
      heap->array[i] = heap->array[i+1];
   }
   heap->size--;
   int smallest_child_index = 0;
   int levels = heap->size/2;
   for(int j = 0; j < levels; j++)
   {
      for(int i = 0; i < levels; i++){
         // find the smallest child
         if((heap->array[i*2]+1) > (heap->array[i*2]+2)){
            smallest_child_index = (i*2)+2;
         }
         else{
            smallest_child_index = (i*2)+1;
         }
         // if parent is greater than smallest child
         if(heap->array[i] > heap->array[smallest_child_index]){
            swap_array(heap->array, i, smallest_child_index);
         }
      }
   }
}


// ----------------------------- Miscellaneous FUNCTIONS --------------------------------//

TreeNode* createTreeNode(int data){
   TreeNode* node;
   node = (TreeNode*)(malloc(sizeof(TreeNode)));
   node->left = NULL;
   node->right = NULL;
   node->value = data;
   return(node);
}

void printBinaryTree(TreeNode* root){
   if(root == NULL){
      return;
   }
   printf("%d, ", root->value);
   if(root->left != NULL){
      //printf("going left ");
      printBinaryTree(root->left);
   }
   //printf(" left was NULL  ");
   if(root->right != NULL){
      //printf("going right ");
      printBinaryTree(root->right);
   }
   //printf(" right was NULL  ");
}

void PrintArray(int* array, int number_of_elements_to_print){
      int i;
      for(i = 0; i < number_of_elements_to_print; i++){
      printf("%d ", array[i]);
   }
   printf("\n");
}

int main() {

// -------------- Test isomorphic function ---------------- //

   Tree tree1;
   tree1.root = createTreeNode(2);
   tree1.root->left = createTreeNode(3);
   tree1.root->right = createTreeNode(60);
   tree1.root->left->left = createTreeNode(2);

   Tree tree2;
   tree2.root = createTreeNode(10);
   tree2.root->left = createTreeNode(4);
   tree2.root->right = createTreeNode(59);
   tree2.root->left->left = createTreeNode(2);

   printf("tree1: ");
   printBinaryTree(tree1.root);
   printf("\n");
   printf("tree2: ");
   printBinaryTree(tree2.root);
   printf("\n");
   
   int is_isomorphic = isomorphic(tree1.root, tree2.root);
   printf("Are tree 1 and tree 2 isomorphic? 1 for YES and 0 for NO: %d\n", is_isomorphic);

   tree2.root->left->left->left = createTreeNode(1);

   printf("tree1: ");
   printBinaryTree(tree1.root);
   printf("\n");
   printf("tree2: ");
   printBinaryTree(tree2.root);
   printf("\n");

   is_isomorphic = isomorphic(tree1.root, tree2.root);
   printf("Are tree 1 and tree 2 isomorphic? 1 for YES and 0 for NO: %d\n", is_isomorphic);

// ------------------ Test isBinarySearchTree Function ----------------------- //

   Tree* ptr_tree1 = &tree1;
   int is_binary_search_tree = isBinarySearchTree(ptr_tree1);
   printf("Is tree 1 a binary search tree? 1 for YES, 0 for NO: %d\n", is_binary_search_tree);

   Tree* ptr_tree2 = &tree2;
   is_binary_search_tree = isBinarySearchTree(ptr_tree2);
   printf("Is tree 2 a binary search tree? 1 for YES, 0 for NO: %d\n", is_binary_search_tree);

// ------------------ Test removeMin Function ----------------------- //

   Heap heap1;
   heap1.capacity = 10;
   heap1.size = 0;
   heap1.array = (int*)(malloc(heap1.capacity * sizeof(int)));
   Heap* pntr_heap1 = &heap1;

   printf("Pushing 7 Nodes to Heap Array: ");
   push_heap_array(pntr_heap1, 1);
   push_heap_array(pntr_heap1, 5);
   push_heap_array(pntr_heap1, 8);
   push_heap_array(pntr_heap1, 6);
   push_heap_array(pntr_heap1, 7);
   push_heap_array(pntr_heap1, 9);
   push_heap_array(pntr_heap1, 10);

   PrintArray(heap1.array, heap1.size);

   removeMin(pntr_heap1);
   printf("The heap array after removing the minimum element: ");

   PrintArray(heap1.array, heap1.size);

   free(heap1.array);

   return 0;
}

/*

tree1: 2, 3, 2, 60,
tree2: 10, 4, 2, 59,
The two binary trees have the same structure.
Are tree 1 and tree 2 isomorphic? 1 for YES and 0 for NO: 1
tree1: 2, 3, 2, 60,
tree2: 10, 4, 2, 1, 59,
One binary tree has more nodes than the other.
Are tree 1 and tree 2 isomorphic? 1 for YES and 0 for NO: 0
Is tree 1 a binary search tree? 1 for YES, 0 for NO: 0
Is tree 2 a binary search tree? 1 for YES, 0 for NO: 1
Pushing 7 Nodes to Heap Array: 1 5 8 6 7 9 10
The heap array after removing the minimum element: 5 7 6 8 9 10

*/