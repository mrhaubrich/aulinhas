#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

/// @brief Estrutura de um nó de árvore binária
typedef struct Node {
  int valor;
  int operacao;
  int altura;
  struct Node *esquerda, *direita;
} Node;

/// @brief Cria um novo nó
/// @param valor valor do nó
/// @return Node* - ponteiro para o nó criado
Node *newNode(int valor) {
  Node *temp = (Node *)malloc(sizeof(Node));
  temp->valor = valor;
  temp->esquerda = temp->direita = NULL;
  return temp;
}

/// @brief AVL
Node *RAIZ = NULL;

/// @brief Funcão auxiliar para imprimir a árvore
/// @param node nó da árvore
/// @param isLeft indica se o nó é filho esquerdo
void printBT(char *prefix, const Node *node, int isLeft) {
  if (node != NULL) {
    printf("%s", prefix);

    printf("%s", (isLeft == 1 ? "├──" : "└──"));

    printf("%d", node->valor);
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

/// @brief Imprime a árvore
/// @param node nó da árvore
void printTree(Node *node) { printBT("", node, 0); }

/// @brief Retorna a altura da árvore
/// @param node nó da árvore
/// @return int - altura da árvore
int altura(Node *node) {
  if (node == NULL)
    return 0;
  return 1 + altura(node->esquerda) + altura(node->direita);
}

/// @brief Retorna o fator de balanceamento da árvore
/// @param node nó da árvore
/// @return int - fator de balanceamento da árvore
int fatorBalanceamento(Node *node) {
  if (node == NULL)
    return 0;
  return altura(node->esquerda) - altura(node->direita);
}

/// @brief Retorna o maior valor entre dois inteiros
/// @param a primeiro valor
/// @param b segundo valor
/// @return int - maior valor
int max(int a, int b) { return (a > b) ? a : b; }

/// @brief Rotaciona a subárvore para a esquerda
/// @param node nó da árvore
/// @return Node* - nova raiz da subárvore
Node *rotacaoEsquerda(Node *node, int verbose) {
  Node *y = node->direita;
  Node *T2 = y->esquerda;

  if (verbose == 1) {
    node->operacao = 1;
    system("clear");
    printf("Rotacao Esquerda\n");
    printTree(RAIZ);
    sleep(1);
  }
  // Realiza a rotação
  y->esquerda = node;
  node->direita = T2;

  // Retorna a nova raiz
  return y;
}

/// @brief Rotaciona a subárvore para a direita
/// @param node nó da árvore
/// @return Node* - nova raiz da subárvore
Node *rotacaoDireita(Node *node, int verbose) {
  Node *x = node->esquerda;
  Node *T2 = x->direita;

  if (verbose == 1) {
    node->operacao = 1;
    system("clear");
    printf("Rotacao Direita\n");
    printTree(RAIZ);
    sleep(1);
  }

  // Realiza a rotação
  x->direita = node;
  node->esquerda = T2;

  // Retorna a nova raiz
  return x;
}

/// @brief Insere um novo nó na árvore
/// @param node nó da árvore
/// @param valor valor do nó
/// @return Node* - nova raiz da árvore
Node *inserir(Node *node, int valor, int verbose) {
  // Realiza a inserção normalmente
  if (node == NULL)
    return (newNode(valor));

  if (verbose == 1) {
    node->operacao = 1;
    // wait 1 secont
    sleep(1);
    system("clear");
    // clear console
    printTree(RAIZ);
  }

  if (valor < node->valor) {
    node->esquerda = inserir(node->esquerda, valor, verbose);
  } else if (valor > node->valor) {
    node->direita = inserir(node->direita, valor, verbose);
  } else {
    return node;
  }

  // Atualiza a altura do nó
  node->altura = 1 + max(altura(node->esquerda), altura(node->direita));

  // Calcula o fator de balanceamento do nó
  int balance = fatorBalanceamento(node);

  // Se o nó estiver desbalanceado, existem 4 casos

  // Caso esquerda-esquerda
  if (balance > 1 && valor < node->esquerda->valor) {
    return rotacaoDireita(node, verbose);
  }

  // Caso direita-direita
  if (balance < -1 && valor > node->direita->valor) {
    return rotacaoEsquerda(node, verbose);
  }

  // Caso esquerda-direita
  if (balance > 1 && valor > node->esquerda->valor) {
    node->esquerda = rotacaoEsquerda(node->esquerda, verbose);
    return rotacaoDireita(node, verbose);
  }

  // Caso direita-esquerda
  if (balance < -1 && valor < node->direita->valor) {
    node->direita = rotacaoDireita(node->direita, verbose);
    return rotacaoEsquerda(node, verbose);
  }

  node->operacao = 0;

  // Retorna o ponteiro para o nó
  return node;
}

/// @brief Gera um inteiro aleatório
/// @param min valor mínimo
/// @param max valor máximo
/// @return int - inteiro aleatório
int randomInt(int min, int max) { return min + rand() % (max - min); }

/// @brief Função principal
int main() {
  int opcao = 0;
  int valor = 0;
  int i = 0;
  int n = 0;
  int *valores = NULL;

  printf("Digite a quantidade de valores: ");
  scanf("%d", &n);

  valores = (int *)malloc(sizeof(int) * n);

  srand(time(NULL));

  for (i = 0; i < n; i++) {
    valores[i] = randomInt(1, 100);
  }

  for (i = 0; i < n; i++) {
    printf("Inserindo %d\n", valores[i]);
    RAIZ = inserir(RAIZ, valores[i], 0);
  }

//   system("clear");
  printf("Arvore AVL\n");
  printTree(RAIZ);

  printf("\n\n");

  // altura
  printf("Altura: %d\n", altura(RAIZ));

  // fator de balanceamento
  printf("Fator de Balanceamento: %d\n", fatorBalanceamento(RAIZ));

  return 0;
}
