#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int counter = 0;

void swap(int* array, int i, int j){
	int temp = *(array+j);
	*(array + j) = *(array + i);
	*(array + i) = temp;
}

int partition(int* array, int low, int high) {     
    int pivot = array[high];
    int i = low - 1;  
    for (int j = low; j < high; j++) {
        if (array[j] <= pivot) {      
            i++;
            swap(array, i, j);    
        }                       
    }  
    swap(array, i+1, high);  
    return i+1;              
}

/* low  --> Starting index,  high  --> Ending index */
void quickSort(int* arr, int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[pi] is now
           at right place */
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);  // Before pi
        quickSort(arr, pi + 1, high); // After pi
    }
}

void PrintArray(int* array, int number_of_elements_to_print){
      int i;
      for(i = 0; i < number_of_elements_to_print; i++){
      printf("%d ", array[i]);
   }
   printf("\n");
}

void selectionSort(int *array, int n){
    int i, j, min_index;
    for(i = 0; i < n-1; i++){
        min_index = i;
        for(j = i+1; j < n; j++){
            counter++;
            if(array[j] < array[i]){
                swap(array, i, j);
            }
        }
    }
}

//
// The algorithm will call two different versions of itself. 
// Both versions eliminate the last element in the array, shrinking it by one.
// The first version ignores this last element completely. The second version subtracts that last element from the sum.
// The first version will break down the array to its first element.
// After this happens, the second version will start subtracting from the sum starting with the first element.
// If the sum does not equal zero, the OR in the return statement will complete and the stack will exit two threads (up two functional
// blocks) to add in the second element and start the process over (different branches of the tree).
// 
int subsetSum(int* set, int count, int sum)
{
    printf("The sum is %d\n", sum);
    PrintArray(set, count);
	// Base Cases 
	if (sum == 0)
		return 1;
	if (count == 0 && sum != 0)
		return 0;

	// If last element is greater than sum, then ignore it 
	if (set[count - 1] > sum)
		return subsetSum(set, count - 1, sum);

	/* else, check if sum can be obtained by any of the following
	   (a) including the last element
	   (b) excluding the last element   */
	return 
    subsetSum(set, count - 1, sum) ||
		subsetSum(set, count - 1, sum - set[count - 1]);
}

// Implementation of Merge Sort Algorithm in C
int main(void)
{

    int array[8] = {5, 7, 1, 9, 4, 2, 0, 6};
	//int p = partition(array, 0, 7);
	quickSort(array, 0, 7);
    //printf("p is: %d\n", p);
    //selectionSort(array, 8);
    //PrintArray(array, 8);
    //printf("the number of times the inner loop executed is: %d", counter);
	int is_sum10 = subsetSum(array, 3, 12);

    return 0;
}