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

//Make
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

//Add
void addChild(btnode* child, btnode* dad){
  if(dad->left != NULL && dad->right != NULL){
    printf("Node Full\n");
    return;
  }

  if(dad->left == NULL){
    dad->left = child;
    return;
  }
  else{
    dad->right = child;
    return;
  }
  
}

void addLeft(btnode* child, btnode* dad){
  if(dad->left != NULL){
    return;
  }
  else{
    dad->left = child;
    return;
  }
}

void addRight(btnode* child, btnode* dad){
  if(dad->right != NULL){
    return;
  }
  else{
    dad->right = child;
    return;
  }
}

//Find
btnode* findNode(btnode* p, datatype x) {
  if (p == NULL) {
    return NULL;
  }

  if (p->data == x) {
    return p;
  }

 btnode* result = findNode(p->left, x);
  if (result != NULL) {
    return result;
  }

  return findNode(p->right, x);
}

btnode* parent(btnode* r, btnode* p){
	if(r == NULL) return NULL;
	if(r->left == p || r->right == p) return r;
	
	btnode* q = parent(r->left,p);
	if(q!=NULL) return q;
	
	return parent(r->right,p);
}

int max2(int a, int b){
    return a > b ? a : b;
}

datatype maxValue(btnode* r){
    if(r == NULL){
        printf("Tree is empty\n");
        exit(1);
    }

    datatype max = r->data;

    if(r->left != NULL)
        max = max2(max, maxValue(r->left));

    if(r->right != NULL)
        max = max2(max, maxValue(r->right));

    return max;
}

int min2(int a, int b){
    return a < b ? a : b;
}

datatype minValue(btnode* r){
    if(r == NULL){
        printf("Tree is empty\n");
        exit(1);
    }

    datatype min = r->data;

    if(r->left != NULL)
        min = min2(min, minValue(r->left));

    if(r->right != NULL)
        min = min2(min, minValue(r->right));

    return min;
}

btnode* lowestCommonAncestor(btnode* r, btnode* p, btnode* q){
    if(r == NULL || r == p || r == q)
        return r;

    btnode* leftResult =
        lowestCommonAncestor(r->left, p, q);

    btnode* rightResult =
        lowestCommonAncestor(r->right, p, q);

    if(leftResult != NULL && rightResult != NULL)
        return r;

    if(leftResult != NULL)
        return leftResult;

    return rightResult;
}

int distanceFrom(btnode* r, btnode* p){
    if(r == NULL || p == NULL) return -1;
    if(r == p) return 0;

    int leftDistance = distanceFrom(r->left, p);
    if(leftDistance != -1)
        return leftDistance + 1;

    int rightDistance = distanceFrom(r->right, p);
    if(rightDistance != -1)
        return rightDistance + 1;

    return -1;
}

int distanceBetweenNodes(btnode* root, btnode* p, btnode* q){
    if(root == NULL || p == NULL || q == NULL)
        return -1;

    btnode* lca = lowestCommonAncestor(root, p, q);
    if(lca == NULL) return -1;

    int d1 = distanceFrom(lca, p);
    int d2 = distanceFrom(lca, q);

    if(d1 == -1 || d2 == -1)
        return -1;

    return d1 + d2;
}

//Traverse
void preOrder(btnode* p){
  if(p==NULL){
    return;
  }

  printf("%d ",p->data);
  preOrder(p->left);
  preOrder(p->right);
}

void inOrder(btnode* p){
  if(p==NULL){
    return;
  }

  inOrder(p->left);
  printf("%d ",p->data);
  inOrder(p->right);
}

void postOrder(btnode* p){
  if(p==NULL){
    return;
  }

  postOrder(p->left);
  postOrder(p->right);
  printf("%d ",p->data);
}

int sumTree(btnode* r){
    if(r == NULL) return 0;

    return r->data
        + sumTree(r->left)
        + sumTree(r->right);
}

void printLevel(btnode* r, int k){
    if(r == NULL || k <= 0) return;

    if(k == 1){
        printf("%d ", r->data);
        return;
    }

    printLevel(r->left, k - 1);
    printLevel(r->right, k - 1);
}

