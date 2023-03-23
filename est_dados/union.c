#include <stdio.h>

typedef union n {
  int i;
  float f;
  double d;
} number;

int main() {
  number n;
  n.i = 10;
  printf("n.i = %d\n", n.i);
  n.f = 10.5;
  printf("n.f = %f\n", n.f);
  n.d = 10.5;
  printf("n.d = %f\n", n.d);
  return 0;
}