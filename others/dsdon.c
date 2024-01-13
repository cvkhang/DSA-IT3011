#include <stdio.h>
#include <stdlib.h>

typedef struct _Node{
	int value;
	struct _Node* next;
}Node;

void printList(Node *head){
	while(head!=NULL){
		printf("%d ",head->value);
		head=head->next;
	}
}

void freeList(Node *head){
	Node *tmp;
	while(head!=NULL){
		tmp=head->next;
		free(head);
		head=tmp;
	}
}

Node* findLast(Node* head){
	Node* p = head;
	while(p != NULL){
		if(p->next == NULL) return p;
		p = p->next;
	}
	return NULL;
}

Node *makeNode(int x){
	Node* tmp=(Node*)malloc(sizeof(Node));
	if(tmp==NULL){
		printf("Error in mem allocation\n");
		exit(1);
	}
	tmp->value=x;
	tmp->next=NULL;
	return tmp;
}

Node *insertHead(Node *head,int x){
	Node* tmp=makeNode(x);
	tmp->next=head;
	return tmp;
}

Node* insertAfter(Node* head, Node* p, int x){
	if(p == NULL) return head;
	Node* q = makeNode(x);
	if(head == NULL) return q;
	q->next = p->next;
	p->next = q;
	return head;
}


Node* insertLast(Node* head, int x){
	Node* q = makeNode(x);
	if(head == NULL)
		return q;
	
	Node* p = head;
	while(p->next != NULL)
		p = p->next;
	
	p->next = q;
	return head;
}

Node* locate(Node* head, int x){
	Node* p = head;
	while(p != NULL){
		if(p->value == x) return p;
		p = p->next;
	}
	return NULL;
}

Node* prev(Node* head, Node* p){
	Node* q = head;
	while(q != NULL){
		if(q->next == p) return q;
		q = q->next;
	}
	return NULL;
}


Node* insertAtRecursive(Node* head, Node* p, int x){
	if(p == NULL) return head;
	if(head == NULL) return makeNode(x);
	if(p == head){
		Node *tmp=makeNode(x);
		tmp->next=p;
		return tmp;
	}else{
		head->next = insertAtRecursive(head->next,p,x);
		return head;
	}
}

Node* insertAt(Node* head, Node* p, int x){
	if(p == NULL)
		return head;
		
	Node* pp = prev(head,p);
	Node* q = makeNode(x);
	if(pp == NULL){
		if(head == NULL)
			return q;
		q->next = head;
		return q;
	}
	
	q->next = p;
	pp->next = q;
	return head;
}

Node* removeElement(Node* head, Node* p){
	if(head == NULL || p == NULL) return head;
	if(head == p){
		head = head->next;
		free(p);
		return head;
	}else{
		head->next = removeElement(head->next,p);
		return head;
	}
}

int sum(Node* head){
	Node* p = head;

	int S = 0;
	while(p != NULL) {
		S = S + p->value;
		p = p->next;
	}
	return S;
}

int sumRecursive(Node* head){
	if(head == NULL) return 0;
	return head->value + sumRecursive(head->next);
}

int main(){
	Node* head=makeNode(1);
	
	Node* tmp=makeNode(2);
	head->next=tmp;
	
	tmp=makeNode(3);
	head->next->next=tmp;
	
	int k=4;
	Node *p_old=tmp;
	while(k<1001){
		tmp=(Node*)malloc(sizeof(Node));
		tmp->value=k;
		tmp->next=NULL;
		p_old->next=tmp;
		p_old=tmp;
		k++;
	}

	head=insertHead(head,0);
	insertAfter(head,head->next,1001);
	insertLast(head,1002);
	insertAtRecursive(head,head->next,-1);
	removeElement(head,head->next);
	printList(head);
	tmp=findLast(head);
	printf("\nnutcuoi:%d\n",tmp->value);
	tmp=locate(head,501);
	printf("\nnut501:%d\n",tmp->value);
	tmp=prev(head,head->next->next);
	printf("\nnut1:%d\n",tmp->value);
	printf("\nsum:%d\n",sum(head));
	printf("\nsum:%d\n",sumRecursive(head));
	freeList(head);
	
	return 0;
}
