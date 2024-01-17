#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int datatype;

typedef struct snode{
  datatype data;
  snode* next;
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
  snode* b = makeSNode(x);
  b->next = a->head;
  a->head = b;
  return;
}

datatype pop(stack* a){
  datatype temp = a->head->data;
  snode* tofree = a->head;
  a->head = a->head->next;
  free(tofree);
  return temp;
}

int isStackEmpty(stack* a){
  if(a == NULL) return 1;
  if(a->head == NULL) return 1;
  return 0;
}