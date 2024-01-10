#include <stdio.h>

void swap(int* a, int* b){
  
  int temp = *a;
  *a = *b;
  *b = temp;

}


int partition(int arr[],int low,int high){ 
  
  int pivot = arr[high];
  int i = low;

  for(int j = low; j <= high; j++){
    if(arr[j] < pivot){
      swap(arr[i],arr[j]);
      i++;
    }
  }

  swap(arr[i],arr[high]);
  return i;
  
}
 
            
void quickSort(int arr[],int low,int high){

  if(low<high){
    int pi=partition(arr,low,high);
    quickSort(arr,low,pi-1);
    quickSort(arr,pi+1,high);
  }

}