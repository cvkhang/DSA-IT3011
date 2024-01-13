void swap(int* a,int* b){
  int temp = *a;
  *a = *b;
  *b = temp;
}

void selectionSort(int* a, int n){
  for(int i = 0; i < n; i++){
    int min = i;
    for(int j = i + 1; j < n; i++){
      if(a[min] > a[j]){
        min = j;
      }
    }
    swap(&a[min], &a[i]);
  }
}

void insertionSort(int* a, int n){
  int i, key, j;
  for (i = 1; i < n; i++) {
    key = a[i];
    j = i - 1;

    /* Move elements of arr[0..i-1], that are
    greater than key, to one position ahead
    of their current position */
    while (j >= 0 && a[j] > key) {
        a[j + 1] = a[j];
        j = j - 1;
    }
    a[j + 1] = key;
  }
}

void bubbleSort(int* a, int n){
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n - i - 1; j++){
      if(a[j] > a[j+1]){
        swap(&a[j],&a[j+1]);
      }
    }
  }
}
