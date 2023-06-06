#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// A node of binary tree
typedef struct Node {
  int data;
  int operacao;
  struct Node *left, *right;
} Node;

// A utility function to create a new Binary Tree node
Node *newNode(int data) {
  Node *temp = (Node *)malloc(sizeof(Node));
  temp->data = data;
  temp->left = temp->right = NULL;
  return temp;
}

// A utility function to find min and max distances with respect
// to root.
void findMinMax(Node *node, int *min, int *max, int hd) {
  // Base case
  if (node == NULL)
    return;

  // Update min and max
  if (hd < *min)
    *min = hd;
  else if (hd > *max)
    *max = hd;

  // Recur for left and right subtrees
  findMinMax(node->left, min, max, hd - 1);
  findMinMax(node->right, min, max, hd + 1);
}

void printBT(char *prefix, const Node *node, int isLeft) {
  if (node != NULL) {
    printf("%s", prefix);

    printf("%s", (isLeft == 1 ? "├──" : "└──"));

    printf("%d", node->data);
    if (node->operacao == 1) {
        printf("<----");
    }
    printf("\n");

    char newPrefix[255];
    strcpy(newPrefix, prefix);
    strcat(newPrefix, (isLeft == 1 ? "|   " : "    "));

    printBT(newPrefix, node->left, 1);
    printBT(newPrefix, node->right, 0);
  }
}

void printTree(Node *node) { printBT("", node, 0); }

Node* MAIN_ROOT;
// function to sort the tree in descending order
void invertTree(Node *root) {
  if (root == NULL)
    return;

  root->operacao = 1;
  // wait 1 secont
  sleep(1);
  system("clear");
  // clear console
  printBT("", MAIN_ROOT, 0);

  // recursively traverse the tree in postorder fashion
  invertTree(root->left);
  invertTree(root->right);

  // swap the data of the node with the right most node
  if (root->left && root->right) {
    Node *temp = root->left;
    root->left = root->right;
    root->right = temp;
  }
  root->operacao = 0;
}


// Driver program to test above functions
int main() {
  MAIN_ROOT = newNode(1);
  // Create binary tree shown in above figure
  MAIN_ROOT->left = newNode(2);
  MAIN_ROOT->right = newNode(3);
  MAIN_ROOT->left->left = newNode(4);
  MAIN_ROOT->left->right = newNode(5);
  MAIN_ROOT->right->left = newNode(6);
  MAIN_ROOT->right->right = newNode(7);
  MAIN_ROOT->right->left->right = newNode(10);
  MAIN_ROOT->right->right->right = newNode(9);
  MAIN_ROOT->right->right->left = newNode(8);

  system("clear");
  printTree(MAIN_ROOT);
  sleep(2);

  invertTree(MAIN_ROOT);
  system("clear");
  printTree(MAIN_ROOT);

  return 0;
}
