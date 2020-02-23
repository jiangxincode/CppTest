#include <stdio.h>
#include <string.h>
#include <ctype.h>

int  find1146(char(*s1)[10],int m,char(*s2)[10],int n,char(*s3)[10])
{
    int i,j,k=0;

    for(i=0; i<m; i++)
        for(j=0; j<n; j++)
            if(strcmp(*(s1+i),*(s2+j))==0)
            {
                strcpy(*(s3+k),*(s2+j));
                k++;
            }

    return k;
}
int main()
{
    char p1[6][10]= {"while", "for", "switch", "if", "break", "continue"},
                    p2[6][10]= {"for", "case", "do", "else", "char", "switch"} ,
                               p3[6][10];
    int d,i;
    d=find1146(p1,6,p2,6,p3);

    for(i=0; i<d; i++)
    {
        puts(p3[i]);
    }

    return 0;
}





