void swap(int* array, int i1, int i2){
    int temp = array[i1];
    array[i1] = array[i2];
    array[i2] = temp;
}

int insert_shell(int* array, int n, int gap){
    if(gap==0){
        return 0;
    }
    for(int i = gap; i < n; i++){
        for(int j = i; j >= gap && (array[j-gap] > array[j]); j-=gap){
            swap(array, j-gap, j);
        }
    }
    printArray(array, n);
    return 1;
}

void shell_sort(int* array, int n){
    int gap = n/2;
    while(insert_shell(array, n, gap)==1){
        gap = gap/2;
    }
}

/* UTILITY FUNCTIONS */
/* Function to print an array */
void printArray(int A[], int size) 
{ 
    int i; 
    for (i = 0; i < size; i++) 
        printf("%d ", A[i]); 
    printf("\n"); 
} 
  
/* Driver program to test above functions */
int main() 
{ 
    int arr[] = { 0,5,15,3,18,7,20,2,16,1}; // 11 times. If it was size 7 then it would be 13 calls including the original call.
    int arr_size = sizeof(arr) / sizeof(arr[0]); 
  
    printf("Given array is \n"); 
    printArray(arr, arr_size); 
    
    shell_sort(arr, arr_size);

    printf("\nSorted array is \n"); 
    printArray(arr, arr_size); 
    return 0; 
} 