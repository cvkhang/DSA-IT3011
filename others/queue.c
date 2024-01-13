#include <stdio.h>
#include <stdlib.h>

#define INFVALUE -2000000000

typedef int datatype;

typedef struct _QueueNode{
	int inf;
	struct _QueueNode *next;
} QueueNode;

typedef struct _Queue{
	struct _QueueNode *first;
	struct _QueueNode *last;
} Queue;

Queue *makeQueue(){
	Queue *q = (Queue*) malloc(sizeof(Queue));
	if(q==NULL){printf("Error in mem allocation\n");exit(1);}
	q->first=NULL;
	q->last=NULL;
	return q;
}

QueueNode *makeNode(int x){
	QueueNode *p = (QueueNode*) malloc(sizeof(QueueNode));
	if(p==NULL){printf("Error in mem allocation\n");exit(1);}
	p->inf=x;
	p->next=NULL;
	return p;
}

void enqueue(Queue *q, datatype x){
	if(q==NULL) return;
	if(q->first==NULL && q->last!=NULL) return;
	if(q->first!=NULL && q->last==NULL) return;
	
	QueueNode *p = makeNode(x);
	if(q->first==NULL && q->last==NULL){
		q->first = p;
		q->last = p;
		return;
	}
	q->last->next=p;
	q->last = p;
}

datatype dequeue(Queue *q){
	if(q==NULL) return INFVALUE;
	if(q->first==NULL || q->last==NULL) return INFVALUE;
	
	datatype x=q->first->inf;
	if(q->first==q->last){
		free(q->first);
		q->first=NULL;
		q->last=NULL;		
		return x;
	}
	
	QueueNode *p = q->first;
	q->first=q->first->next;
	free(p);
	
	return x;
}

int isEmpty(Queue *q){
	if(q==NULL) return 1;
	if(q->first==NULL && q->last==NULL) return 1;
	return 0;
}

int main(){
	Queue *q=makeQueue();
	enqueue(q,10);
	enqueue(q,20);
	enqueue(q,30);
	
	while(!isEmpty(q)){
		printf("%d\n",dequeue(q));
	}
	
	printf("\n");
	
	return 0;
}
