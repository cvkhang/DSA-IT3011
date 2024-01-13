#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int datatype;

typedef struct LNode{
  datatype data;
  struct LNode* next;
}LNode;

LNode* makeLNode(datatype x){
  LNode* p = (LNode*) malloc(sizeof(LNode));
  p->data = x;
  p->next = NULL;
  return p;
}


LNode* findNode(LNode* head, datatype x){
  if(head == NULL){
    return head;
  }

  LNode* w = head;
  if(w->data == x){
    return w;
  }
  else{
    return findNode(w->next,x);
  }

}


LNode* findprevNode(LNode* head, LNode* a){
  if(head == NULL || a == NULL){
    return NULL;
  }

  LNode* w = head;
  while(w->next!=a){
    w = w->next;
  }

  return w;
}

LNode* insertAfter(LNode* head, LNode* a, datatype x){
  if(a == NULL){
    return head;
  }
  LNode* q = makeLNode(x);
  if(head == NULL){
    return q;
  }
  q->next = a->next;
  a->next = q;
  return head;
}

LNode* insertBefore(LNode* head, LNode* a, datatype x){
  if(a==NULL){
    return head;
  }

  LNode* q = makeLNode(x);
  if(head == NULL){
    return q;
  }
  if(head == a){
    q->next = head;
    return q;
  }
  
  LNode* w = head;
  while (w->next != a) {
    w = w->next;
  }

  w->next = q;
  q->next = a;
  return head;
}

LNode* insertLast(LNode* head, datatype x){
  LNode* p = makeLNode(x);

  if(head == NULL){
    return p;
  }

  LNode* w = head;
  while(w->next != NULL){
    w = w->next;
  }
  w->next = p;

  return head;  
}

LNode* removeNode(LNode* head, LNode* a){
  if(head == NULL || a == NULL){
    return head;
  }

  LNode* prev = findprevNode(head,a);
  prev->next = a->next;
  free(a);
  return head;
}

LNode* removeNode_byval(LNode* head, datatype x){
  if(head == NULL){
    return NULL;
  }

  LNode* prev = head;
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


int nodeCount(LNode* head){
  LNode* w = head;
  int count = 0;
  while(w!=NULL){
    count++;
    w = w->next;
  }
  return count;
}



