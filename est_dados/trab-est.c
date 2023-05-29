#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 26

typedef struct Node {
  char palavra[50];
  int quantidade;
  struct Node *prox;
  struct Node *ant;
} Node;

int hashear(const char *palavra) { return palavra[0] - 'a'; }

void inserePalavra(Node **hashList, const char *palavra) {
  int hash = hashear(palavra);

  Node *aux = hashList[hash];
  while (aux != NULL) {
    if (strcmp(aux->palavra, palavra) == 0) {
      aux->quantidade++;
      return;
    }
    aux = aux->prox;
  }

  Node *novo = (Node *)malloc(sizeof(Node));
  strcpy(novo->palavra, palavra);
  novo->quantidade = 1;
  novo->prox = NULL;

  if (hashList[hash] == NULL) {
    hashList[hash] = novo;
  } else {
    aux = hashList[hash];
    while (aux->prox != NULL) {
      aux = aux->prox;
    }
    aux->prox = novo;
  }
}

void printarHashList(Node **hashList, int tipoOrdenacao) {
  Node *aux;
  Node *listaFiltrada = NULL;

  if (tipoOrdenacao == 1) {
    for (int i = 0; i < HASH_SIZE; i++) {
      Node *aux = hashList[i];
      while (aux != NULL) {
        printf("%s: %d\n", aux->palavra, aux->quantidade);
        aux = aux->prox;
      }
    }
  } else if (tipoOrdenacao == 2) {
    for (int i = HASH_SIZE - 1; i >= 0; i--) {
      aux = hashList[i];
      while (aux != NULL) {
        printf("%s: %d\n", aux->palavra, aux->quantidade);
        aux = aux->prox;
      }
    }
  } else {
    printf("\nOpção inválida. Voltando ao menu.\n");
    return;
  }
}

void limparHashList(Node **hashList) {
  for (int i = 0; i < HASH_SIZE; i++) {
    Node *aux = hashList[i];
    while (aux != NULL) {
      Node *next = aux->prox;
      free(aux);
      aux = next;
    }
  }
}

void removePalavra(Node **hashList, const char *palavra) {
  int hash = hashear(palavra);

  Node *aux = hashList[hash];
  while (aux != NULL) {
    if (strcmp(aux->palavra, palavra) == 0) {
      if (aux->ant != NULL) {
        aux->ant->prox = aux->prox;
      } else {
        hashList[hash] = aux->prox;
      }
      if (aux->prox != NULL) {
        aux->prox->ant = aux->ant;
      }
      free(aux);
      printf("A palavra '%s' foi removida da lista.\n", palavra);
      return;
    }
    aux = aux->prox;
  }
  printf("A palavra '%s' não foi encontrada na lista.\n", palavra);
}

void buscarPorLetra(Node **head, char letter, int sortOption) {
  int hash = hashear(&letter);
  Node *aux = head[hash];
  Node *listaFiltrada[HASH_SIZE];
  memset(listaFiltrada, 0, sizeof(listaFiltrada));

  while (aux != NULL) {
    if (aux->palavra[0] == letter) {
      inserePalavra(listaFiltrada, aux->palavra);
    }
    aux = aux->prox;
  }

  printf("\nPalavras que iniciam com '%c':\n", letter);
  printarHashList(listaFiltrada, sortOption);

  limparHashList(listaFiltrada);
}

void buscarPorOcorrencias(Node **hashList, int numeroOcorrencias) {
  Node *listaFiltrada[HASH_SIZE];
  memset(listaFiltrada, 0, sizeof(listaFiltrada));

  for (int i = 0; i < HASH_SIZE; i++) {
    Node *aux = hashList[i];
    while (aux != NULL) {
      if (aux->quantidade == numeroOcorrencias) {
        inserePalavra(listaFiltrada, aux->palavra);
      }
      aux = aux->prox;
    }
  }

  printf("\nPalavras com %d ocorrência(s):\n", numeroOcorrencias);
  printarHashList(listaFiltrada, 1);

  limparHashList(listaFiltrada);
}

void trocar(Node **a, Node **b) {
  Node *temp = *a;
  *a = *b;
  *b = temp;
}

void limparConsole() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}


void insereOrdenado(Node **head, Node *novo) {
  if (*head == NULL) {
    *head = novo;
    return;
  }

  Node *aux = *head;
  Node *ant = NULL;

  while (aux != NULL && aux->quantidade > novo->quantidade) {
    ant = aux;
    aux = aux->prox;
  }

  if (ant == NULL) {
    novo->prox = *head;
    *head = novo;
  } else {
    ant->prox = novo;
    novo->prox = aux;
  }

  return;
}

void ordenarPorQuantidade(Node **listaFiltrada) {
  int trocou;
  Node *ptr1 = NULL;
  Node *lptr = NULL;
  
  Node *aux = NULL;

  for (int i = 0; i < HASH_SIZE; i++) {
    aux = listaFiltrada[i];
    while (aux != NULL) {
      Node *novo = (Node *)malloc(sizeof(Node));
      strcpy(novo->palavra, aux->palavra);
      novo->quantidade = aux->quantidade;
      novo->prox = NULL;
      insereOrdenado(&ptr1, novo);
      aux = aux->prox;
    }
  }

  *listaFiltrada = ptr1;
}

void inserePalavraComQuantidade(Node **hashList, const char *palavra,
                                int quantidade) {
  int hash = hashear(palavra);

  Node *aux = hashList[hash];
  while (aux != NULL) {
    if (strcmp(aux->palavra, palavra) == 0) {
      aux->quantidade += quantidade;
      return;
    }
    aux = aux->prox;
  }

  Node *novo = (Node *)malloc(sizeof(Node));
  strcpy(novo->palavra, palavra);
  novo->quantidade = quantidade;
  novo->prox = NULL;

  if (hashList[hash] == NULL) {
    hashList[hash] = novo;
  } else {
    aux = hashList[hash];
    while (aux->prox != NULL) {
      aux = aux->prox;
    }
    aux->prox = novo;
  }
}

