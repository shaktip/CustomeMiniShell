#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* for fork */
#include <sys/types.h> /* for pid_t */
#include <sys/wait.h> /* for wait */
#include <string.h>
#include <malloc.h>

#include  <sys/ipc.h>
#include  <sys/shm.h>


#define BUFFERSIZE 1000
#define DIRSTRINGSIZE 1024

/**
  Note : 
      execv defines a path of application to be executed by a child process and once
      the application of execv is completed the child is automatically terminates its
      application.
      So, it is not possible to assign any work to forked child process after call of
      execv.
      The exec() family of functions replaces the current process image with a new process image.
      
     the strtok runtime function works like this
     the first time you call strtok you provide a string that you want to tokenize
     char s[] = "this is a string";
     in the above string space seems to be a good delimiter between words so lets use that:
     char* p = strtok(s, " ");
     what happens now is that 's' is searched until the space character is found, the first token is       
     returned ('this') and p points to that token (string)

     in order to get next token and to continue with the same string NULL is passed as first argument     
     since strtok maintains a static pointer to your previous passed string:

     p = strtok(NULL," ");

     p now points to 'is'

    and so on until no more spaces can be found, then the last string is returned as the last token 'string'.
*/
int main()
{
    pid_t pid, parent_pid ; 
    char argv[BUFFERSIZE];
    char **argumentsToPass;
    char currentWorkingDir[DIRSTRINGSIZE];
    char *token;
    key_t key = 5678;
    int i, j;
   
     int    ShmID;
     char   *ShmPTR_CWD; 
    
     ShmID = shmget(key, DIRSTRINGSIZE*sizeof(char), IPC_CREAT | 0777);
     if (ShmID < 0) {
          printf("*** shmget error (server) ***\n");
          exit(1);
     }
     ShmPTR_CWD = (char *) shmat(ShmID, NULL, 0);

    parent_pid = getpid();
    //currentWorkingDir = (char *) malloc(1024 * sizeof(char));
    if (getcwd(currentWorkingDir, DIRSTRINGSIZE) == NULL)
        perror("getcwd() error");
    for(i = 0 ; i < strlen(currentWorkingDir); i++)
        ShmPTR_CWD[i] = currentWorkingDir[i];
    ShmPTR_CWD[i] = '\0';
    /*Spawn a child to run the program.*/
    
    while(1)
    {
      //printf("\n%s$ ",ShmPTR_CWD);
      printf("\nMyUser$ ");
      fflush(stdin);  
      if(fgets(argv, BUFFERSIZE , stdin) == NULL)
      {
           printf("Error in accepting input from user\n");
           break;
      }  
      //printf("\n\t int - %d" , argv[0]);
      if(argv[0] == 10)
           continue;
      argv[strlen(argv) - 1] = '\0';

      argumentsToPass = (char **) calloc((strlen(argv) / 2) , sizeof(char *));

      
      token = strtok (argv," ");
      char *appToRun = token;
      
      //for(j=0; j<strlen(appToRun) ; j++)
      //     printf(" %d %c\n" , j, appToRun[j]);
      argumentsToPass[0] = ShmPTR_CWD;

      token = strtok(NULL, " ");
      i = 1; 
      while(token != NULL)
      {
          argumentsToPass[i++] = token;
          token = strtok(NULL, " ");
      }
      if(strcmp(appToRun , "exit") == 0)
          break ;
      //for(j = 0; j < i ;j++)
      //  printf("%s \n",argumentsToPass[j]);

      pid=fork();
      if (pid==0) 
      { 
          // child process 
          if(strcmp(appToRun,"mypwd") == 0)
          {   
              execv("mypwd",argumentsToPass);
              _exit(1);
          }
          else if(strcmp(appToRun , "mymkdir") == 0)
          {
              execv("mymkdir" , argumentsToPass);
              _exit(1);
          }
          else if(strcmp(appToRun , "myls") == 0)
          {
              execv("myls" , argumentsToPass);
              _exit(1);  
          }    
          else if(strcmp(appToRun, "mycd") == 0)
          {
            // printf("Check2 %s \n" , argumentsToPass[1]);
             execv("mycd", argumentsToPass);            
             _exit(1);
          }  
          else if(strcmp(appToRun , "myrm") == 0)
          {
                 execv("myrm", argumentsToPass);
                 _exit(1);
          }
          else if(strcmp(appToRun , "mytail") == 0)
          {
                execv("mytail" , argumentsToPass);
                _exit(1);
          }
          else if(strcmp(appToRun , "mymv") == 0)
          {
               execv("mymv" , argumentsToPass);
               _exit(1);
          }   
          else if(strcmp(appToRun , "myps") == 0)
          {
               execv("myps" , argumentsToPass);
               _exit(1);
          }               
          else
          {
             printf("Invalid Command");
          }
          //exit(127); // only if execv fails 
          //printf("\n\tRunning inside if");
      }
      else
      { 
        // pid!=0; parent process
         waitpid(pid, 0, 0);
      }
            
      free(argumentsToPass);
      if(getpid() == parent_pid)
           continue;
      else
           break;
   
    } 
    //printf("Parent is running\n");
    return 0;
}


