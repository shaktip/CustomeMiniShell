#include<stdio.h>
#include<string.h>

#include<dirent.h>
#include<sys/stat.h>
#include<sys/types.h>



int main(int argc, char *argv[])
{
   if(argc != 3)
   {
        printf("Please supply correct no of arguments");
        return;
   } 
   char p1[1024];
   char p2[1024];
   //char cwd[1024];
   //getcwd(cwd, sizeof(cwd));
   
   char newfile[1000];

   if(argv[1][0] == '/')
      strcpy(p1, argv[1]);
   else
   {
      strcpy(p1, argv[0]);
      strcat(p1 , "/");
      strcat(p1, argv[1]);
   }
   
   if(argv[2][0] == '/')
   {
      strcpy(p2 , argv[2]);
      strcpy(newfile, p2);
      strcat(p2, "/");            
      strcat(p2 , argv[1]);
      
   }
   else
   { 
      strcpy(p2, argv[0]);
      strcat(p2, "/");
      strcat(p2, argv[2]);
      strcpy(newfile, p2);
      strcat(p2, "/");
      strcat(p2 , argv[1]);
   }
 
   DIR *dir;
   dir = opendir(newfile);
   if(dir != NULL)
   {
         closedir(dir);
         //printf("First File Path : %s\n",p1);
         //printf("Second File Path : %s\n",p2);
         rename(p1, p2);
   }
   else
   {
          closedir(dir);
          //printf("First File Path : %s\n",p1);
          //printf("Second File Path : %s\n",newfile);
          rename(p1, newfile);
   }
      
   return 0;  
}
