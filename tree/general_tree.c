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

etnode *findNode_et(etnode *r, datatype x){
	if(r == NULL) return NULL;
	if(r->data == x) return r;
	
	etnode *p = r->leftchild,*q;
	while(p!=NULL){
		q=findNode(p,x);
		if(q!=NULL) return q;
		p = p->rightsib;
	}
	
	return NULL;
}

void addChild_et(etnode* dad, etnode* child) {
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

void preOrder(etnode *r){
	if(r == NULL) return;
	printf("%c ",r->data);
	
	etnode *p = r->leftchild;
	while(p!=NULL){
		preOrder(p);
		p = p->rightsib;
	}
}

void postOrder(etnode *r){
	if(r == NULL) return;
	
	etnode *p = r->leftchild;
	while(p!=NULL){
		postOrder(p);
		p = p->rightsib;
	}

	printf("%c ",r->data);
}

void inOrder(etnode *r){
	if(r == NULL) return;
	
	etnode *p = r->leftchild;
	inOrder(p);
	printf("%c ",r->data);
	
	if(p!=NULL) p = p->rightsib;
	while(p!=NULL){
		inOrder(p);
		p = p->rightsib;
	}
}

int count(etnode* r){
	if(r == NULL) return 0;
	int dem=1;
	
	etnode *p = r->leftchild;
	while(p!=NULL){
		dem+=count(p);
		p = p->rightsib;
	}
	
	return dem;
}


int countLeaves(etnode* r){
	if(r == NULL) return 0;
	if(r->leftchild==NULL) return 1;
	
	int dem=0;
	
	etnode *p = r->leftchild;
	while(p!=NULL){
		dem+=countLeaves(p);
		p = p->rightsib;
	}
	
	return dem;
}

int countNodeKChild(etnode* r, int k){
	if(r == NULL || k<=0) return 0;

	int dem=0,c=0;
	
	etnode *p = r->leftchild;
	while(p!=NULL){
		c++;
		dem+=countNodeKChild(p,k);
		p = p->rightsib;
	}
	
	if(c==k)
		return dem + 1;
	else return dem;
}

int height(etnode* p){
	if(p == NULL) return 0;
	int hc, maxh=0;
	
	etnode *pp = p->leftchild;
	while(pp!=NULL){
		hc=height(pp);
		if(hc>maxh) maxh=hc;
		pp = pp->rightsib;
	}
	
	return maxh+1;
}

etnode* parent(etnode* r, etnode* q){
	if(r == NULL) return NULL;
	
	etnode *p = r->leftchild;
	while(p!=NULL){
		if(p==q) return r;
		p = p->rightsib;
	}
	
	p = r->leftchild;
	etnode *pp=NULL;
	while(p!=NULL){
		pp=parent(p,q);
		if(pp!=NULL) return pp;
		p = p->rightsib;
	}
	
	return NULL;
}

int stepdepth(etnode* r, datatype v, int level){
	if(r == NULL) return 0;
	if(r->data == v) return level;
	
	etnode *p = r->leftchild;
	int lv=0;
	while(p!=NULL){
		lv=stepdepth(p,v,level+1);
		if(lv!=0) return lv;
		p = p->rightsib;
	}
	
	return 0;
}

int depth(etnode* r, datatype v){
	return stepdepth(r,v,1);
}

