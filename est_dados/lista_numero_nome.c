// - implementar uma lista de 10 elementos através de um vetor (array) de
// tamanho 10. Cada elemento é composto de número e nome (usar struct para
// definir o elemento em C, em Java usar classe).
// - implementar a operação para inverter a lista (não apenas escrever
// invertido) .

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da struct
typedef struct n {
  int i;
  char nome[20];
} number;

// Função para inverter a lista
// - n: lista de números
// - tam: tamanho da lista
void inverter(number *n, int tam) {
  int i;
  number *aux = (number *)malloc(tam * sizeof(number));
  for (i = 0; i < tam; i++) {
    aux[i].i = n[tam - i - 1].i;
    strcpy(aux[i].nome, n[tam - i - 1].nome);
  }
  for (i = 0; i < tam; i++) {
    n[i].i = aux[i].i;
    strcpy(n[i].nome, aux[i].nome);
  }
  free(aux);
}

int main() {
  number n[10];
  int i;
  for (i = 0; i < 10; i++) {
    n[i].i = i;
    sprintf(n[i].nome, "nome %d", i);
  }
  for (i = 0; i < 10; i++) {
    printf("n[%d].i = %d\n", i, n[i].i);
    printf("n[%d].nome = %s\n", i, n[i].nome);
  }

  printf("---------------------- Invertendo lista de 10 elementos "
         "------------------");

  inverter(n, 10);

  for (i = 0; i < 10; i++) {
    printf("n[%d].i = %d\n", i, n[i].i);
    printf("n[%d].nome = %s\n", i, n[i].nome);
  }

  return 0;
}