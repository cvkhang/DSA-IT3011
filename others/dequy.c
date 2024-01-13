#include <stdio.h>

 

int Fact(int n){
    if (n==0) return 1;
    else return n*Fact(n-1);
}

 

int sum(int n) {
    printf("Goi ham sum voi n=%d\n",n);
    if (n <= 1) {
        printf("Ket thuc ham tra ve 1\n");
        return 1;
    }
    int s = sum(n-1);
    printf("Ket thuc ham tra ve %d\n",n+s);
    return n + s;
}

 

int C(int k, int n) {
    if (k == 0 || k == n)
        return 1;
    int C1 = C(k-1,n-1);
    int C2 = C(k,n-1);
    return C1+C2;    
}
 
int Fibo(int n){
    if(n<=1) return n;
    return Fibo(n-1)+Fibo(n-2);    
}
 
int d=0; 
void thapHN(int n, char a, char b, char c){
    if(n==1) {
        printf("Lan %d:Chuyen 1 dia tu %c->%c\n",++d,a,c);
        return;
    }
    thapHN(n-1,a,c,b);
    thapHN(1,a,b,c);
    thapHN(n-1,b,a,c);
}
  
 
int main(){
    printf("%d\n",sum(5));
    printf("%d\n",Fact(5));
    printf("%d\n",C(3,5));
    thapHN(3,'A','B','C');
    return 0;
}
