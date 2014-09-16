/*编写一个程序，统计输入一行字符串中各个字母使用次数（大小写不区分），
将次数不为零的字母及次数输出。*/
#include<stdio.h>
#include<ctype.h>
int main1142()
{
    int a[26]= {0},i;
    char s[100],ch;
    gets(s);

    for(i=0; s[i]; i++)
        if(isalpha(s[i]))
        {
            ch=tolower(s[i]);
            a[ch-'a']++;
        }

    for(i=0; i<26; i++)
        if(a[i])
            printf("%c:%d",i+'a',a[i]);
}