int printPath(btnode* r, datatype x){
    if(r == NULL) return 0;

    if(r->data == x){
        printf("%d ", r->data);
        return 1;
    }

    if(printPath(r->left, x) || printPath(r->right, x)){
        printf("%d ", r->data);
        return 1;
    }

    return 0;
}

int getPath(btnode* r, datatype x, datatype path[], int* length){
    if(r == NULL) return 0;

    path[*length] = r->data;
    (*length)++;

    if(r->data == x) return 1;

    if(getPath(r->left, x, path, length)) return 1;
    if(getPath(r->right, x, path, length)) return 1;

    (*length)--;
    return 0;
}

void printRootToNodePath(btnode* root, datatype x){
    datatype path[1000];
    int length = 0;

    if(getPath(root, x, path, &length)){
        for(int i = 0; i < length; i++){
            printf("%d ", path[i]);
        }
    }else{
        printf("Not found");
    }
}

//Count
int count(btnode *r){
	if(r == NULL) return 0;
	int dem=1;
		
	dem += count(r->left);
	dem += count(r->right);

	return dem;
}

int countLeaves(btnode* r){
    if(r == NULL) return 0;
    if(isLeaf(r)) return 1;

    return countLeaves(r->left) + countLeaves(r->right);
}

int countNodeKChild(btnode *r, int k){
	if(r == NULL || k<0 || k>2) return 0;
	int dem=0,c=0;
	
	dem += countNodeKChild(r->left,k);
	dem += countNodeKChild(r->right,k);
	
	if(r->left!=NULL) c++;
	if(r->right!=NULL) c++;
	
	if(c==k) dem++;
	
	return dem;
}

int countOneChild(btnode* r){
    if(r == NULL) return 0;

    int current =
        (r->left == NULL && r->right != NULL) ||
        (r->left != NULL && r->right == NULL);

    return current
        + countOneChild(r->left)
        + countOneChild(r->right);
}

int countNodeWithOnlyLeftChild(btnode *r){
	if(r == NULL) return 0;
	int dem=0;
	
	dem += countNodeLeftChild(r->left);
	dem += countNodeLeftChild(r->right);
	
	if(r->left!=NULL && r->right==NULL) dem++;
	
	return dem;
}

int countNodeAtLevel(btnode* r, int k){
    if(r == NULL || k <= 0) return 0;
    if(k == 1) return 1;

    return countNodeAtLevel(r->left, k - 1)
         + countNodeAtLevel(r->right, k - 1);
}

int height(btnode *r){
	if(r == NULL) return 0;	
	
	int hl = height(r->left);
	int hr = height(r->right);
	
	if(hl>hr) return hl+1;
	else return hr+1;
}

int depth(btnode* r, btnode* p) {
  if (r == NULL || p == NULL) {
    return -1;
  }

  if (r == p) {
    return 0;
  }

  int leftDepth = depth(r->left, p);
  if (leftDepth != -1) {
    return leftDepth + 1;
  }

  int rightDepth = depth(r->right, p);
  if (rightDepth != -1) {
    return rightDepth + 1;
  }

  return -1;
}

int maxWidth(btnode* root){
    if(root == NULL) return 0;

    int h = height(root);
    int result = 0;

    for(int level = 1; level <= h; level++){
        int currentWidth = countNodeAtLevel(root, level);

        if(currentWidth > result)
            result = currentWidth;
    }

    return result;
}

//Check
int isLeaf(btnode* p){
    return p != NULL && p->left == NULL && p->right == NULL;
}

int isSameTree(btnode* r1, btnode* r2){
    if(r1 == NULL && r2 == NULL)
        return 1;

    if(r1 == NULL || r2 == NULL)
        return 0;

    return r1->data == r2->data
        && isSameTree(r1->left, r2->left)
        && isSameTree(r1->right, r2->right);
}

int isSameStructure(btnode* r1, btnode* r2){
    if(r1 == NULL && r2 == NULL)
        return 1;

    if(r1 == NULL || r2 == NULL)
        return 0;

    return isSameStructure(r1->left, r2->left)
        && isSameStructure(r1->right, r2->right);
}

//
void mirrorTree(btnode* r){
    if(r == NULL) return;

    btnode* temp = r->left;
    r->left = r->right;
    r->right = temp;

    mirrorTree(r->left);
    mirrorTree(r->right);
}
