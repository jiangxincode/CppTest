#include<stdio.h>
#include<string.h>
#include<ctype.h>
int f1143(char a[])
{
    int i,j,count=0;

    for(i=0; a[i]; i++)
        if(isdigit(a[i]))
        {
            for(j=i; a[j]; j++)
            {
                a[j]=a[j+1];
            }

            count++;
            i--;
        }

    return count;
}
int main1143()
{
    int count,i;
    char a[100]= {0};
    fgets(a,100,stdin);
    count=f1143(a);

    for(i=0; a[i]; i++)
        printf("%c",a[i]);

    printf("\n%d",count);
    return 0;
}



