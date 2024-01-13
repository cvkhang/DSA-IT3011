#include <stdio.h>
#include <stdlib.h>

#define MINVALUE ' '

typedef char datatype;

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

int kiemtracungloai(char c, char xi){
	if(c=='('&&xi==')') return 1;
	if(c=='{'&&xi=='}') return 1;
	if(c=='['&&xi==']') return 1;
	return 0;
}

int btngoacdung(Stack *s, char x[], int n){
	if(!isEmpty(s)) return 0;
	for(int i=0;i<n;i++){
		if(x[i]=='('||x[i]=='{'||x[i]=='[')
			push(s,x[i]);
		else{
			if(isEmpty(s)) return -1;
			else{
				datatype c=pop(s);
				if(kiemtracungloai(c,x[i])==0) return -2;
			}
		}
	}
	
	if(isEmpty(s)) return 1;
	else return -3;
}

int main(){
	Stack *s = makeStack();
	char x[6]={'(','{','[','[',']',']'};
	int kq=btngoacdung(s,x,6);
	printf("%d\n",kq);
	return 0;
}
