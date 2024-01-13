#include <stdio.h>
#include <stdlib.h>

#define MINVALUE -2000000000

typedef int datatype;

typedef struct _StackNode{
	datatype inf;
	struct _StackNode *next;
} StackNode;

typedef struct _Stack {
	StackNode *top;
} Stack;

Stack *makeStack(){
	Stack *p = (Stack*) malloc(sizeof(Stack));
	if(p==NULL){printf("Error in mem allocation\n");exit(1);}	
	p->top=NULL;
	return p;
}

StackNode *makeNode(datatype x){
	StackNode *p = (StackNode*) malloc(sizeof(StackNode));
	if(p==NULL){printf("Error in mem allocation\n");exit(1);}
	p->inf=x;
	p->next=NULL;
	return p;
}

void printList(StackNode *h){
	StackNode *p=h;
	while(p != NULL){
		printf("%d ",p->inf);
		p = p->next;
	}
	printf("\n");
}

void push(Stack *s, datatype x){
	StackNode* q = makeNode(x);

	if(s->top == NULL){
		s->top = q;
		return;
	}
	
	q->next = s->top;
	s->top = q;
}

datatype pop(Stack *s){	
	if(s==NULL||s->top==NULL){
		return MINVALUE;
	}
	
	StackNode *tmp=s->top;
	s->top=s->top->next;
	datatype x = tmp->inf;
	free(tmp);
	
	return x;
}

int isEmpty(Stack *s){
	if(s==NULL||s->top==NULL) return 1;
	return 0;
}

void chuyencoso(int n, int b, Stack *s){
	if(b<1||b>9) return;
	if(!isEmpty(s)) return;
	
	while(n!=0){
		push(s,n%b);
		n=n/b;
	}
	
	while(!isEmpty(s)){
		printf("%d ",pop(s));
	}
}

int main(){
	Stack *s = makeStack();
	push(s,10);
	push(s,20);
	push(s,30);
	
	while(!isEmpty(s)){
		printf("%d ",pop(s));
	}
	
	printf("\nChuyen co so:\n");
	chuyencoso(3553,8,s);
	
	return 0;
}
