#include <stdio.h>
#include <stdlib.h>

typedef struct _Node{
	int inf;
	struct _Node *next;
} Node;

Node *makeNode(int x){
	Node *p = (Node*) malloc(sizeof(Node));
	if(p==NULL){printf("Error in mem allocation\n");exit(1);}
	p->inf=x;
	p->next=NULL;
	return p;
}

void printList(Node *h){
	Node *p=h;
	while(p != NULL){
		printf("%d ",p->inf);
		p = p->next;
	}
	printf("\n");
}

Node *insertHead(Node *h,int x){
	Node* q = makeNode(x);

	if(h == NULL){
		return q;
	}
	
	q->next = h;
	return q;
}

Node *daods1(Node *h){
	Node *dsdaura=NULL;
	while(h!=NULL){
		dsdaura=insertHead(dsdaura,h->inf);
		h=h->next;
	}
	return dsdaura;
}

Node *daods2(Node *h){
	if(h==NULL||h->next==NULL) return h;
	Node *p1=NULL,*p2=h,*p3=h->next;
	while(p2!=NULL){
		p2->next=p1;
		p1=p2;
		p2=p3;
		if(p3!=NULL) p3=p3->next;
	}
	
	return p1;
}

Node *daods3(Node *h){
	if(h==NULL) return h;
	if(h->next==NULL) return h;
	Node *tmp=daods3(h->next);
	h->next->next=h;
	h->next=NULL;
	return tmp;
}

int main(){
	Node *head=NULL,*ds;
	for(int i=10;i>0;i--){
		head=insertHead(head,i);		
	}
	
	printList(head);
	printf("daods3:\n");
	ds=daods3(head);
	printList(ds);
	
	return 0;
}
