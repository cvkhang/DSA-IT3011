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

btnode* insert_bst(btnode* root,datatype x){
      
  if (root == NULL){
    return makeNode(x);
  }

  if (x < root->data){
    root->left = insert_bst(root->left, x);
  }
  else{
    root->right = insert_bst(root->right, x);
  }

  return root;
}

btnode* findNode_bst(btnode* p, datatype x){
  if(p == NULL)  return NULL;
  if(p->data == x) return p;

  if(p->data > x){
    return findNode_bst(p->left,x);
  }
  else{
    return findNode_bst(p->right,x);
  }
}

btnode* findmin_bst(btnode* p){
  if(p == NULL) return NULL;
  if(p->left == NULL){
    return p;
  }
  else{ 
    return findmin_bst(p->left);
  }
}

btnode* delete_bst(btnode* p, datatype x){
  if(p == NULL) return NULL;

  if(p->data == x ){
    if(p->left == NULL && p->right == NULL){
      free(p);
      return NULL;
    }
    if(p->left != NULL && p->right == NULL){
      btnode* temp = p->left;
      free(p);
      return temp;
    }
    if(p->left == NULL && p->right != NULL){
      btnode* temp = p->right;
      free(p);
      return temp;
    }

    btnode* successor_p = findmin_bst(p->right);
		p->data = successor_p->data;
		p->right = delete_bst(p->right,successor_p->data);
		return p;
    
  }

  if(p->data > x){
    p->left = delete_bst(p->left, x);
  }
  else{
    p->right = delete_bst(p->right,x);
  }

  return p;
}

