#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>

int perfeito(int n) {
    int i, soma = 0;
    for (i = 1; i < n; i++) {
        if (n % i == 0) {
            soma += i;
        }
    }
    return soma == n;
}

void escrevePerfeitos(int n) {
    int i;
    for (i = 1; i <= n; i++) {
        if (perfeito(i)) {
            printf("%d eh perfeito\n", i);
        }
    }
}

void escrevePerfeitosRange(int inicio, int fim, int np) {
    int i;
    for (i = inicio; i <= fim; i += np) {
        if (perfeito(i)) {
            printf("%d eh perfeito\n", i);
        }
    }
}

void divideEmProcessos(int n, int np) {
    int i;
    for (i = 0; i < np; i++) {
        int pid = fork();
        if (pid == 0) {
            escrevePerfeitosRange(i + 1, n, np);
            exit(0);
        }
    }
    for (i = 0; i < np; i++) {
        if (i == 0) {
            wait(NULL);
        }
    }

}

int main(int argc, char const *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <n> <np>\n", argv[0]);
        exit(1);
    }

    int n = atoi(argv[1]);
    int np = atoi(argv[2]);
    divideEmProcessos(n, np);

    return 0;
}

// PROCESSOS LIMITAM NO NUMERO DE CORES FISICOS
// THREADS LIMITAM NO NUMERO DE CORES LOGICOS 