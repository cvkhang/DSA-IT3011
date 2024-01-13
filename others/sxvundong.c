#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void max_heapify(int A[], int i, int N)
{
	int L = 2*i;
	int R = 2*i+1;
	int max = i;
	if(L <= N && A[L] > A[i])
	max = L;
	if(R <= N && A[R] > A[max])
	max = R;
	if(max != i){
		swap(A+i, A+max);
		max_heapify(A,max,N);
	}
}

void Build_Max_Heap(int A[], int n){
	for(int i=n/2;i>0;i--)
		max_heapify(A,i,n);	
}

void heapsort(int A[], int n)
{
	Build_Max_Heap(A,n);
	for(int i=n;i>1;i--){
		swap(A+1,A+i);
		max_heapify(A,1,i-1);
	}
}

int main(){
	/*
	int A[]={0,16,4,10,14,7,9,3,2,8,1};
	
	max_heapify(A,2,10);
	
	for(int i=1;i<=10;i++)
	   printf("%d ",A[i]);
	*/
	
	int A[]={0,1,4,10,14,7,9,33,2,28,11};
	/*Build_Max_Heap(A,10);*/
	heapsort(A,10);
	for(int i=1;i<=10;i++)
	   printf("%d ",A[i]);
	   
	return 0;
}
