#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* datatype;

typedef struct etnode{
  datatype data;
  struct etnode* leftchild;
  struct etnode* rightsib;
} etnode;


etnode* makeNode(datatype x){
  etnode* p = (etnode*) malloc(sizeof(etnode));
  p->data = x;
  p->leftchild = NULL;
  p->rightsib = NULL;
  return p;
}


etnode* findNode2(datatype x, etnode** p,int p_count){

  for(int i = 0; i < p_count; i++){
    if(p[i] != NULL && strcmp(p[i]->data,x) == 0){
      return p[i];
    }
  }
  return NULL;
}

void addChild2(etnode* child, etnode* dad) {
  if (dad->leftchild == NULL) {
    dad->leftchild = child;
  }
  else {
    etnode* temp = dad->leftchild;
    while (temp->rightsib != NULL) {
      temp = temp->rightsib;
    }
    temp->rightsib = child;
  }
}

int treeHeight(etnode* p, int current_height, int* max_height){
  if(p == NULL){
    return current_height;
  }
  etnode* q = p->leftchild;
  while(q != NULL){
    if(current_height+1 > *max_height){
      *max_height = current_height + 1;
    }
    treeHeight(q,current_height + 1,max_height);
    q = q->rightsib;
  }
  return 0;
}

void countDescen(etnode* p, int* count) {
  if (p == NULL) {
    return;
  }

  if (p->leftchild != NULL) {
    (*count)++;
    countDescen(p->leftchild, count);
  }
  
  countDescen(p->rightsib, count);
}

int countDescen2(etnode* p) {
  int count = 0;
  
  if (p->leftchild != NULL) {
    count++;
    count += countDescen2(p->leftchild);
  }
  
  if (p->rightsib != NULL) {
    count += countDescen2(p->rightsib);
  }
  
  return count;
}

void printDescendants(etnode* p,int* count) {
  if (p == NULL) {
    return;
  }

  etnode* q = p->leftchild;
  while (q != NULL) {
    (*count)++;
    printDescendants(q,count);
    q = q->rightsib;
  }

}

int main(){
  
  etnode** p = (etnode**) calloc(1,sizeof(etnode*));
  memset(p, 0, sizeof(etnode*) * 1);
  int p_count = 0;
  int result[30];
  int count_result=0;


    while(1){
      char* line = (char*) calloc(43,sizeof(char));
      fgets(line, 43, stdin);
      line[strlen(line)-1] = '\0';
      char* temp1 = strtok(line, " ");
      char* temp2 = strtok(NULL, " ");
      if(strcmp(line,"***") == 0){
        free(line);
        break;
      }

      etnode* child = findNode2(temp1,p,p_count);
      
      if(child == NULL){
        child = makeNode(temp1);
        p[p_count] = child;
        p_count++;
        p = (etnode**) realloc(p,sizeof(etnode*) * (p_count+1));
      }

      etnode* dad = findNode2(temp2,p,p_count);
      if(dad == NULL){
        dad = makeNode(temp2);
        p[p_count] = dad;
        p_count++;
        p = (etnode**) realloc(p,sizeof(etnode*) * (p_count+1));
      }

      addChild2(child,dad);

    }

    while(1){
            char* line = (char*) calloc(43,sizeof(char));
            fgets(line, 43, stdin);
            line[strlen(line)-1] = '\0';
            char* cmd = strtok(line, " ");
            char* cmd2 = strtok(NULL, " ");
      if(strcmp(line,"***") == 0){
        free(cmd);
        free(cmd2);
        free(line);
        break;
      }
      else if(strcmp(cmd,"descendants") == 0){
        int* count = (int*) malloc(sizeof(int));
        *count = 0;
        printDescendants(findNode2(cmd2,p,p_count),count);
        result[count_result] = *count;
        count_result++;
        //printf("%d\n",*count);
        free(count);
      }
      else if(strcmp(cmd,"generation") == 0){
        int* count = (int*) malloc(sizeof(int));
        *count = 0;
        treeHeight(findNode2(cmd2,p,p_count),0,count);
        result[count_result] = *count;
        count_result++;
        //printf("%d\n",*count);
        free(count);
      }
    }
    for(int i=0; i < count_result; i++){
      printf("%d\n",result[i]);
    }

    return 0;
}
