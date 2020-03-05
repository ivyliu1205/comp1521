#include <stdio.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;
    pid = fork();
    if (pid < 0)
        perror("fork() failed");
    else if (pid != 0)
        printf("I am the parent\n");
    else
        printf("I am the child\n");
    return 0;
}
















