#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000

void merge(int A[], int first, int mid, int last){
	int tempA[MAX_SIZE];// mảng phụ
	
	int first1 = first; 
	int last1 = mid;
	int first2 = mid + 1; 
	int last2 = last; 
	
	int index = first1;
	for (; (first1 <= last1) && (first2 <= last2); ++index){
		if (A[first1] < A[first2])
		{
			tempA[index] = A[first1]; ++first1;
		}
		else
		{ 
			tempA[index] = A[first2]; ++first2;
		}
	}
	
	for (; first1 <= last1; ++first1, ++index)
		tempA[index] = A[first1]; // sao nốt dãy con 1
		
	for (; first2 <= last2; ++first2, ++index)
		tempA[index] = A[first2]; // sao nốt dãy con 2
	
	for (index = first; index <= last; ++index)
		A[index] = tempA[index]; // sao trả mảng kết quả
} // end merge

void mergesort(int A[], int first, int last)
{
	if (first < last)
	{ // chia thành hai dãy con
		int mid = (first + last)/2;
		// chỉ số điểm giữa
		// sắp xếp dãy con trái A[first..mid]
		mergesort(A, first, mid);
		// sắp xếp dãy con phải A[mid+1..last]
		mergesort(A, mid+1, last);
		// Trộn hai dãy con
		merge(A, first, mid, last);
	} // end if
} // end mergesort

void swap(int *a, int *b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int Partition(int A[],int left,int right){
	int i = left, j = right + 1, pivot = A[left];
	
	while (i < j) {
		i = i + 1;
		while (i <= right && A[i] < pivot) 
		        i = i + 1;
		
		j = j - 1;
		while (j >= left && A[j] > pivot)
		        j = j - 1;
		
		swap(A + i, A + j);
	}
	
	swap(A + i, A + j); 
	swap(A + j, A + left);
	return j;
}

void QS(int A[], int l, int r){
	if(l<r){
		int pivot = Partition(A,l,r);
		QS(A,l,pivot-1);
		QS(A,pivot+1,r);
	}
}


int main(){
	int x[]={3,1,9,6,7,10,0,2};
	mergesort(x,0,7);
	printf("sxtron\n");
	for(int i=0;i<=7;i++)
	   printf("%d ",x[i]);
	
	int y[]={3,1,9,6,7,10,0,2};
	QS(y,0,7);
	printf("\nsxnhanh\n");
	for(int i=0;i<=7;i++)
	   printf("%d ",y[i]);
	   
	return 0;
}
