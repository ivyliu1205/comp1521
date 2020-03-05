#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include <assert.h>
#include <ctype.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
   pid_t id;  int stat;
   if ((id = fork()) != 0) {
      printf("A = %d\n", id);
      
      printf("%d\n",wait(&stat));
      printf("%d!!!!!\n", stat);
      return 1;
   }
   else {
      printf("B = %d\n", getppid());
      return 0;
   }
}
