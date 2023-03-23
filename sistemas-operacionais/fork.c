#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/*
                pai
               / | \
              /  |  \
            f1  f2  f3
                 |
                f4
*/

// function to create a tree of processes
void createTree() {
    int pid1 = fork();
    if (pid1 > 0) {
        printf("0 created child 1\n");
        int pid2 = fork();
        if (pid2 > 0) {
            printf("0 created child 2\n");
            int pid3 = fork();
            if (pid3 > 0) {
                printf("0 created child 3\n");
            }
        }
        else if (pid2 == 0) {
            int pid4 = fork();
            if (pid4 > 0) {
                printf("2 created child 4\n");
            }
        }
    }
}

int main() {
    createTree();
    sleep(20);
    return 0;
}