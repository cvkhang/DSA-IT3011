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
  LNode* w = head;

  while(w != NULL){
    if(w->data == x){
      return w;
    }
    w = w->next;
  }

  return NULL;
}


LNode* findprevNode(LNode* head, LNode* a){
  if(head == NULL || a == NULL || head == a){
    return NULL;
  }

  LNode* w = head;
  while(w != NULL && w->next != a){
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
  if(a == NULL){
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
  while(w != NULL && w->next != a){
    w = w->next;
  }

  if(w == NULL){
    free(q);
    return head;
  }

  w->next = q;
  q->next = a;
  return head;
}

LNode* insertFirst(LNode* head, datatype x){
  LNode* p = makeLNode(x);
  p->next = head;
  return p;
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

  if(head == a){
    LNode* newHead = head->next;
    free(head);
    return newHead;
  }

  LNode* prev = findprevNode(head, a);
  if(prev == NULL){
    return head;
  }

  prev->next = a->next;
  free(a);
  return head;
}

LNode* removeNode_byval(LNode* head, datatype x){
  if(head == NULL){
    return NULL;
  }

  if(head->data == x){
    LNode* newHead = head->next;
    free(head);
    return newHead;
  }

  LNode* prev = head;
  while(prev->next != NULL && prev->next->data != x){
    prev = prev->next;
  }

  if(prev->next == NULL){
    return head;
  }

  LNode* tofree = prev->next;
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

void printList(LNode* head){
  LNode* w = head;

  while(w != NULL){
    printf("%d ", w->data);
    w = w->next;
  }

  printf("\n");
}
