#include <stdio.h>
#include <stdlib.h>

typedef struct _Node{
	int key;
	struct _Node* leftChild;
	struct _Node* rightChild;
} Node;


Node* makeNode(int v){
	Node *p = (Node*)malloc(sizeof(Node));
	if(p==NULL){printf("Mem error\n");exit(1);}
	p->leftChild=NULL;
	p->rightChild=NULL;
	p->key = v;
	return p;
}


Node* find_min(Node * T) {
	/* luôn đi theo con trái */
	if (T == NULL) return(NULL);
	else
		if (T->leftChild == NULL) return(T);
		else return(find_min(T->leftChild));
}


Node* find_max(Node* T) {
	/* luôn đi theo con phải */
	if (T != NULL)
		while (T->rightChild != NULL)
			T = T->rightChild;
			
	return(T);
}

void preOrder(Node *r){
		if(r==NULL) return;
		printf("%d ",r->key);
		preOrder(r->leftChild);
		preOrder(r->rightChild);
}

Node *search(Node *r, int v){
	if(r==NULL) return NULL;
	if(r->key == v) return r;
	if(r->key > v) {
		Node *tmp = search(r->leftChild,v);
		if(tmp!=NULL) return tmp;
	}
	return search(r->rightChild,v);
}

void insert_bst(Node *r, int v){
	if(r==NULL) return;
	if(r->key == v) return; //dk dung
	if(r->key > v) {
		if(r->leftChild != NULL) insert_bst(r->leftChild,v);
		else r->leftChild = makeNode(v); //dk dung
	}
	else{
		if(r->rightChild != NULL) insert_bst(r->rightChild,v);
		else r->rightChild = makeNode(v); //dk dung
	}
}

Node *delete_bst(Node *r, int v){
	if(r==NULL) return NULL;
	if(r->key == v) { //thuc hien xoa nut co khoa la v
		//TH1
		if(r->leftChild==NULL && r->rightChild==NULL)
		{
			free(r);
			return NULL;
		}
		//TH2
		if(r->leftChild!=NULL && r->rightChild==NULL)
		{
			Node *tmp = r->leftChild;
			free(r);
			return tmp;
		}
		//TH3
		if(r->leftChild==NULL && r->rightChild!=NULL)
		{
			Node *tmp = r->rightChild;
			free(r);
			return tmp;
		}
		//TH4
		Node *successor_r = find_min(r->rightChild);
		//printf("%d\n",successor_r->key);
		r->key = successor_r->key;
		r->rightChild = delete_bst(r->rightChild,successor_r->key);
		return r;
	}
	
	if(r->key > v){
		r->leftChild = delete_bst(r->leftChild,v);
	} 
	else 
	{
		r->rightChild = delete_bst(r->rightChild,v);
	}
	return r;
}


int main(){
	/*xay dung cay nhi phan giong trong slide tham khao 17*/
	Node* root=makeNode(43);
	root->leftChild = makeNode(31);
	root->rightChild = makeNode(64);
	root->leftChild->leftChild = makeNode(20);
	root->leftChild->rightChild = makeNode(40);
	root->rightChild->leftChild = makeNode(56);
	root->rightChild->rightChild = makeNode(89);
	root->leftChild->leftChild->rightChild = makeNode(28);
	root->leftChild->rightChild->leftChild = makeNode(33);
	root->rightChild->leftChild->leftChild = makeNode(47);
	root->rightChild->leftChild->rightChild = makeNode(59);
	
	preOrder(root);
	Node *tmp = find_min(root);
	if(tmp!=NULL) printf("\nmin=%d\n",tmp->key);
	tmp = find_max(root);
	if(tmp!=NULL) printf("max=%d\n",tmp->key);
	tmp = search(root,300);
	if(tmp!=NULL) printf("\nkhoa300=%d\n",tmp->key);
	tmp = search(root,33);
	if(tmp!=NULL) printf("\nkhoa33=%d\n",tmp->key);
	
	printf("chen 70\n");
	insert_bst(root,70);
	preOrder(root);
	printf("\nchen 100\n");
	insert_bst(root,100);
	preOrder(root);
	printf("\n xoa 100\n");
	delete_bst(root, 100);
	preOrder(root);
	printf("\n xoa 70\n");
	delete_bst(root, 70);
	preOrder(root);
	printf("\n xoa 40\n");
	delete_bst(root, 40);
	preOrder(root);
	printf("\n xoa 20\n");
	delete_bst(root, 20);
	preOrder(root);
	printf("\n xoa 47\n");
	delete_bst(root, 47);
	preOrder(root);
	printf("\n xoa 43\n");
	delete_bst(root, 43);
	preOrder(root);
	
	return 0;
}
