#include <stdio.h>

int A[10]={1,2,3,4,5,6,7,8,9,10};
int x[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int n=4;

void ghinhan(){
	int i;
	for(i=1;i<n+1;i++){
		printf("%d ",x[i]);
	}
	printf("\n");
}

int check(int ucv, int k){
	int i;
	for(i=1;i<k;i++){
		if(x[i]==ucv){
			return 0;
		}
	}
	
	return 1;
}

void Try(int k){
	int i;
	for(i=0;i<n;i++){
		if(check(A[i],k)==1){
			x[k]=i;
			if(k==n) ghinhan();
			else Try(k+1);
		}
	}
}


int main(){
	Try(1);

	return 0;
}
