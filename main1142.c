/*��дһ������ͳ������һ���ַ����и�����ĸʹ�ô�������Сд�����֣���
��������Ϊ�����ĸ�����������*/
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

