#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// A node of binary tree
typedef struct Node {
  int data;
  int operacao;
  struct Node *esquerda, *direita;
} Node;

// A utility function to create a new Binary Tree node
Node *newNode(int data) {
  Node *temp = (Node *)malloc(sizeof(Node));
  temp->data = data;
  temp->esquerda = temp->direita = NULL;
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

  // Recur for esquerda and direita subtrees
  findMinMax(node->esquerda, min, max, hd - 1);
  findMinMax(node->direita, min, max, hd + 1);
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

    printBT(newPrefix, node->esquerda, 1);
    printBT(newPrefix, node->direita, 0);
  }
}

void printTree(Node *node) { printBT("", node, 0); }

Node *MAIN_ROOT = NULL;
// function to sort the tree in descending order
void invertTree(Node *root, int verbose) {
  if (root == NULL)
    return;
  if (verbose == 1) {
    root->operacao = 1;
    // wait 1 secont
    sleep(1);
    system("clear");
    // clear console
    printBT("", MAIN_ROOT, 0);
  }

  // recursively traverse the tree in postorder fashion
  invertTree(root->esquerda, verbose);
  invertTree(root->direita, verbose);

  // swap the data of the node with the direita most node
  if (root->esquerda && root->direita) {
    Node *temp = root->esquerda;
    root->esquerda = root->direita;
    root->direita = temp;
  }
  root->operacao = 0;
}

void adicionarOrdenado(Node *root, int data) {
  if (root == NULL) {
    root = newNode(data);
    return;
  }
  // root->operacao = 1;
  sleep(1);
  system("clear");

  printBT("", MAIN_ROOT, 0);

  if (data < root->data) {
    if (root->esquerda == NULL) {
      root->esquerda = newNode(data);
      return;
    } else {
      adicionarOrdenado(root->esquerda, data);
    }
  } else {
    if (root->direita == NULL) {
      root->direita = newNode(data);
      return;
    } else {
      adicionarOrdenado(root->direita, data);
    }
  }
  // root->operacao = 0;
}

// Driver program to test above functions
int main() {
  // MAIN_ROOT = (Node *)malloc(sizeof(Node));
  // Create binary tree shown in above figure
  // MAIN_ROOT->esquerda = newNode(2);
  // MAIN_ROOT->direita = newNode(3);
  // MAIN_ROOT->esquerda->esquerda = newNode(4);
  // MAIN_ROOT->esquerda->direita = newNode(5);
  // MAIN_ROOT->direita->esquerda = newNode(6);
  // MAIN_ROOT->direita->direita = newNode(7);
  // MAIN_ROOT->direita->esquerda->direita = newNode(10);
  // MAIN_ROOT->direita->direita->direita = newNode(9);
  // MAIN_ROOT->direita->direita->esquerda = newNode(8);

  // array de numeros
  int numeros[] = {5, 3, 7, 2, 4, 6, 8, 1, 9, 10};

  // adicionar os numeros na arvore
  for (int i = 0; i < 10; i++) {
    adicionarOrdenado(MAIN_ROOT, numeros[i]);
  }

  system("clear");
  printTree(MAIN_ROOT);
  sleep(2);

  invertTree(MAIN_ROOT, 0);
  system("clear");
  printTree(MAIN_ROOT);

  return 0;
}
