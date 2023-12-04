#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
  int a, b;
  a = atoi(argv[1]);
  b = atoi(argv[2]);

  // Create two child processes
  pid_t child1 = fork();
  if (child1 == -1) {
    perror("fork");
    exit(1);
  }

  // Child 1
  if (child1 == 0) {
    char *args[] = {"./child1", argv[1], argv[2], NULL};
    execvp(args[0], args);
    perror("execvp");
    exit(1);
  }

  // Child 2
  else 
  {
    pid_t child2 = fork();
    if (child2 == -1) {
        perror("fork");
        exit(1);
    }
    if(child2 == 0)
    {
        char *args[] = {"./child2", argv[1], argv[2], NULL};
        execvp(args[0], args);
        perror("execvp");
        exit(1);
    }
    else
    {
        wait(NULL);
        wait(NULL);
    }
  }
  printf("Parent exiting\n");
  return 0;
}
