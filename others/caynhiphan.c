#include <stdio.h>
#include <stdlib.h>

typedef char datatype;
typedef struct _BNode{
	datatype id;
	struct _BNode* leftChild;// con tro tro den nut con trai 
	struct _BNode* rightChild;// con tro tro den nut con phai
} BNode;

BNode *makeNode(datatype x){
	BNode *p = (BNode*) malloc(sizeof(BNode));
	if(p==NULL){printf("Error in mem allocation\n");exit(1);}
	p->id=x;
	p->leftChild=NULL;
	p->rightChild=NULL;
	return p;
}

void preOrder(BNode* r) {
	if(r == NULL) return;
	printf("%c ",r->id);
	preOrder(r->leftChild);
	preOrder(r->rightChild);
}

void postOrder(BNode* r) {
	if(r == NULL) return;
	postOrder(r->leftChild);
	postOrder(r->rightChild);
	printf("%c ",r->id);
}

void inOrder(BNode* r) {
	if(r == NULL) return;
	inOrder(r->leftChild);
	printf("%c ",r->id);
	inOrder(r->rightChild);
}

int count(BNode *r){
	if(r == NULL) return 0;
	int dem=1;
		
	dem += count(r->leftChild);
	dem += count(r->rightChild);

	return dem;
}

int countLeaves(BNode* r){
	if(r == NULL) return 0;
	if(r->leftChild==NULL && r->rightChild==NULL) return 1;
	int dem=0;
		
	dem += countLeaves(r->leftChild);
	dem += countLeaves(r->rightChild);

	return dem;
}

int countNodeKChild(BNode *r, int k){
	if(r == NULL || k<0 || k>2) return 0;
	int dem=0,c=0;
	
	dem += countNodeKChild(r->leftChild,k);
	dem += countNodeKChild(r->rightChild,k);
	
	if(r->leftChild!=NULL) c++;
	if(r->rightChild!=NULL) c++;
	
	if(c==k) dem++;
	
	return dem;
}

int countNodeLeftChild(BNode *r){
	if(r == NULL) return 0;
	int dem=0;
	
	dem += countNodeLeftChild(r->leftChild);
	dem += countNodeLeftChild(r->rightChild);
	
	if(r->leftChild!=NULL && r->rightChild==NULL) dem++;
	
	return dem;
}

int height(BNode *r){
	if(r == NULL) return 0;	
	
	int hl = height(r->leftChild);
	int hr = height(r->rightChild);
	
	if(hl>hr) return hl+1;
	else return hr+1;
}

BNode *find(BNode* r, datatype x){
	if(r == NULL) return NULL;
	if(r->id == x) return r;
	
	BNode* p = find(r->leftChild,x);
	if(p!=NULL) return p;
	
	return find(r->rightChild,x);
}

void freeTree(BNode *r){
	if(r == NULL) return;

	freeTree(r->leftChild);
	freeTree(r->rightChild);

	free(r);
}

BNode* parent(BNode* r, BNode* p){
	if(r == NULL) return NULL;
	if(r->leftChild == p || r->rightChild == p) return r;
	
	BNode* q = parent(r->leftChild,p);
	if(q!=NULL) return q;
	
	return parent(r->rightChild,p);
}

int stepdepth(BNode* r, BNode* p, int k){
	if(r == NULL) return 0;
	if(r == p) return k;

	int l1 = stepdepth(r->leftChild, p, k+1);
	if(l1!=0) return l1;
	
	return stepdepth(r->rightChild, p, k+1);
}

int depth(BNode* r, BNode* p){
	if(r == NULL || p == NULL) return 0;
	
	return stepdepth(r,p,1);
}

int main(){
	
	BNode *root=NULL;
	
	BNode *nutA=makeNode('A');
	BNode *nutB=makeNode('B');
	BNode *nutC=makeNode('C');
	BNode *nutD=makeNode('D');
	BNode *nutE=makeNode('E');
	BNode *nutF=makeNode('F');
	BNode *nutG=makeNode('G');
	BNode *nutH=makeNode('H');
	BNode *nutI=makeNode('I');
	BNode *nutJ=makeNode('J');
	BNode *nutK=makeNode('K');
	
	root=nutA;
	nutA->leftChild = nutB;
	
	nutB->leftChild = nutE;
	nutB->rightChild = nutC;
	
	nutC->leftChild = nutG;
	nutC->rightChild = nutD;
	
	nutE->rightChild = nutF;
	
	nutG->leftChild = nutH;
	
	nutH->rightChild = nutI;
	nutI->rightChild = nutJ;
	nutJ->rightChild = nutK;
	
	root=nutA;
	
	preOrder(root);
	printf("\n");
	postOrder(root);
	printf("\n");
	inOrder(root);
	printf("\n");
	
	printf("count=%d\n",count(root));
	printf("\n");
	printf("countLeaves=%d\n",countLeaves(root));
	printf("\n");
	printf("countKChild=%d\n",countNodeKChild(root,1));
	printf("\n");
	printf("countNodeLeftChild=%d\n",countNodeLeftChild(root));
	printf("\n");
	
	printf("height=%d\n",height(root));
	printf("\n");
	
	BNode *tmp=find(root,'H');
	if(tmp!=NULL) printf("findH=%c\n",tmp->id);
	
	tmp=parent(root,nutG);
	if(tmp!=NULL) printf("parentofG=%c\n",tmp->id);
	
	printf("levelofD=%d\n",depth(root,nutD));
	printf("\n");
	
	freeTree(root);
	root=NULL;
	
	return 0;
}
