#include <stdio.h>
#include <stdlib.h>

typedef char datatype;
typedef struct _TNode{
	datatype inf;
	struct _TNode* leftMostChild;// con tro tro den nut con trai nhat
	struct _TNode* rightSibling;// con tro tro den nut anh em ben phai
}TNode;

TNode *makeNode(datatype x){
	TNode *p = (TNode*) malloc(sizeof(TNode));
	if(p==NULL){printf("Error in mem allocation\n");exit(1);}
	p->inf=x;
	p->leftMostChild=NULL;
	p->rightSibling=NULL;
	return p;
}

void preOrder(TNode *r){
	if(r == NULL) return;
	printf("%c ",r->inf);
	
	TNode *p = r->leftMostChild;
	while(p!=NULL){
		preOrder(p);
		p = p->rightSibling;
	}
}

void postOrder(TNode *r){
	if(r == NULL) return;
	
	TNode *p = r->leftMostChild;
	while(p!=NULL){
		postOrder(p);
		p = p->rightSibling;
	}

	printf("%c ",r->inf);
}

void inOrder(TNode *r){
	if(r == NULL) return;
	
	TNode *p = r->leftMostChild;
	inOrder(p);
	printf("%c ",r->inf);
	
	if(p!=NULL) p = p->rightSibling;
	while(p!=NULL){
		inOrder(p);
		p = p->rightSibling;
	}
}

void freeTree(TNode *r){
	if(r == NULL) return;
	
	TNode *p = r->leftMostChild;
	while(p!=NULL){
		freeTree(p);
		p = p->rightSibling;
	}

	free(r);
}

TNode *find(TNode *r, datatype x){
	if(r == NULL) return NULL;
	if(r->inf == x) return r;
	
	TNode *p = r->leftMostChild,*q;
	while(p!=NULL){
		q=find(p,x);
		if(q!=NULL) return q;
		p = p->rightSibling;
	}
	
	return NULL;
}


int count(TNode* r){
	if(r == NULL) return 0;
	int dem=1;
	
	TNode *p = r->leftMostChild;
	while(p!=NULL){
		dem+=count(p);
		p = p->rightSibling;
	}
	
	return dem;
}


int countLeaves(TNode* r){
	if(r == NULL) return 0;
	if(r->leftMostChild==NULL) return 1;
	
	int dem=0;
	
	TNode *p = r->leftMostChild;
	while(p!=NULL){
		dem+=countLeaves(p);
		p = p->rightSibling;
	}
	
	return dem;
}

int countNodeKChild(TNode* r, int k){
	if(r == NULL || k<=0) return 0;

	int dem=0,c=0;
	
	TNode *p = r->leftMostChild;
	while(p!=NULL){
		c++;
		dem+=countNodeKChild(p,k);
		p = p->rightSibling;
	}
	
	if(c==k)
		return dem + 1;
	else return dem;
}

int height(TNode* p){
	if(p == NULL) return 0;
	int hc, maxh=0;
	
	TNode *pp = p->leftMostChild;
	while(pp!=NULL){
		hc=height(pp);
		if(hc>maxh) maxh=hc;
		pp = pp->rightSibling;
	}
	
	return maxh+1;
}

TNode* parent(TNode* r, TNode* q){
	if(r == NULL) return NULL;
	
	TNode *p = r->leftMostChild;
	while(p!=NULL){
		if(p==q) return r;
		p = p->rightSibling;
	}
	
	p = r->leftMostChild;
	TNode *pp=NULL;
	while(p!=NULL){
		pp=parent(p,q);
		if(pp!=NULL) return pp;
		p = p->rightSibling;
	}
	
	return NULL;
}

TNode* parent2(TNode* r, TNode* q){
	if(r == NULL) return NULL;
	
	TNode *p = r->leftMostChild,*pp;
	while(p!=NULL){
		if(p==q) return r;
		pp=parent2(p,q);
		if(pp!=NULL) return pp;
		p = p->rightSibling;
	}
	
	return NULL;
}

int stepdepth(TNode* r, datatype v, int level){
	if(r == NULL) return 0;
	if(r->inf == v) return level;
	
	TNode *p = r->leftMostChild;
	int lv=0;
	while(p!=NULL){
		lv=stepdepth(p,v,level+1);
		if(lv!=0) return lv;
		p = p->rightSibling;
	}
	
	return 0;
}

int depth(TNode* r, datatype v){
	return stepdepth(r,v,1);
}

int main(){
	TNode *root=NULL;
	
	TNode *nutA=makeNode('A');
	TNode *nutB=makeNode('B');
	TNode *nutC=makeNode('C');
	TNode *nutD=makeNode('D');
	TNode *nutE=makeNode('E');
	TNode *nutF=makeNode('F');
	TNode *nutG=makeNode('G');
	TNode *nutH=makeNode('H');
	TNode *nutI=makeNode('I');
	TNode *nutJ=makeNode('J');
	TNode *nutK=makeNode('K');
	
	root=nutA;
	nutA->leftMostChild = nutB;
	
	nutB->leftMostChild = nutE;
	nutB->rightSibling = nutC;
	
	nutC->leftMostChild = nutG;
	nutC->rightSibling = nutD;
	
	nutE->rightSibling = nutF;
	
	nutG->leftMostChild = nutH;
	
	nutH->rightSibling = nutI;
	nutI->rightSibling = nutJ;
	nutJ->rightSibling = nutK;
	
	preOrder(root);
	printf("\n");
	postOrder(root);
	printf("\n");
	inOrder(root);
	printf("\n");
	
	TNode *nuttimthay=find(root,'I');
	if(nuttimthay!=NULL) printf("nuttimthay:%c\n",nuttimthay->inf);
	
	printf("sonuttrencay=%d\n",count(root));
	printf("sonutlatrencay=%d\n",countLeaves(root));
	printf("sonutco4contrencay=%d\n",countNodeKChild(root,4));
	printf("chieucaocuacay=%d\n",height(root));
	
	nuttimthay=parent2(root,nutJ);
	if(nuttimthay!=NULL) printf("chacuaJ=%c\n",nuttimthay->inf);
	
	printf("dosaucuanutF=%d\n",depth(root,'F'));
	
	printf("giaiphong\n");
	freeTree(root);
	root=NULL;
	//if(root!=NULL) printf("root:%c\n",root->inf);
	
	return 0;
}
