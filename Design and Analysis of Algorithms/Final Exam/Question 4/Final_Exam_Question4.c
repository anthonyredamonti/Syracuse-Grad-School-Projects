#include <stdio.h>
#define N 7 // length of array1
#define M 4 // length of array2
#define P 5 // length of array3

// function that returns base^exponent 
int power_func(int base, int exponent)
{ 
   int i; 
   int answer = base; 
   for(i = 1; i < exponent; i++)
   { 
      answer *= base; 
   } 
   return(answer); 
}

void return_min(int* arr1, int* arr2, int* arr3, int* index1, int* index2, int* index3, int* bigarr, int* count){
   // array1 and array2 are empty. return array3.
   if((*index1 == -1)&&(*index2 == -1)&&(*index3 != -1)){
      bigarr[*count] = arr3[*index3];
      *index3 = *index3 + 1;;
      *count = *count + 1;
      return;
   }
   // array2 and array3 are empty. return array1.
   if((*index2 == -1)&&(*index3 == -1)&&(*index1 != -1)){
      bigarr[*count] = arr1[*index1];
      *index1 = *index1 + 1;
      *count = *count + 1;
      return;
   }
   // array1 and array3 are empty. return array2. 
   if((*index3 == -1)&&(*index1 == -1)&&(*index2 != -1)){
      bigarr[*count] = arr2[*index2];
      *index2 = *index2 + 1;
      *count = *count + 1;
      return;
   }

   // array1 is empty but array2 and array3 are not.
   if((*index1 == -1)&&(*index2 != -1)&&(*index3 != -1)){
      if(arr2[*index2] <= arr3[*index3]){
         bigarr[*count] = arr2[*index2];
         *index2 = *index2 + 1;
         *count = *count + 1;
         return;
      }
      else{
         bigarr[*count] = arr3[*index3];
         *index3 = *index3 + 1;
         *count = *count + 1;
         return;
      }
   }

   // array2 is empty but array1 and array3 are not.
   if((*index2 == -1)&&(*index1 != -1)&&(*index3 != -1)){
      if(arr1[*index1] <= arr3[*index3]){
         bigarr[*count] = arr1[*index1];
         *index1 = *index1 + 1;
         *count = *count + 1;
         return;
      }
      else{
         bigarr[*count] = arr3[*index3];
         *index3 = *index3 + 1;
         *count = *count + 1;
         return;
      }
   }

   // array3 is empty but array2 and array1 are not.
   if((*index3 == -1)&&(*index2 != -1)&&(*index1 != -1)){
      if(arr2[*index2] <= arr1[*index1]){
         bigarr[*count] = arr2[*index2];
         *index2 = *index2 + 1;
         *count = *count + 1;
         return;
      }
      else{
         bigarr[*count] = arr1[*index1];
         *index1 = *index1 + 1;
         *count = *count + 1;
         return;
      }
   }

   // none of the arrays are empty.
   if((arr1[*index1] <= arr2[*index2])&&(arr1[*index1] <= arr3[*index3])){
      bigarr[*count] = arr1[*index1];
      *index1 = *index1 + 1;
      *count = *count + 1;
      return;
   }
   if((arr2[*index2] <= arr1[*index1])&&(arr2[*index2] <= arr3[*index3])){
      bigarr[*count] = arr2[*index2];
      *index2 = *index2 + 1;
      *count = *count + 1;
      return;
   }
   if((arr3[*index3] <= arr1[*index1])&&(arr3[*index3] <= arr2[*index2])){
      bigarr[*count] = arr3[*index3];
      *index3 = *index3 + 1;
      *count = *count + 1;
   }
}

void combine_arrays(int* array1, int* array2, int* array3, int* big_array){
   int count = 0;
   int size_of_big_array = N+M+P;
   int index1 = 0;   int index2 = 0;   int index3 = 0;
   int* ptr_index1 = &index1; int* ptr_index2 = &index2; 
   int* ptr_index3 = &index3; int* ptr_count = &count;
   int min;

   while(count != size_of_big_array){

      return_min(array1, array2, array3, ptr_index1, ptr_index2, ptr_index3, big_array, ptr_count);
      if(index1 == N){index1 = -1;}
      if(index2 == M){index2 = -1;}
      if(index3 == P){index3 = -1;}
   }
}

// create array of indices 
int balance_the_tree(int* tree_array, int* sorted_array, int size, int count, int tree_index, int iteration){
   int i, prev_index, value;
   if(count == size){return 0;}
   int number_of_elements_to_fill = power_func(2, iteration);
   int special_value = ((tree_array[0])/number_of_elements_to_fill);
   if(special_value == 0){return count;}
   int index1, index2;
   for(i = 0; i < number_of_elements_to_fill/2; i++){
      if(tree_index%2 == 0){
         prev_index = (tree_index/2)-1;
      }
      else{
         prev_index = (tree_index/2);
      }

      value = tree_array[prev_index]; // 8

      index1 = (value - special_value); 
      index2 = (value + special_value);
      tree_array[tree_index] = index1;
      count++; tree_index++;
      if(count == size){return 0;}
      tree_array[tree_index] = index2;
      count++; tree_index++;
   }
   iteration++;
   balance_the_tree(tree_array, sorted_array, size, count, tree_index, iteration);
}

void create_balanced_binary_tree(int* sorted_array, int* tree_array, int size){
   int i;
   int count = 1; int tree_index = 1; int iteration = 1;
   int* index_array = (int*)(malloc(sizeof(int)*size));
   index_array[0] = size/2; // fill root node.
   count = balance_the_tree(index_array, sorted_array, size, count, tree_index, iteration);
   int temp = 0;
   for(i = 0; i < count; i++){
      tree_array[i] = sorted_array[index_array[i]];
   }
   while(count != size){
      tree_array[i] = sorted_array[temp];
      i++; temp++; count++;
   }
   free(index_array);
}

void print_array(int* array, int size){
   for(int i = 0; i < size-1; i++){
      printf("%d, ", array[i]);
   }
   printf("%d]\n", array[size-1]);
}

int main(){
   int i;
   int array1[N] = {2,5,9,10,11,12,15};
   int array2[M] = {34, 56, 200, 204};
   int array3[P] = {20, 21, 22, 23, 400};
   
   printf("Array 1: [");
   print_array(array1, N);

   printf("Array 2: [");
   print_array(array2, M);

   printf("Array 3: [");
   print_array(array3, P);

   int* union_array = (int*)(malloc(sizeof(int)*(N+M+P)));
   combine_arrays(array1, array2, array3, union_array);
   printf("Union Array: [");
   print_array(union_array, N+M+P);

   int* balanced_binary_tree = (int*)(malloc(sizeof(int)*(N+M+P)));
   create_balanced_binary_tree(union_array, balanced_binary_tree, N+M+P);
   printf("Balanced Binary Search Tree: [");
   print_array(balanced_binary_tree, N+M+P);
   
   free(union_array);
   free(balanced_binary_tree);
}
