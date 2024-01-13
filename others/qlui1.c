#include <stdio.h>

int x[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int n=6;

void ghinhan(){
	int i;
	for(i=1;i<n+1;i++){
		printf("%d ",x[i]);
	}
	printf("\n");
}

int check(int ai, int k){
	int i;
	for(i=1;i<k;i++){
		if(x[i]==1){
			if(ai==1) return 0;
			else return 1;//ai phai = 0
		}
	}
	
	if(k==n) {
		if(ai==0) return 0;
		else return 1;//ai phai = 1
	}
	
	return 1;
}

void Try(int k){
	int i;
	for(i=0;i<2;i++){
		if(check(i,k)==1){
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
