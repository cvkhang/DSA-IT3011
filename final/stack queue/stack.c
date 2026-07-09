#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int datatype;

typedef struct snode{
  datatype data;
  struct snode* next;
} snode;

typedef struct stack{
  snode* head;
} stack;

stack* makeStack(){
  stack* a = (stack*) malloc(sizeof(stack));
  a->head = NULL;
  return a;
}

snode* makeSNode(datatype x){
  snode* a = (snode*) malloc(sizeof(snode));
  a->data = x;
  a->next = NULL;
  return a;
}

void push(stack* a, datatype x){
  if(a == NULL) return;

  snode* b = makeSNode(x);
  b->next = a->head;
  a->head = b;
}

int pop(stack* a, datatype* out){
  if(a == NULL || a->head == NULL) return 0;

  snode* tofree = a->head;
  *out = tofree->data;
  a->head = a->head->next;
  free(tofree);

  return 1;
}

int isStackEmpty(stack* a){
  if(a == NULL) return 1;
  if(a->head == NULL) return 1;
  return 0;
}

datatype peek(stack* a){
  if(a == NULL || a->head == NULL){
    printf("Stack is empty\n");
    exit(1);
  }

  return a->head->data;
}

void printStack(stack* a){
  if(a == NULL || a->head == NULL){
    printf("Stack is empty\n");
    return;
  }

  snode* p = a->head;
  while(p != NULL){
    printf("%d ", p->data);
    p = p->next;
  }
  printf("\n");
}

int countStack(stack* a){
  if(a == NULL) return 0;

  int count = 0;
  snode* p = a->head;

  while(p != NULL){
    count++;
    p = p->next;
  }

  return count;
}

void clearStack(stack* a){
  if(a == NULL) return;

  snode* p = a->head;

  while(p != NULL){
    snode* temp = p;
    p = p->next;
    free(temp);
  }

  a->head = NULL;
}
