#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int datatype;

typedef struct qnode{
  datatype data;
  struct qnode* next;
} qnode;

typedef struct queue{
  qnode* first;
  qnode* last;
} queue;

queue* makeQueue(){
  queue* a = (queue*) malloc(sizeof(queue));
  a->first = NULL;
  a->last = NULL;
  return a;
}

qnode* makeQNode(datatype x){
  qnode* a = (qnode*) malloc(sizeof(qnode));
  a->data = x;
  a->next = NULL;
  return a;
}

void enqueue(queue* a, datatype x){
  if(a==NULL) return;
	if(a->first==NULL && a->last!=NULL) return;
	if(a->first!=NULL && a->last==NULL) return;
	
	qnode *b = makeQNode(x);
	if(a->first==NULL && a->last==NULL){
		a->first = b;
		a->last = b;
		return;
	}

	a->last->next = b;
	a->last = b;

}

int dequeue(queue* a, datatype* out){
    if(a == NULL || a->first == NULL) return 0;

    qnode* tofree = a->first;
    *out = tofree->data;

    if(a->first == a->last){
        a->first = NULL;
        a->last = NULL;
    } else {
        a->first = a->first->next;
    }

    free(tofree);
    return 1;
}

int isQueueEmpty(queue* a){
	if(a==NULL) return 1;
	if(a->first==NULL && a->last==NULL) return 1;
	return 0;
}

datatype peek(queue* a){
    if(a == NULL || a->first == NULL){
        printf("Queue is empty\n");
        exit(1);
    }

    return a->first->data;
}

void printQueue(queue* a){
    if(a == NULL || a->first == NULL){
        printf("Queue is empty\n");
        return;
    }

    qnode* p = a->first;
    while(p != NULL){
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int countQueue(queue* a){
    if(a == NULL) return 0;

    int count = 0;
    qnode* p = a->first;

    while(p != NULL){
        count++;
        p = p->next;
    }

    return count;
}

void clearQueue(queue* a){
    if(a == NULL) return;

    qnode* p = a->first;

    while(p != NULL){
        qnode* temp = p;
        p = p->next;
        free(temp);
    }

    a->first = NULL;
    a->last = NULL;
}

