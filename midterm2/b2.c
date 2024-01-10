#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct product{
    char* name;
    int weight;
}product;

typedef struct btnode{
  product* data;
  struct btnode* left;
  struct btnode* right; 
}btnode;

btnode* makeNode(product* x){
  btnode* p = (btnode*) malloc(sizeof(btnode));
  p->data = x;
  p->left = NULL;
  p->right = NULL;
  return p;
}


btnode* insert_bst(btnode* root,product* x){
      
  if (root == NULL){
    return makeNode(x);
  }

  if (strcmp(root->data->name,x->name) < 0){
    root->left = insert_bst(root->left, x);
  }
  else{
    root->right = insert_bst(root->right, x);
  }

  return root;
}

btnode* findNode_bst(btnode* p, char* x){
  if(p == NULL)  return NULL;
  if(strcmp(p->data->name,x) == 0) return p;

  if(strcmp(p->data->name,x) < 0){
    return findNode_bst(p->left,x);
  }
  else{
    return findNode_bst(p->right,x);
  }
}

btnode* findmin_bst(btnode* p){
  if(p == NULL) return NULL;
  if(p->left == NULL){
    return p;
  }
  else{ 
    return findmin_bst(p->left);
  }
}

btnode* delete_bst(btnode* p, product* x){
  if(p == NULL) return NULL;

  if(strcmp(p->data->name,x->name) == 0){
    if(p->left == NULL && p->right == NULL){
      free(p);
      return NULL;
    }
    if(p->left != NULL && p->right == NULL){
      btnode* temp = p->left;
      free(p);
      return temp;
    }
    if(p->left == NULL && p->right != NULL){
      btnode* temp = p->right;
      free(p);
      return temp;
    }

    btnode* successor_p = findmin_bst(p->right);
		p->data = successor_p->data;
		p->right = delete_bst(p->right,successor_p->data);
		return p;
    
  }

  if(strcmp(p->data->name,x->name) > 0){
    p->left = delete_bst(p->left, x);
  }
  else{
    p->right = delete_bst(p->right,x);
  }

  return p;
}

int main()
{
    int n;
    scanf("%d",&n);
    getchar();

    btnode* root = NULL;

    for(int i = 0; i<n; i++){

        char* line = (char*) calloc(50,sizeof(char));
        fgets(line,50,stdin);
        line[strlen(line)-1] = '\0';

        //command split
        char* cmd = strtok(line," ");
        char* cmd2 = strtok(NULL," ");

        product* add = (product*) malloc(sizeof(product));
        add->name = cmd;
        add->weight = atoi(cmd2);

        root = insert_bst(root, add);
    }

    int m;
    scanf("%d",&m);
    getchar();
    
    for(int i = 0; i < m; i++){

      char* line = (char*) calloc(50,sizeof(char));
      fgets(line,50,stdin);
      line[strlen(line)-1] = '\0';
      char* cmd = strtok(line," ");

      int number = atoi(cmd);
      int totalweight = 0;

      for(int j = 0; j < number; j++){
        char* cmd2 = strtok(line," ");
        char* cmd3 = strtok(line," ");
        int x = atoi(cmd3);
    
        product* a = findNode_bst(root, cmd2);
        totalweight = totalweight + x*a->weight;
      }
      printf("%d\n",totalweight);
    }

    return 0;
}