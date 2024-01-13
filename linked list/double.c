#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int datatype;

typedef struct DLNode{
  datatype data;
  struct DLNode* next;
  struct DLNode* prev;
}DLNode;

typedef struct DLList{
  struct DLNode* head;
  struct DLNode* tail;
}DLList;

DLNode* makeDLNode(datatype x){
  DLNode* p = (DLNode*) malloc(sizeof(DLNode));
  p->data = x;
  p->next = NULL;
  p->prev = NULL;
  return p;
}

DLNode* makeDLList(){
  DLList* p = (DLList*) malloc(sizeof(DLList));
  p->head = NULL;
  p->tail = NULL;
  return p;
}


DLNode* findNode(DLNode* head, datatype x){
  if(head == NULL){
    return head;
  }

  DLNode* w = head;
  if(w->data == x){
    return w;
  }
  else{
    return findNode(w->next,x);
  }

}


DLNode* findprevNode(DLNode* head, DLNode* a){
  if(head == NULL || a == NULL){
    return NULL;
  }

  DLNode* w = head;
  while(w->next!=a){
    w = w->next;
  }

  return w;
}

DLNode* insertAfter(DLNode* head, DLNode* a, datatype x){
  if(a == NULL){
    return head;
  }
  DLNode* q = makeLNode(x);
  if(head == NULL){
    return q;
  }
  q->next = a->next;
  a->next = q;
  return head;
}

DLNode* insertBefore(DLNode* head, DLNode* a, datatype x){
  if(a==NULL){
    return head;
  }

  DLNode* q = makeLNode(x);
  if(head == NULL){
    return q;
  }
  if(head == a){
    q->next = head;
    return q;
  }
  
  DLNode* w = head;
  while (w->next != a) {
    w = w->next;
  }

  w->next = q;
  q->next = a;
  return head;
}

void insertLast(DLList *list, datatype x){
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

void removeNode(DLList* list, DLNode *p) {
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

DLNode* removeNode_byval(DLNode* head, datatype x){
  if(head == NULL){
    return NULL;
  }

  DLNode* prev = head;
  while(prev->next != NULL && prev->next->data != x){
    prev=prev->next;
  }
  if(prev->next == NULL){
    return head;
  }

  tofree = prev->next;
  prev->next = tofree->next;
  free(tofree);
  return head;
  
}


int nodeCount(DLNode* head){
  DLNode* w = head;
  int count = 0;
  while(w!=NULL){
    count++;
    w = w->next;
  }
  return count;
}

int count(DNode* pp, int x) {
	int dem=0;
	DLNode *p=pp;
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



