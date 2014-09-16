#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<conio.h>
void FindLWord(char *a,char*b)
{
    char p[50];
    int i,j,k;

    for(i=0; i<(int)strlen(a); i++)
    {
        if(isalpha(a[i])&&!isalpha(a[i-1]))
        {
            for(j=i,k=0; isalpha(a[j]); j++)
            {
                p[k]=a[j];
                k++;
            }

            p[k]='\0';

            if(strlen(p)>strlen(b))
                strcpy(b,p);
        }
    }
}
main1145()
{
    char a[20],b[2]= {0};
    gets(a);
    FindLWord(a,b);
    puts(b);
    getch();
}
















