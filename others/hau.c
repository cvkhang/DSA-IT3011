#include <stdio.h>

int x[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int n=8;
int dem=0;

void ghinhan(){
	int i;
	printf("loi giai=%d|",++dem);
	for(i=1;i<n+1;i++){
		printf("%d ",x[i]);
	}
	printf("\n");
}

int abs(int a){
	if(a<0) return -a;
	return a; 
}

int check(int ucv, int k){
	int j;
	for(j=1;j<k;j++){
		if(x[j]==ucv) return 0;
		if(abs(x[j]-ucv)==abs(k-j)) return 0;
	}
		
	return 1;
}

void Try(int k){
	int i;
	for(i=1;i<n+1;i++){
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
