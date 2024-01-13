#include <stdio.h>
#include <stdlib.h>

typedef struct _DNode{
	int inf;
	struct _DNode *prev;
	struct _DNode *next;
} DNode;

typedef struct _DList{
	struct _DNode *first;
	struct _DNode *last;
} DList;

DNode *makeNode(int x){
	DNode *p = (DNode*) malloc(sizeof(DNode));
	if(p==NULL){printf("Error in mem allocation\n");exit(1);}
	p->inf=x;
	p->next=NULL;
	p->prev=NULL;
	return p;
}

DList *makeList(){
	DList *list=(DList*)malloc(sizeof(DList));
	if(list==NULL){
		printf("Error in mem alloc\n");
		exit(1);		
	}
	list->first=NULL;
	list->last=NULL;
	return list;
}

void printListForward(DNode *h){
	DNode *p=h;
	while(p != NULL){
		printf("%d ",p->inf);
		p = p->next;
	}
	printf("\n");
}

void printListBack(DNode *last){
	DNode *p=last;
	while(p != NULL){
		printf("%d ",p->inf);
		p = p->prev;
	}
	printf("\n");
}

void insertLast(DList *list,int x){
	DNode* q = makeNode(x);

	if(list->first == NULL && list->last == NULL){
		list->first = q;
		list->last = q;
		return;
	}
	
	q->prev = list->last;
	list->last->next = q;
	list->last = q;
}

void removeNode(DList* list, DNode *p) {
	if(p == NULL) return;
	if(list->first == NULL && list->last == NULL) return; 
	
	if(list->first == list->last && p == list->first){
		list->first = NULL;
		list->last = NULL; 
		free(p);
		return;
	}
	
	if(p == list->first){
		list->first = p->next; 
		list->first->prev = NULL;
		free(p); 
		return;
	}
	
	if(p == list->last){
		list->last = p->prev; 
		list->last->next = NULL;
		free(p); 
		return;
	}
	
	p->prev->next = p->next;
	p->next->prev = p->prev;
	free(p);
}

int count(DNode* pp, int x) {
	int dem=0;
	DNode *p=pp;
	while(p != NULL){
		if(p->inf==x) dem++;
		p = p->next;
	}
	
	p=pp;
	while(p != NULL){
		if(p->inf==x) dem++;
		p = p->prev;
	}
	
	if(pp->inf==x) dem--;
	
	return dem;
}

int main(){
	DList *list=makeList();
	DNode *nut=makeNode(1);
	list->first=nut;
	nut=makeNode(2);
	list->first->next=nut;
	nut->prev=list->first;
	nut=makeNode(3);
	list->last = nut;
	nut->prev=list->first->next;
	list->first->next->next=nut;
	
	
	insertLast(list,4);
	removeNode(list,list->first->next);
	printListForward(list->first);
	printListBack(list->last);
	
	return 0;
}
