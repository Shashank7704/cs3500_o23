#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int main() {
  char buffer[BUFFER_SIZE];
  char *args[BUFFER_SIZE];

  while (1) {
    // Display the command prompt
    printf("prompt> ");

    // Read the user input
    fgets(buffer, BUFFER_SIZE, stdin);

    // Check if the user entered exit
    if (strcmp(buffer, "exit") == 0) {
      break;
    }

    // Tokenize the user input into arguments
    char *delim = " ";
    char *token = strtok(buffer, delim);
    int i = 0;
    while (token != NULL) {
      args[i++] = token;
      token = strtok(NULL, delim);
    }

    // Spawn a new process to execute the command
    pid_t child = fork();
    if (child == 0) {
      execlp(args[0], args[0], NULL);
      perror("execlp");
      exit(1);
    } else if (child > 0) {
      // Wait for the child process to finish
      int status;
      waitpid(child, &status, 0);
    } else {
      perror("fork");
      exit(1);
    }
  }

  return 0;
}