void printarLista(Node *head) {
  Node *aux = head;
  while (aux != NULL) {
    printf("%s: %d\n", aux->palavra, aux->quantidade);
    aux = aux->prox;
  }
}

void printarOrdenadoPorQuantidade(Node **hashList) {
  Node *aux;
  Node *listaFiltrada[HASH_SIZE];
  memset(listaFiltrada, 0, sizeof(listaFiltrada));

  for (int i = 0; i < HASH_SIZE; i++) {
    aux = hashList[i];
    while (aux != NULL) {
      inserePalavraComQuantidade(listaFiltrada, aux->palavra, aux->quantidade);
      aux = aux->prox;
    }
  }

  free(aux);

  aux = NULL;

  ordenarPorQuantidade(&aux);

  printf(
      "\nPalavras e suas contagens (ordenadas por número de ocorrências):\n");
  printarLista(aux);

  free(aux);

  limparHashList(listaFiltrada);
}

int contarHashList(Node **hashList) {
  int count = 0;
  for (int i = 0; i < HASH_SIZE; i++) {
    Node *aux = hashList[i];
    while (aux != NULL) {
      count++;
      aux = aux->prox;
    }
  }
  return count;
}

int contarOcorrencias(Node **hashList, const char *word) {
  int hash = hashear(word);
  Node *aux = hashList[hash];
  while (aux != NULL) {
    if (strcmp(aux->palavra, word) == 0) {
      return aux->quantidade;
    }
    aux = aux->prox;
  }
  return 0;
}

void printMenu() {
  printf("\n----- MENU -----\n");
  printf("0 - Encerrar o programa\n");
  printf("1 - Inserir frase\n");
  printf("2 - Consultar palavra\n");
  printf("3 - Remover palavra\n");
  printf("4 - Contar palavras\n");
  printf("5 - Exibir palavras em ordem alfabética\n");
  printf("6 - Buscar palavras que iniciam com uma letra\n");
  printf("7 - Exibir palavras em ordem de número de ocorrências\n");
  printf("8 - Exibir palavras com um determinado número de ocorrências\n");
  printf("Digite a opção desejada: ");
}

int main() {
  Node *hashList[HASH_SIZE];
  memset(hashList, 0, sizeof(hashList));

  Node *head = NULL;

  int option = -1;
  while (option != 0) {
    limparConsole();
    printMenu();
    scanf("%d", &option);
    getchar();

    switch (option) {
    case 0:
      printf("Encerrando o programa.\n");
      break;
    case 1: {
      printf("Digite uma frase: ");
      char text[1000];
      fgets(text, sizeof(text), stdin);

      char *word = strtok(text, " \n");
      while (word != NULL) {
        if (isalpha(word[0])) {
          word[0] = tolower(word[0]);
          inserePalavra(hashList, word);
        }
        word = strtok(NULL, " \n");
      }

      limparConsole();
      printf("\nPalavras e suas contagens:\n");
      printarHashList(hashList, 1);
      printf("Pressione ENTER para continuar...");
      getchar();
      break;
    }
    case 2: {
      printf("Digite a palavra para consultar: ");
      char word[50];
      scanf("%s", word);

      int wordCount = contarOcorrencias(hashList, word);


      if (wordCount == 0) {
        printf("A palavra '%s' não foi encontrada.\n", word);
      } else if (wordCount == 1) {
        printf("A palavra '%s' ocorre %d vez.\n", word, wordCount);
      } else {
        printf("A palavra '%s' ocorre %d vezes.\n", word, wordCount);
      }

      printf("Pressione ENTER para continuar...");
      getchar();
      getchar();
      break;
    }
    case 3: {
      printf("Digite a palavra para remover: ");
      char word[50];
      scanf("%s", word);
      limparConsole();
      removePalavra(hashList, word);
      printf("Pressione ENTER para continuar...");
      getchar();
      getchar();
      break;
    }
    case 4: {
      int count = contarHashList(hashList);
      limparConsole();
      printf("O número de palavras na lista é: %d\n", count);
      printf("Pressione ENTER para continuar...");
      getchar();
      break;
    }
    case 5: {
      int sortOption;
      printf("Digite '1' para ordem A-Z ou '2' para ordem Z-A: ");
      scanf("%d", &sortOption);
      limparConsole();
      printarHashList(hashList, sortOption);
      printf("Pressione ENTER para continuar...");
      getchar();
      getchar();
      break;
    }
    case 6: {
      char letter;
      int sortOption;
      printf("Digite a letra para buscar palavras: ");
      scanf(" %c", &letter);
      printf("Digite '1' para ordem A-Z ou '2' para ordem Z-A: ");
      scanf("%d", &sortOption);

      limparConsole();
      buscarPorLetra(hashList, letter, sortOption);
      printf("Pressione ENTER para continuar...");
      getchar();
      getchar();
      break;
    }
    case 7: {
      limparConsole();
      printarOrdenadoPorQuantidade(hashList);
      printf("Pressione ENTER para continuar...");
      getchar();
      break;
    }
    case 8: {
      int count;
      printf("Digite o número de ocorrências: ");
      scanf("%d", &count);

      limparConsole();
      buscarPorOcorrencias(hashList, count);
      printf("Pressione ENTER para continuar...");
      getchar();
      getchar();
      break;
    }
    default:
      printf("Opção inválida. Tente novamente.\n");
      break;
    }
  }

  limparHashList(hashList);

  return 0;
}
