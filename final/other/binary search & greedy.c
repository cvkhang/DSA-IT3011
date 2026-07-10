#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int n, k;

bool isValid(int arr[], int limit){
	int sum = 0;
	int bag_count = 1;
	for(int i = 0; i < n; i++){
		if(sum + arr[i] <= limit){
			sum += arr[i];
		}
		else{
			if(bag_count == k) return false;
			bag_count++;
			sum = arr[i];
		}
	}
	return true;
}

int solve(int arr[], int min, int max){
	int low = min;
	int high = max;
	int mid = (low + high)/2;

	int solution = max;

	while(low <= high){
		if(isValid(arr, mid)){
			solution = mid;
			high = mid - 1;
			mid = (low + high)/2;
		}
		else{
			low = mid + 1;
			mid = (low + high)/2;
		}
	}

	return solution;
}

int main(){
	
	scanf("%d %d\n", &n, &k);

	int arr[n];
	int min = 0;
	int max = 0;
	for(int i = 0; i < n; i++){
		scanf("%d ", &arr[i]);
		max += arr[i];
		min = arr[i] > min ? arr[i] : min;
	}

	printf("%d", solve(arr, min, max));	

	return 0;
}





