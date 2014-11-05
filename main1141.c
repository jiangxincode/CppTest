/*
【程序功能】
 replaceword函数的功能是对s指向的数组所存储的一个英文句子中的每个单词作如下处理：
 在word_tab数组中查找该单词，若未找到则保持原单词不变；
 若找到则用word_tab数组中该单词后面的第一个单词替换句子中的原单词
 （如果该单词是word_tab数组中的最后一个单词则用第一个单词替换）。
【测试数据与运行结果】
 测试数据：I accuse your mistakes.
 输出结果：I forgive your mistakes.
【要求】
1．根据题目要求及程序中语句之间的逻辑关系对程序中的错误进行修改。
2．改错时，可以修改语句中的一部分内容，调整语句次序，
   增加少量的声明或编译预处理命令，但不能增加其他语句，也不能删去整条语句。
*/
#include<stdio.h>
#include<string.h>
#include<ctype.h>
void replaceword(char s[])
{
    char word_tab[4][10]= {"sad","happy","accuse","forgive"};
    char t[10],tmp[80];
    int i,j,k,n;

    for(i=0; s[i]; i++)
    {
        for(j=i,k=0; isalpha(s[j]); k++,j++)
            t[k]=s[j];

        t[k]=0;

        if(k>0)
        {
            for(n=0; n<4; n++)
                if(strcmp(t,word_tab[n])==0)
                    break;

            if(n<4)
            {
                strcpy(tmp,s+i+strlen(t));
                strcpy(s+i,word_tab[(n+1)%4]);
                strcat(s,tmp);
                i=i+strlen(word_tab[(n+1)%4]);
            }
            else
                i=i+strlen(t);
        }
    }
}
int main1141()
{
    char line[80]="I accuse your mistakes.";
    replaceword(line);
    puts(line);
    return 0;
}
