#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int a = atoi(argv[1]);
  int b = atoi(argv[2]);

  int result = (a - b) * (a - b);

  printf("Child 2: %d, %d\n", getpid(), result);

  return 0;
}
