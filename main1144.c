#include<stdio.h>
#include<string.h>
#include<ctype.h>
void f1144(char xx[])
{
    int i,count=0;

    for(i=0; xx[i]; i++)
        if(isdigit(xx[i]))
        {
            count++;
        }

    for(i=strlen(xx); i>=0; i--)
    {
        xx[i+count]=xx[i];

        if(isdigit(xx[i]))
        {
            xx[i+count-1]='$';
            count--;
        }
    }
}
int main1144()
{
    int i;
    char xx[100]= {0};
    gets(xx);
    f1144(xx);

    for(i=0; xx[i]; i++)
        printf("%c",xx[i]);

    return 0;
}

