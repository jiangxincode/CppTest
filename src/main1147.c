#include <stdio.h>
#include <string.h>
#include <ctype.h>

int  my_delete(char s[][10],int n)
{
    int i,j,k;

    for(i=0,k=0; i<n; i++)
    {
        for(j=0; s[i][j]!='\0'; j++)
        {
            if(isalpha(s[i][j])||isdigit(s[i][j])||s[i][j]=='_')
            {
                continue;
            }
            else
            {
                break;
            }
        }

        if(s[i][j]=='\0'&&!isdigit(s[i][0]))
        {
            strcpy(s[k],s[i]);
            k=k+1;
        }
    }

    return k;
}
int main1147()
{
    char a[][10]= {"a%1","_a12","aaa","$ss","1sss"};
    int d,i;
    d=my_delete(a,5);

    for(i=0; i<d; i++)
    {
        puts(a[i]);
    }

    return 0;
}





