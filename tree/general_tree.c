#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* datatype;

typedef struct etnode{
  datatype data;
  struct etnode* leftchild;
  struct etnode* rightsib;
} etnode;

typedef struct etree{
  etnode* root;
  int size;
  int height;
} etree;

etree* makeETree(){
  etree* t = (etree*) malloc(sizeof(etree));
  t->root = NULL;
  t->height = 0;
  t->size = 0;
  return t;
}

etnode* makeENode(datatype x){
  etnode* p = (etnode*) malloc(sizeof(etnode));
  p->data = x;
  p->leftchild = NULL;
  p->rightsib = NULL;
  return p;
}


etnode* findNode_inArray(datatype x, etnode** p,int p_count){

  for(int i = 0; i < p_count; i++){
    if(p[i] != NULL && strcmp(p[i]->data,x) == 0){
      return p[i];
    }
  }
  return NULL;
}

void addChild_et(etnode* child, etnode* dad) {
  if (dad->leftchild == NULL) {
    dad->leftchild = child;
  }
  else {
    etnode* temp = dad->leftchild;
    while (temp->rightsib != NULL) {
      temp = temp->rightsib;
    }
    temp->rightsib = child;
  }
}

int treeHeight_et(etnode* p, int current_height, int* max_height){
  if(p == NULL){
    return current_height;
  }
  etnode* q = p->leftchild;
  while(q != NULL){
    if(current_height+1 > *max_height){
      *max_height = current_height + 1;
    }
    treeHeight_et(q,current_height + 1,max_height);
    q = q->rightsib;
  }
  return 0;
}


void countDescendants_et(etnode* p,int* count) {
  if (p == NULL) {
    return;
  }

  etnode* q = p->leftchild;
  while (q != NULL) {
    (*count)++;
    countDescendants_et(q,count);
    q = q->rightsib;
  }
}


