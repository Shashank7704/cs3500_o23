#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("invalid input\n");
        return 0;
    }
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    int pid1 = fork();
    if(pid1 == 0)
    {
        int ans = a*a - b*b;
        printf("Child 1: %d, %d\n", getpid(), ans);
    }
    else
    {
        int pid2 = fork();
        if(pid2 == 0)
        {
            int ans = (a+b)*(a-b);
            printf("Child 2: %d, %d\n", getpid(), ans);
        }
        else
        {
            wait(NULL);
            wait(NULL);
            printf("Parent exiting\n");
        }
    }
}