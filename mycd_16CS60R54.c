#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>

#define DIRSTRINGLENGTH 1024

void main(int c, char *argv[])
{
    //printf("Inside child %s  %s", argv[0],argv[1]);
    int i;
    int shmid;
    key_t key = 5678;
    char *shm, *s;
    int j;
    char *name , *token , *newDir , **all_tokens;

    all_tokens = (char **) malloc(strlen(argv[0]) * sizeof(char *));
    name = (char *) malloc(strlen(argv[0]) * sizeof(char));
    newDir = (char *) malloc(strlen(argv[0]) * sizeof(char));
    newDir[0] = '\0';
    char *temp;
    strcpy(name , argv[0]);
    
    //printf("Check1 \n");
    if(c != 2)
    {
      printf("*************** Invalid number of arguments\n");
      return ;
    }
    char ptr[1024];
    if(argv[1][0] != '/')
    {
       strcpy(ptr, argv[0]);
       strcat(ptr, "/");
       strcat(ptr, argv[1]);
    }
    else
       strcpy(ptr , argv[1]);

    //printf("%s %s",ptr, argv[1]);
    DIR* directory = opendir(ptr);
    
    if (directory)
    {
      /* Directory exists. */
      //   printf("Directory exists\n");
         //fflush(stdout);     
         closedir(directory);
         if((shmid = shmget(key, DIRSTRINGLENGTH * sizeof(char), 0777)) < 0)
         {
                 perror("shmget");
                 return;
         }     
         if((shm = shmat(shmid, NULL , 0)) == (char *) -1)
         {
               perror("shmat");
               return;
         }
         if(strcmp(argv[1], "..") == 0)
         {
         
              //printf("Check2sdf\n");
              token = strtok (name,"/");     
              i = 0;
              while(token != NULL)
              {
                   
                   all_tokens[i] = token;
                   //token = strtok(NULL, " ");
                   //printf("%d Token : %s " , i, token);
                   i++;
                   token = strtok(NULL, "/");
              }
              for(j = 0; j<i - 1; j++)
              {
                   strcat(newDir , "/");
                   strcat(newDir , all_tokens[j]);
              } 
              if(j == 0)
                strcpy(newDir , "/");       
              strcpy(shm, newDir);

         }
         else if(strcmp(argv[1] , ".") == 0)
              return; 
         else
         {   
           if( argv[1][0]  != '/')
           {  
             for(j= 0; shm[j] != '\0'; j++);
             if(shm[j-1] != '/')
                 strcat(shm, "/");
             strcat(shm, argv[1]);
           }
           else
             strcpy(shm, argv[1]);
         }
        // printf(" Inside child process :  %s\n",shm);      
    }
    else
    {
       /* Directory does not exist. */
       printf("Directory does not exist or no permissions to read\n");
       return;
    }
    return;
    
    
}
