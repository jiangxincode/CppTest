/*
ʵ��һ����������һ���ַ����е��ַ���СдתΪ��д��
*/

#include "stdio.h"

void uppers(char *s,char *us)
{
    for(; *s!='\0'; s++,us++)
    {
        if(*s>='a'&&*s<='z')
            *us = *s-32;
        else
            *us = *s;
    }
    *us = '\0';
}
void main0507()
{
    char *s,*us = NULL;
    char ss[20];
    printf("Please input a string:\n");
    scanf("%s",ss);
    s = ss;
    uppers(s,us);
    printf("The result is:\n%s\n",us);
}

