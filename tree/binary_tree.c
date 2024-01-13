#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int datatype;

typedef struct btnode{
  datatype data;
  struct btnode* left;
  struct btnode* right; 
}btnode;

typedef struct btree{
  btnode* root;
  int size;
  int height;
}btree;

btnode* makeNode(datatype x){
  btnode* p = (btnode*) malloc(sizeof(btnode));
  p->data = x;
  p->left = NULL;
  p->right = NULL;
  return p;
}

btree* makeTree(){
  btree* t = (btree*) malloc(sizeof(btree));
  t->root = NULL;
  t->size = 0;
  t->height = 0;
  return t;
}

void addChild(btnode* child, btnode* dad){
  if(dad->left != NULL && dad->right != NULL){
    printf("Node Full\n");
    return;
  }

  if(dad->left == NULL){
    dad->left = child;
    return;
  }
  else{
    dad->right = child;
    return;
  }
  
}

void addLeft(btnode* child, btnode* dad){
  if(dad->left != NULL){
    return;
  }
  else{
    dad->left = child;
    return;
  }
}

void addRight(btnode* child, btnode* dad){
  if(dad->right != NULL){
    return;
  }
  else{
    dad->right = child;
    return;
  }
}

btnode* findNode(btnode* p, datatype x) {
  if (p->data == x) {
    return p;
  }

  if (p->left != NULL) {
    btnode* leftResult = findNode(p->left, x);
    if (leftResult != NULL) {
      return leftResult;
    }
  }

  if (p->right != NULL) {
    btnode* rightResult = findNode(p->right, x);
    if (rightResult != NULL) {
      return rightResult;
    }
  }

  return NULL;
}

void preOrder(btnode* p){
  if(p==NULL){
    return;
  }

  printf("%d ",p->data);
  preOrder(p->left);
  preOrder(p->right);
}

void inOrder(btnode* p){
  if(p==NULL){
    return;
  }

  inOrder(p->left);
  printf("%d ",p->data);
  inOrder(p->right);
}

void postOrder(btnode* p){
  if(p==NULL){
    return;
  }

  postOrder(p->left);
  postOrder(p->right);
  printf("%d ",p->data);
}

int height(btnode* root){

}

int nodeCount(btnode* root){
  
}

