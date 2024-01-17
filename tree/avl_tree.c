#include <stdio.h>
#include <stdlib.h>

typedef int datatype;

typedef struct avlNode{
    datatype data;
    struct avlNode* left;
    struct avlNode* right;
    int height;
}avlNode;

// Calculate height
int height(avlNode *p) {
  if (p == NULL){
    return 0;
  }
  return p->height;
}

int max(int a, int b) {
  return (a > b) ? a : b;
}

// Create a node
avlNode* make_avlNode(datatype x) {
  avlNode* node = (avlNode*) malloc(sizeof(avlNode));
  node->data = x;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  return node;
}

// Right rotate
avlNode* rightRotate(avlNode* y) {
  avlNode* x = y->left;
  avlNode* T2 = x->right;

  x->right = y;
  y->left = T2;

  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;

  return x;
}

// Left rotate
avlNode* leftRotate(avlNode* x) {
  avlNode* y = x->right;
  avlNode* T2 = y->left;

  y->left = x;
  x->right = T2;

  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;

  return y;
}

// Get the balance factor
int getBalance(avlNode* N) {
  if (N == NULL)
    return 0;
  return height(N->left) - height(N->right);
}

// Insert node
avlNode* insertNode(avlNode* node, int data) {
  // Find the correct position to insertNode the node and insertNode it
  if (node == NULL)
    return (newNode(data));

  if (data < node->data)
    node->left = insertNode(node->left, data);
  else if (data > node->data)
    node->right = insertNode(node->right, data);
  else
    return node;

  // Update the balance factor of each node and
  // Balance the tree
  node->height = 1 + max(height(node->left),
               height(node->right));

  int balance = getBalance(node);
  if (balance > 1 && data < node->left->data)
    return rightRotate(node);

  if (balance < -1 && data > node->right->data)
    return leftRotate(node);

  if (balance > 1 && data > node->left->data) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }

  if (balance < -1 && data < node->right->data) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  return node;
}

avlNode* minValueNode(avlNode* node) {
  avlNode* current = node;

  while (current->left != NULL)
    current = current->left;

  return current;
}

// Delete a nodes
avlNode* deleteNode(avlNode* root, int data) {
  // Find the node and delete it
  if (root == NULL)
    return root;

  if (data < root->data)
    root->left = deleteNode(root->left, data);

  else if (data > root->data)
    root->right = deleteNode(root->right, data);

  else {
    if ((root->left == NULL) || (root->right == NULL)) {
      avlNode* temp = root->left ? root->left : root->right;

      if (temp == NULL) {
        temp = root;
        root = NULL;
      } else
        *root = *temp;
      free(temp);
    } else {
      avlNode* temp = minValueNode(root->right);

      root->data = temp->data;

      root->right = deleteNode(root->right, temp->data);
    }
  }

  if (root == NULL)
    return root;

  // Update the balance factor of each node and
  // balance the tree
  root->height = 1 + max(height(root->left),
               height(root->right));

  int balance = getBalance(root);
  if (balance > 1 && getBalance(root->left) >= 0)
    return rightRotate(root);

  if (balance > 1 && getBalance(root->left) < 0) {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }

  if (balance < -1 && getBalance(root->right) <= 0)
    return leftRotate(root);

  if (balance < -1 && getBalance(root->right) > 0) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }

  return root;
}