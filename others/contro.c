#include <stdio.h>
#include <stdlib.h>

typedef struct _TNode{
	int a;
	float b;
	char *s;
} TNode;

void f(){
	TNode *q=NULL; 
	q=(TNode*)malloc(sizeof(TNode));
	q->a = 12;
	printf("%d\n",q->a);
	free(q);
}


int main(){
	while(1)
	    f();

	
	int *p;
	int x;
	p=&x;
	*p = 123;
	printf("%d\n",*p);
	x=345;
	printf("%d\n",*p);
	
	
	
	return 0;
}
