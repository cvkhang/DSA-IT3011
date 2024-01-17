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

btnode *delete_bst(btnode *r, datatype v){
	if(r==NULL) return NULL;
	if(r->data == v) { //thuc hien xoa nut co khoa la v
		//TH1
		if(r->left==NULL && r->right==NULL)
		{
			free(r);
			return NULL;
		}
		//TH2
		if(r->left!=NULL && r->right==NULL)
		{
			btnode *tmp = r->left;
			free(r);
			return tmp;
		}
		//TH3
		if(r->left==NULL && r->right!=NULL)
		{
			btnode *tmp = r->right;
			free(r);
			return tmp;
		}
		//TH4
		btnode *successor_r = findmin_bst(r->right);
		r->data = successor_r->data;
		r->right = delete_bst(r->right,successor_r->data);
		return r;
	}
	
	if(r->data > v){
		r->left = delete_bst(r->left,v);
	} 
	else 
	{
		r->right = delete_bst(r->right,v);
	}
	return r;
}

