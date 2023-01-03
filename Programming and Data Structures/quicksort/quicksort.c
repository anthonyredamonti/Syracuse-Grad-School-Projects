// capacity is the actual size of the array in memory.
// size is the number of elements that are in use.
typedef struct Heap {
int* array;
int capacity;
int size;
} Heap;

typedef struct listNode {
   int value;
   struct listNode* next;
} Node;

typedef struct TreeNode {
   int value;
   struct TreeNode* left;
   struct TreeNode* right;
} TreeNode;

typedef struct Tree {
   TreeNode* root;
} Tree;

/// Remove the minimum value from the heap.
void HeapInsert(Heap* heap, int value) {

   if(heap->size == heap->capacity){
      int temp_size = heap->capacity * 2;
      int* array_temp = (int*)(malloc(temp_size*(sizeof(int))));
      copy_array(heap->array, heap->capacity, array_temp, temp_size);
      free(heap->array);
      heap->array = array_temp;
      heap->capacity = temp_size;
   }

   // push value on top of stack
   heap->array[heap->size] = value;
   heap->size++; // -1 + 1 = 0 for first element in array

   int levels = heap->size/2;

   for(int j = 0; j < levels; j++){
       for(int i = 0; i < levels; i++){
           if((heap->array[((i*2)+1)]) > heap->array[i]){
               swap_array(heap->array, i, ((i*2)+1));
           }
           if((heap->array[((i*2)+2)]) > heap->array[i]){
               swap_array(heap->array, i, ((i*2)+2));
           }
       }
   }
}

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
      int* array_temp = (int*)(malloc(temp_size*(sizeof(int))));
      copy_array(heap->array, heap->capacity, array_temp, temp_size);
      free(heap->array);
      heap->array = array_temp;
      heap->capacity = temp_size;
   }

   // push value on top of stack
   heap->array[heap->size] = value;
   heap->size++; // -1 + 1 = 0 for first element in array

}
  
void PrintArray(int* array, int number_of_elements_to_print){
      int i;
      for(i = 0; i < number_of_elements_to_print; i++){
      printf("%d ", array[i]);
   }
   printf("\n");
}
  
// Driver program to test above functions 
int main() 
{ 

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

   HeapInsert(pntr_heap1, 3);
   printf("The heap array after inserting the element: ");

   PrintArray(heap1.array, heap1.size);

   free(heap1.array);

    return 0; 
} 