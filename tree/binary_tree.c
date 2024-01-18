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

int height(btnode *r){
	if(r == NULL) return 0;	
	
	int hl = height(r->left);
	int hr = height(r->right);
	
	if(hl>hr) return hl+1;
	else return hr+1;
}

int count(btnode *r){
	if(r == NULL) return 0;
	int dem=1;
		
	dem += count(r->left);
	dem += count(r->right);

	return dem;
}

int countLeaves(btnode* r){
	if(r == NULL) return 0;
	if(r->left==NULL && r->right==NULL) return 1;
	int dem=0;
		
	dem += countLeaves(r->left);
	dem += countLeaves(r->right);

	return dem;
}

int countNodeKChild(btnode *r, int k){
	if(r == NULL || k<0 || k>2) return 0;
	int dem=0,c=0;
	
	dem += countNodeKChild(r->left,k);
	dem += countNodeKChild(r->right,k);
	
	if(r->left!=NULL) c++;
	if(r->right!=NULL) c++;
	
	if(c==k) dem++;
	
	return dem;
}

int countNodeLeftChild(btnode *r){
	if(r == NULL) return 0;
	int dem=0;
	
	dem += countNodeLeftChild(r->left);
	dem += countNodeLeftChild(r->right);
	
	if(r->left!=NULL && r->right==NULL) dem++;
	
	return dem;
}

btnode* parent(btnode* r, btnode* p){
	if(r == NULL) return NULL;
	if(r->left == p || r->right == p) return r;
	
	btnode* q = parent(r->left,p);
	if(q!=NULL) return q;
	
	return parent(r->right,p);
}

int stepdepth(btnode* r, btnode* p, int k){
	if(r == NULL) return 0;
	if(r == p) return k;

	int l1 = stepdepth(r->left, p, k+1);
	if(l1!=0) return l1;
	
	return stepdepth(r->right, p, k+1);
}

int depth(btnode* r, btnode* p){
	if(r == NULL || p == NULL) return 0;
	
	return stepdepth(r,p,1);
}

