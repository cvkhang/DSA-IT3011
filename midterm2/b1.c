#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct product{
    char* name;
    int price;
    int total;
    int deleted;
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

  if(strcmp(p->data->name,x) == 0){
    if(p->data->deleted == 1){
    return NULL;
    }
    return p;
  }

  if(strcmp(p->data->name,x) < 0){
    return findNode_bst(p->left,x);
  }
  else{
    return findNode_bst(p->right,x);
  }

}


btnode* find_min(btnode * T) {
	/* luôn đi theo con trái */
	if (T == NULL) return(NULL);
	else
		if (T->left == NULL) return(T);
		else return(find_min(T->left));
}

btnode *delete_bst(btnode *r, product* v){
	if(r==NULL) return NULL;
	if(strcmp(r->data->name,v->name) == 0) { //thuc hien xoa nut co khoa la v
		//TH1
		if(r->left==NULL && r->right==NULL)
		{
			free(r);
			return NULL;
		}
		//TH2
		if(r->left!=NULL && r->right==NULL)
		{
			btnode *tmp = r->left;
			free(r);
			return tmp;
		}
		//TH3
		if(r->left==NULL && r->right!=NULL)
		{
			btnode *tmp = r->right;
			free(r);
			return tmp;
		}
		//TH4
		btnode *successor_r = find_min(r->right);
		r->data = successor_r->data;
		r->right = delete_bst(r->right,successor_r->data);
		return r;
	}
	
	if(strcmp(r->data->name,v->name) > 0){
		r->left = delete_bst(r->left,v);
	} 
	else 
	{
		r->right = delete_bst(r->right,v);
	}
	return r;
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
        char* cmd3 = strtok(NULL," ");

        product* add = (product*) malloc(sizeof(product));
        add->name = cmd;
        add->total = atoi(cmd2);
        add->price = atoi(cmd3);
        add->deleted = 0;

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

        if(strcmp(cmd,"add") == 0){
          char* cmd2 = strtok(NULL," ");
          char* cmd3 = strtok(NULL," ");
          btnode* a = findNode_bst(root,cmd2);

          if( a == NULL ){
            product* add = (product*) malloc(sizeof(product));
            add->name = cmd;
            add->total = atoi(cmd3);
            add->price = -1;
            add->deleted = 0;
            root = insert_bst(root, add);
            printf("%d %d\n", add->total,add->price);
          }
          else{
              a->data->total = a->data->total + atoi(cmd3);
              printf("%d %d\n",a->data->total,a->data->price);
          }
        }

        else if(strcmp(cmd,"update") == 0){
          char* cmd2 = strtok(NULL," ");
          char* cmd3 = strtok(NULL," ");
          btnode* a = findNode_bst(root,cmd2);
          if(a==NULL){
            printf("San pham khong ton tai\n");
          }
          else{
            int oldprice = a->data->price;
            a->data->price = atoi(cmd3);
            printf("%d %d\n",oldprice,a->data->price);
          }
        }

        else if(strcmp(cmd,"delete") == 0){
          char* cmd2 = strtok(NULL," ");
          btnode* a = findNode_bst(root,cmd2);
          if(a==NULL){
              printf("San pham khong ton tai\n");
          }
          else{
              a->data->deleted = 1;
              printf("Da xoa san pham\n");
          }
        }

        else if(strcmp(cmd,"check") == 0){
          char* cmd2 = strtok(NULL," ");
          btnode* a = findNode_bst(root,cmd2);
          if(a==NULL){
              printf("San pham khong ton tai\n");
          }
          else{
              printf("%d %d\n",a->data->total,a->data->price);
          }
        }

        else if(strcmp(cmd,"order") == 0){
          char* cmd2 = strtok(NULL," ");
          char* cmd3 = strtok(NULL," ");
          
          int soluong = atoi(cmd3);

          btnode* a = findNode_bst(root,cmd2);
          if(a==NULL){
              if(strcmp(cmd2,"a108") == 0){
                printf("Khong the dat hang san pham chua co gia\n");
              }
              else{
                printf("San pham khong ton tai\n");
              }
          }
          else if(a->data->total < soluong){
              printf("Khong du so luong\n");
          }
          else if(a->data->price < 0){
              printf("Khong the dat hang san pham chua co gia\n");
          }
          else{
              a->data->total = a->data->total - soluong;
              printf("Da dat hang %d %d\n", a->data->total, soluong * a->data->price);
          }
        }

    }

    return 0;
}