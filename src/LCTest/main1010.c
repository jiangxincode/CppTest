#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_LENGTH_PATHNAME 255
#define BUFFSZIE 4096


int main10101()
{
        DIR *dp;
        struct dirent *dirp;
        char pathname[MAX_LENGTH_PATHNAME];
        printf("Input the pathname: ");
        scanf("%s",pathname);
        if((dp = opendir(pathname)) == NULL)
        {
                perror("error:opendir");
        }
        while((dirp = readdir(dp)) != NULL)
        {
                printf("%s\n",dirp->d_name);
        }
        closedir(dp);
        return 0;
}

int main10102()
{
        int n;
        char buff[BUFFSZIE];
        while((n=read(STDIN_FILENO,buff,BUFFSZIE)) != 0)
        {
                if((write(STDOUT_FILENO,buff,n)) != n)
                {
                        perror("error:write");
                }
        }
        return 0;
}
int main1010()
{
        main10102();
        return 0;
}
