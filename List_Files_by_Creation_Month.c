//Display all the files from current directory which are created in particular month 

#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<sys/stat.h>
#include<time.h>

int main(int argc,char *argv[])
{
     DIR *dir;
     struct stat file_stat;
     struct dirent *entry;
     struct tm *timeinfo;
     int target_month;

     if(argc!=2)
     {
        printf("Usage  : %s  <month number>\n",argv[0]);
        return 1;
     }

     target_month=atoi(argv[1]);

     if(target_month<1 || target_month>12)
     {
        printf("Month must be between 1 and 12 \n");
        return 1;
     }

     dir=opendir(".");
     if(dir==NULL)
     {
        printf("Unable to open\n");
        return 1;
     }

     while((entry=readdir(dir))!=NULL)
     {
        if(stat(entry->d_name,&file_stat)==0)
        {
            timeinfo=localtime(&file_stat.st_ctime);


            if((timeinfo->tm_mon+1)==target_month)
            {
                printf("%s\n",entry->d_name);
            }
            
        }
     }

     closedir(dir);
    return 0;

}