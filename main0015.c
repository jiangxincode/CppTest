/**
 * 实现一个函数，把一个字符串中的字符从小写转为大写。
 */

#include <stdio.h>
#include <stdlib.h>

void uppers(const char *s,char *us)
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
void main0015()
{
    char source[20];
    printf("Please input a string:\n");
    scanf("%s",source);
    char *target = (char *)malloc(sizeof(source));
    uppers(source,target);
    printf("The result is:\n%s\n",target);
}
