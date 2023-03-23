// Nomes: Marco Haubrich e Santiago Fae

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int contains(int baralho[], int carta) {
  for (int i = 0; i < 9; i++) {
    if (baralho[i] == carta) {
      return 1;
    }
  }
  return 0;
}

void remove_carta(int baralho[], int carta) {
  for (int i = 0; i < 9; i++) {
    if (baralho[i] == carta) {
      baralho[i] = -1;
    }
  }
}

int get_carta(int baralho[]) {
  int carta_idx = 0;

  int carta = -1;

  while (carta == -1 || contains(baralho, carta) == 0) {
    carta_idx = rand() % 13;
    carta = baralho[carta_idx];
  }

  baralho[carta_idx] = -1;
  return carta;
}

void inserir_ordenado(int mao[], int carta) {
    // insertion sort
    int i = 0;
    while (mao[i] != 0 && mao[i] < carta) {
        i++;
    }

    int j = 8;
    while (j > i) {
        mao[j] = mao[j - 1];
        j--;
    }

    mao[i] = carta;
}

void mostrar_mao(int mao[]) {
  for (int i = 0; i < 9; i++) {
    printf("%d\t", mao[i]);
  }
  printf("\n");
}

void mostrar_mao_invertida(int mao[]) {
  for (int i = 8; i >= 0; i--) {
    printf("%d\t", mao[i]);
  }
  printf("\n");
}

void mostra_baralho(int baralho[]) {
  for (int i = 0; i < 13; i++) {
    printf("%d\t", baralho[i]);
  }
  printf("\n");
}

int main() {
  int baralho[13];
  int mao[9] = {0};

  for (int i = 0; i < 13; i++) {
    baralho[i] = i + 1;
  }

  mostra_baralho(baralho);

  for (int i = 0; i < 9; i++) {
    inserir_ordenado(mao, get_carta(baralho));
  }

  mostrar_mao(mao);

  mostra_baralho(baralho);


  mostrar_mao_invertida(mao);

  return 0;
}