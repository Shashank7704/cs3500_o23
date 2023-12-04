#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int a = atoi(argv[1]);
  int b = atoi(argv[2]);

  int result = a * a - 2 * a * b + b * b;

  printf("Child 1: %d, %d\n", getpid(), result);

  return 0;
}
