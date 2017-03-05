#include<stdio.h>
#include<dirent.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<time.h>
#include<pwd.h>
#include<malloc.h>
#include<string.h>

#ifdef HAVE_ST_BIRTHTIME
#define birthtime(x) x.st_birthtime
#else
#define birthtime(x) x.st_ctime
#endif

struct Display
{
     char perm[12];
     char no_of_links[10];
     char user_id[100];
     char gr_id[100];
     char f_size[20];
     char bdate[20];
     char fname[30];
  
};

void main(int c, char *agv[])
{
   if( c != 1) 
   {
       printf("Invalid number of arguments");
       return ;
   }
     
   DIR *dir;
   size_t i;
   struct dirent *ent;
   struct stat fileStat; 
   char buffer[100];
   struct passwd *getDetails;
   
   char cwd[1024];
   getcwd(cwd, sizeof(cwd));
   
   int n = 0;
   int index = 0;
   //printf(" argv[0] is %s \n",agv[0]);
   
   if((dir = opendir(agv[0])) != NULL)
   {
      while((ent = readdir(dir)) != NULL)
      {
         n++;
      }
      closedir(dir);
   }
   //printf(" No of files %d \n",n);
   struct Display **d = (struct Display **)malloc(n * sizeof(struct Display *));
   for(i = 0; i<n; i++)
      d[i] = (struct Display *) malloc(sizeof(struct Display));

   if((dir = opendir(agv[0])) != NULL)
   {
     // printf("Check1 \n");
      while((ent = readdir(dir)) != NULL)
      {
        //printf("Check2 \n");
        if(!strcmp(ent->d_name , "."))
        {
           printf("\n.");
           continue;
        }   
        
        if(!strcmp(ent->d_name , ".."))
        {
            printf("\n..");
            continue;
        }
        stat(ent->d_name,&fileStat);
                     
        //printf("Check3 \n");         

    	strcpy(d[index]->perm,  (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    	strcat(d[index]->perm, (fileStat.st_mode & S_IRUSR) ? "r" : "-");
    	strcat(d[index]->perm, (fileStat.st_mode & S_IWUSR) ? "w" : "-");
    	strcat(d[index]->perm, (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    	strcat(d[index]->perm, (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    	strcat(d[index]->perm, (fileStat.st_mode & S_IWGRP) ? "w" : "-");
    	strcat(d[index]->perm, (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    	strcat(d[index]->perm, (fileStat.st_mode & S_IROTH) ? "r" : "-");
        strcat(d[index]->perm, (fileStat.st_mode & S_IWOTH) ? "w" : "-");
        strcat(d[index]->perm, (fileStat.st_mode & S_IXOTH) ? "x" : "-");
        //snprintf(buffer , 4, " %d ",(int)fileStat.st_nlink);
        //printf("Check4 \n"); 
        sprintf(d[index]->no_of_links , "%d" , (int)fileStat.st_nlink);
        snprintf(buffer , 7 , " %d ",(int)fileStat.st_size);
        //printf("Check5 \n");
//getpwuid(fileStat.st_uid); getpwuid(fileStat.st_gid);  
        //printf("%d", fileStat.st_uid); 
        if(strcmp(agv[0] , cwd) == 0)
        {       
    	  getDetails = getpwuid(fileStat.st_uid);
    	 //printf(" Checking ");
    	//printf("Size of uer_id is %d",strlen(getDetails->pw_name));
    	 //printf(" what %s", getDetails->pw_name);
    	  if(getDetails != NULL)
             sprintf(d[index]->user_id ,"%s", getDetails->pw_name);
          else
             sprintf(d[index]->user_id , "%s", "");
          getDetails = getpwuid(fileStat.st_gid);
    	  if(getDetails != NULL)
              sprintf(d[index]->gr_id , " %s ", getDetails->pw_name);      
         }    
         else
         {
            //printf("Check6 _ 1 \n");
             sprintf(d[index]->user_id , "%s", "");
        //printf("Check6 \n");
    	
         
             sprintf(d[index]->gr_id , "%s", "");
         }    
        //printf("Check7 \n");


        sprintf(d[index]->f_size ,"%ld",(long)fileStat.st_size);
        //printf("Check8 \n"); 
        char date[20];
       /*    
        char monthno[4];  
        strftime(monthno , 4 ,"%m", localtime(&(fileStat.st_ctime)));
        sscanf(monthno , "%d" , mno);
        */
        strftime(date, 20, "%b %d %y %H:%M", localtime(&(fileStat.st_ctime)));
        //printf("Check8 \n");
        sprintf(d[index]->bdate , "%s",date);
        //printf("Check9 \n"); 
        //printf("File ino de: %5d",fileStat.st_ino);
        //printf("%i",birthtime(fileStat));        
/*
        time_t t = time(NULL);
        struct tm *tm = birthtime(fileStat);
        char s[64];
        strftime(s, sizeof(s), "%c", tm);
        printf(" %s ", s);

*/
        //snprintf(buffer , 20 ," %s ",ent->d_name);
        sprintf(d[index]->fname, "%s",ent->d_name);
         
        //printf("Check10 \n"); 
        index++;
        //printf("The file %s a symbolic link\n", (S_ISLNK(fileStat.st_mode)) ? "is" : "is not");
      }
      //printf(" index is %d \n ",index); 
      closedir(dir);
   
       int pass, comp;
       struct Display *temp;
       for(pass = 0 ; pass < index - 1; ++pass)
       {
          for(comp = 0 ; comp < index - pass - 1; ++comp)
          {
            if(strcmp(d[comp]->fname, d[comp+1]->fname) > 0)
            {
               temp = d[comp];
               d[comp] = d[comp+1];
               d[comp+1] = temp;
            } 
          }
       }
       for(i = 0; i<index ; i++)
       {
           printf("\n");
           printf("%s %s %s %s %20s %20s %s",d[i]->perm, d[i]-> no_of_links, d[i]->user_id,
                  d[i]->gr_id, d[i]->f_size, d[i]->bdate, d[i]->fname);
 

       }
   }
   else
       printf("Directory Reading Permission Denied\n"); 
   printf("\n");  
   
}
