#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int datatype;

typedef struct btnode{
  datatype data;
  struct btnode* left;
  struct btnode* right; 
}btnode;

typedef struct btree{
  btnode* root;
  int size;
  int height;
}btree;

btnode* makeNode(datatype x){
  btnode* p = (btnode*) malloc(sizeof(btnode));
  p->data = x;
  p->left = NULL;
  p->right = NULL;
  return p;
}

btree* makeTree(){
  btree* t = (btree*) malloc(sizeof(btree));
  t->root = NULL;
  t->size = 0;
  t->height = 0;
  return t;
}

btnode* insert_bst(btnode* root,datatype x){
      
  if (root == NULL){
    return makeNode(x);
  }

  if (x < root->data){
    root->left = insert_bst(root->left, x);
  }
  else{
    root->right = insert_bst(root->right, x);
  }

  return root;
}

btnode* findNode_bst(btnode* p, datatype x){
  if(p == NULL)  return NULL;
  if(p->data == x) return p;

  if(p->data > x){
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

btnode* findmax_bst(btnode* r){
    if(r == NULL) return NULL;

    while(r->right != NULL){
        r = r->right;
    }

    return r;
}

btnode *delete_bst(btnode *r, datatype v){
	if(r==NULL) return NULL;
	if(r->data == v) { //thuc hien xoa nut co khoa la v
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
		btnode *successor_r = findmin_bst(r->right);
		r->data = successor_r->data;
		r->right = delete_bst(r->right,successor_r->data);
		return r;
	}
	
	if(r->data > v){
		r->left = delete_bst(r->left,v);
	} 
	else 
	{
		r->right = delete_bst(r->right,v);
	}
	return r;
}

void inorder_bst(btnode* r){
    if(r == NULL) return;

    inorder_bst(r->left);
    printf("%d ", r->data);
    inorder_bst(r->right);
}

void reverseInorder_bst(btnode* r){
    if(r == NULL) return;

    reverseInorder_bst(r->right);
    printf("%d ", r->data);
    reverseInorder_bst(r->left);
}

int count_bst(btnode* r){
    if(r == NULL) return 0;

    return 1
         + count_bst(r->left)
         + count_bst(r->right);
}

int height_bst(btnode* r){
    if(r == NULL) return 0;

    int hl = height_bst(r->left);
    int hr = height_bst(r->right);

    return (hl > hr ? hl : hr) + 1;
}

int countLeaves_bst(btnode* r){
    if(r == NULL) return 0;

    if(r->left == NULL && r->right == NULL){
        return 1;
    }

    return countLeaves_bst(r->left)
         + countLeaves_bst(r->right);
}

btnode* deleteMin_bst(btnode* r){
    if(r == NULL) return NULL;

    if(r->left == NULL){
        btnode* rightChild = r->right;
        free(r);
        return rightChild;
    }

    r->left = deleteMin_bst(r->left);
    return r;
}

btnode* deleteMax_bst(btnode* r){
    if(r == NULL) return NULL;

    if(r->right == NULL){
        btnode* leftChild = r->left;
        free(r);
        return leftChild;
    }

    r->right = deleteMax_bst(r->right);
    return r;
}

btnode* predecessor_bst(btnode* root, datatype x){
    btnode* result = NULL;

    while(root != NULL){
        if(root->data < x){
            result = root;
            root = root->right;
        }
        else{
            root = root->left;
        }
    }

    return result;
}

btnode* successor_bst(btnode* root, datatype x){
    btnode* result = NULL;

    while(root != NULL){
        if(root->data > x){
            result = root;
            root = root->left;
        }
        else{
            root = root->right;
        }
    }

    return result;
}

btnode* kthSmallestHelper(btnode* r, int* k){
    if(r == NULL) return NULL;

    btnode* result = kthSmallestHelper(r->left, k);
    if(result != NULL){
        return result;
    }

    (*k)--;

    if(*k == 0){
        return r;
    }

    return kthSmallestHelper(r->right, k);
}

btnode* kthSmallest_bst(btnode* root, int k){
    if(k <= 0) return NULL;

    return kthSmallestHelper(root, &k);
}

void printRange_bst(btnode* r, datatype low, datatype high){
    if(r == NULL) return;

    if(r->data > low){
        printRange_bst(r->left, low, high);
    }

    if(r->data >= low && r->data <= high){
        printf("%d ", r->data);
    }

    if(r->data < high){
        printRange_bst(r->right, low, high);
    }
}

