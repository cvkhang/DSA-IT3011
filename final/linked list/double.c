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

DLList* makeDLList(){
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

void insertAfter(DLList* list, DLNode* a, datatype x){
  if(list == NULL || a == NULL) return;

  DLNode* q = makeDLNode(x);

  q->next = a->next;
  q->prev = a;

  if(a->next != NULL){
    a->next->prev = q;
  } else {
    list->tail = q;
  }

  a->next = q;
}

void insertBefore(DLList* list, DLNode* a, datatype x){
  if(list == NULL || a == NULL) return;

  DLNode* q = makeDLNode(x);

  q->next = a;
  q->prev = a->prev;

  if(a->prev != NULL){
    a->prev->next = q;
  } else {
    list->head = q;
  }

  a->prev = q;
}

void insertFirst(DLList* list, datatype x){
  if(list == NULL) return;

  DLNode* q = makeDLNode(x);

  if(list->head == NULL && list->tail == NULL){
    list->head = q;
    list->tail = q;
    return;
  }

  q->next = list->head;
  list->head->prev = q;
  list->head = q;
}

void insertLast(DLList *list, datatype x){
	DLNode* q = makeDLNode(x);

	if(list->head == NULL && list->tail == NULL){
		list->head = q;
		list->tail = q;
		return;
	}
	
	q->prev = list->tail;
	list->tail->next = q;
	list->tail = q;
}

void removeNode(DLList* list, DLNode *p) {
  if(list == NULL || p == NULL) return;
  if(list->head == NULL && list->tail == NULL) return; 

  if(list->head == list->tail && p == list->head){
    list->head = NULL;
    list->tail = NULL; 
    free(p);
    return;
  }

  if(p == list->head){
    list->head = p->next; 
    list->head->prev = NULL;
    free(p); 
    return;
  }

  if(p == list->tail){
    list->tail = p->prev; 
    list->tail->next = NULL;
    free(p); 
    return;
  }

  p->prev->next = p->next;
  p->next->prev = p->prev;
  free(p);
}

void removeNode_byval(DLList* list, datatype x){
  if(list == NULL) return;

  DLNode* p = list->head;

  while(p != NULL && p->data != x){
    p = p->next;
  }

  if(p == NULL) return;

  removeNode(list, p);
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

int countValue(DLList* list, datatype x){
  if(list == NULL) return 0;

  int dem = 0;
  DLNode* p = list->head;

  while(p != NULL){
    if(p->data == x) dem++;
    p = p->next;
  }

  return dem;
}

void printForward(DLList* list){
  if(list == NULL) return;

  DLNode* p = list->head;

  while(p != NULL){
    printf("%d ", p->data);
    p = p->next;
  }

  printf("\n");
}

void printBackward(DLList* list){
  if(list == NULL) return;

  DLNode* p = list->tail;

  while(p != NULL){
    printf("%d ", p->data);
    p = p->prev;
  }

  printf("\n");
}



