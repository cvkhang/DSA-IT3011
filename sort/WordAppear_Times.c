//C 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swapInt(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swapString( char** a, char** b){
    char* temp = *a;
    *a = *b;
    *b = temp;
}

int cmp(char* a, char*b ){
    if(a == NULL || b == NULL){
        return 0;
    }
    if(strlen(a) != strlen(b) ){
        return 0;
    }
    
    for( int i = 0; i<strlen(a); i++){
        if(a[i] != b[i]){
            return 0;
        }
    }
    return 1;
}

int asciicmp(char* a, char*b){
    int minlen = strlen(a) < strlen(b) ? strlen(a) : strlen(b);
    
    for( int i = 0; i<minlen; i++){
        if(a[i] < b[i]){
            return 1;
        }
        if(b[i] < a[i]){
            return -1;
        }
    }
    
    return 0;
}

void heapify(int arr[], char** a, int N, int i)
{
   
    int largest = i;
 
    int left = 2 * i + 1;
 
    int right = 2 * i + 2;

    if(arr[i] == 0){
        return;
    }
 
    if (left < N){
        
        if(arr[left] < arr[largest])
            largest = left;
        else if(arr[left] == arr[largest]){
            if(asciicmp(a[left],a[largest]) == -1){
                largest = left;
            }
        }
    }


    if (right < N){
 
        if(arr[right] < arr[largest])
            largest = right;
        else if(arr[right] == arr[largest]){
            if(asciicmp(a[right],a[largest]) == -1){
                largest = right;
            }
        }
 
    }

    if (largest != i) {
        swapInt(&arr[i], &arr[largest]);
        swapString(&a[i], &a[largest]);
        heapify(arr,a, N, largest);
    }
}
 
void heapSort(int arr[], char** a, int N)
{
    for (int i = N/2 - 1 ; i >= 0; i--){
        heapify(arr,a, N, i);
    }
    for (int i = N - 1; i >= 0; i--) {
        swapInt(&arr[0], &arr[i]);
        swapString(&a[0], &a[i]);
        heapify(arr,a, i, 0);
    }
}


int main(){
    
    char** arr = (char**) malloc(sizeof(char*));
    char* word = (char*) malloc(sizeof(char) * 20);
    
    char temp;
    char* tofree;
    int lettercount = 0;
    int wordcount = 0;
    scanf("%c", &temp);
    
    while(temp != '\n'){ 
        if(temp == ' '){
            word[lettercount] = '\0';
            lettercount = 0;
            arr[wordcount] = word;
            wordcount++;
            arr = (char**) realloc(arr, sizeof(char*) * ( wordcount + 1 ) );
            word = (char*) malloc(sizeof(char) * 20);
            scanf("%c", &temp);
            continue;
        }
        
        word[lettercount] = temp;
        lettercount++;
        scanf("%c", &temp);
        
    }
    
    word[lettercount] = '\0';
    arr[wordcount] = word;
    wordcount++;
    
    int* times = (int*) malloc(sizeof(int) * wordcount);
    int count;
    
    for(int i = 0; i < wordcount; i++){
        
        if(arr[i] == NULL){
            times[i] = 0;
            continue;
        }
        count = 1;
        
        for(int j = i + 1; j < wordcount; j++){
            if( cmp(arr[i],arr[j]) == 1 ){
                count++;
                arr[j] = NULL;
            }
        }
        
        times[i] = count;        
    }

    heapSort(times,arr,wordcount);
    
    
    for(int i = 0; i < wordcount; i++){
        if(times[i] != 0){
            printf("%s",arr[i]);
            printf(" %d\n",times[i]);
        }
    }

    
    return 0;
}