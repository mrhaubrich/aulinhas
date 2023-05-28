#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  char word[50];
  int count;
  struct Node *next;
  struct Node *prev;
} Node;

#define HASH_SIZE 26

void insertWord(Node **hashList, const char *word) {
  int index = word[0] - 'a';

  Node *current = hashList[index];
  while (current != NULL) {
    if (strcmp(current->word, word) == 0) {
      current->count++;
      return;
    }
    current = current->next;
  }

  Node *newNode = (Node *)malloc(sizeof(Node));
  strcpy(newNode->word, word);
  newNode->count = 1;
  newNode->next = NULL;

  if (hashList[index] == NULL) {
    hashList[index] = newNode;
  } else {
    current = hashList[index];
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = newNode;
  }
}

void printHashList(Node **hashList, int sortOption) {
  // sortOption: 1 - A-Z, 2 - Z-A
  Node *current;
  Node *filteredList = NULL;

  if (sortOption == 1) {
    for (int i = 0; i < HASH_SIZE; i++) {
      Node *current = hashList[i];
      while (current != NULL) {
        printf("%s: %d\n", current->word, current->count);
        current = current->next;
      }
    }
  } else if (sortOption == 2) {
    for (int i = HASH_SIZE - 1; i >= 0; i--) {
      Node *current = hashList[i];
      while (current != NULL) {
        printf("%s: %d\n", current->word, current->count);
        current = current->next;
      }
    }
  } else {
    printf("\nOpção inválida. Voltando ao menu.\n");
    return;
  }
}

void freeHashList(Node **hashList) {
  for (int i = 0; i < HASH_SIZE; i++) {
    Node *current = hashList[i];
    while (current != NULL) {
      Node *next = current->next;
      free(current);
      current = next;
    }
  }
}

void removeWord(Node **hashList, const char *word) {
  int index = word[0] - 'a';

  Node *current = hashList[index];
  while (current != NULL) {
    if (strcmp(current->word, word) == 0) {
      if (current->prev != NULL) {
        current->prev->next = current->next;
      } else {
        hashList[index] = current->next;
      }
      if (current->next != NULL) {
        current->next->prev = current->prev;
      }
      free(current);
      printf("A palavra '%s' foi removida da lista.\n", word);
      return;
    }
    current = current->next;
  }
  printf("A palavra '%s' não foi encontrada na lista.\n", word);
}

// pesquisa pela primeira letra
void searchWordsByLetter(Node **head, char letter, int sortOption) {
  int index = letter - 'a';
  Node *current = head[index];
  Node *filteredList[HASH_SIZE];
  memset(filteredList, 0, sizeof(filteredList));

  while (current != NULL) {
    if (current->word[0] == letter) {
      insertWord(filteredList, current->word);
    }
    current = current->next;
  }

  printf("\nPalavras que iniciam com '%c':\n", letter);
  printHashList(filteredList, sortOption);

  freeHashList(filteredList);
}

void searchWordsByCount(Node **hashList, int count) {
  Node *filteredList[HASH_SIZE];
  memset(filteredList, 0, sizeof(filteredList));

  for (int i = 0; i < HASH_SIZE; i++) {
    Node *current = hashList[i];
    while (current != NULL) {
      if (current->count == count) {
        insertWord(filteredList, current->word);
      }
      current = current->next;
    }
  }

  printf("\nPalavras com %d ocorrência(s):\n", count);
  printHashList(filteredList, 1);

  freeHashList(filteredList);
}

int hashFunction(const char *word) { return word[0] - 'a'; }

void insertWordByCount(Node **head, const char *word, int count) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  int index = hashFunction(word);
  Node *current = head[index];

  strcpy(newNode->word, word);
  newNode->count = count;
  newNode->next = NULL;
  newNode->prev = NULL;

  if (head[index] == NULL) {
    head[index] = newNode;
  } else {
    current = head[index];
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = newNode;
    newNode->prev = current;
  }
}

// Helper function to swap two nodes
void swapNodes(Node **a, Node **b) {
  Node *temp = *a;
  *a = *b;
  *b = temp;
}

// Helper function to sort the filtered list by count using bubble sort
void sortByCount(Node **filteredList) {
  int swapped;
  Node *ptr1 = NULL;
  Node *lptr = NULL;

  if (*filteredList == NULL)
    return;

  do {
    swapped = 0;
    Node *current = *filteredList;

    while (current->next != lptr) {
      if (current->count < current->next->count) {
        swapNodes(&current, &(current->next));
        swapped = 1;
      }
      current = current->next;
    }
    lptr = current;
  } while (swapped);
}

// print the hashed list ordered by number of occurrences
void printOrderedByCount(Node **hashList) {
  Node *current;
  Node *filteredList = NULL;

  for (int i = 0; i < HASH_SIZE; i++) {
    current = hashList[i];
    while (current != NULL) {
      insertWord(&filteredList, current->word);
      current = current->next;
    }
  }

  sortByCount(&filteredList);

  printf(
      "\nPalavras e suas contagens (ordenadas por número de ocorrências):\n");
  printHashList(&filteredList, 1);

  freeHashList(&filteredList);
}

int countHashList(Node **hashList) {
  int count = 0;
  for (int i = 0; i < HASH_SIZE; i++) {
    Node *current = hashList[i];
    while (current != NULL) {
      count++;
      current = current->next;
    }
  }
  return count;
}

int main() {
  Node *hashList[HASH_SIZE];
  memset(hashList, 0, sizeof(hashList));

  Node *head = NULL;

  int option = -1;
  while (option != 0) {
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
          insertWord(hashList, word);
        }
        word = strtok(NULL, " \n");
      }

      printf("\nPalavras e suas contagens:\n");
      printHashList(hashList, 1);
      break;
    }
    case 2: {
      printf("Digite a palavra para consultar: ");
      char word[50];
      scanf("%s", word);

      Node *current = head;
      while (current != NULL) {
        if (strcmp(current->word, word) == 0) {
          printf("A palavra '%s' ocorre %d vez(es).\n", word, current->count);
          break;
        }
        current = current->next;
      }
      if (current == NULL) {
        printf("A palavra '%s' não foi encontrada na lista.\n", word);
      }
      break;
    }
    case 3: {
      printf("Digite a palavra para remover: ");
      char word[50];
      scanf("%s", word);
      removeWord(hashList, word);
      break;
    }
    case 4: {
      int count = countHashList(hashList);
      printf("O número de palavras na lista é: %d\n", count);
      break;
    }
    case 5: {
      int sortOption;
      printf("Digite '1' para ordem A-Z ou '2' para ordem Z-A: ");
      scanf("%d", &sortOption);
      printHashList(hashList, sortOption);
      break;
    }
    case 6: {
      char letter;
      int sortOption;
      printf("Digite a letra para buscar palavras: ");
      scanf(" %c", &letter);
      printf("Digite '1' para ordem A-Z ou '2' para ordem Z-A: ");
      scanf("%d", &sortOption);

      searchWordsByLetter(hashList, letter, sortOption);
      break;
    }
    case 7: {
      printOrderedByCount(hashList);
      break;
    }
    case 8: {
      int count;
      printf("Digite o número de ocorrências: ");
      scanf("%d", &count);

      searchWordsByCount(hashList, count);
      break;
    }
    default:
      printf("Opção inválida. Tente novamente.\n");
      break;
    }
  }

  freeHashList(hashList);

  return 0;
}
