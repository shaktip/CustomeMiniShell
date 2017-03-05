#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main(int c , char *argv[]) {
  /*
   char cwd[1024];
   if (getcwd(cwd, sizeof(cwd)) != NULL)
       fprintf(stdout, "Current working dir: %s\n", cwd);
   else
       perror("getcwd() error");
   */
   if(c != 1)
   { 
      printf("Invalid number of arguments \n");
      return -1;
   }
   printf("Current Directory is : %s\n" , argv[0]);
   return 0;
}
