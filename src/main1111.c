#include<stdio.h>
int *count1111(char *ch_p)
{
    static int num=0;

    if(*ch_p>='A'&&*ch_p<='Z')
    {
        *ch_p+=32;
    }

    if(*ch_p=='a'||*ch_p=='e'||*ch_p=='i'||*ch_p=='o'||*ch_p=='u')
    {
        num++;
    }

    return &num;
}
int main1111(void)
{
    int *n;
    char ch;

    while((ch=getchar())!='\n')
    {
        n=count1111(&ch);
        putchar(ch);
    }

    printf(",\t%d\n",*n);
    return 0;
}


