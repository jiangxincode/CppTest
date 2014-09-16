#include <iostream>
#include <string>
/*
给定一个query和一个text，均由小写字母组成。
要求在text中找出以同样的顺序连续出现在query中的最长连续字母序列的长度。
例如， query为“acbac”，text为“acaccbabb”，
那么text中的“cba”为最长的连续出现在query中的字母序列，
因此，返回结果应该为其长度3。
请注意程序效率。
2015 阿里巴巴 数据研发工程师 在线笔试
*/
using namespace std;

int main0031()
{
    string text,query;
    cout << "Input text: " << endl;
    cin >> text;
    cout << "Input query: " << endl;
    cin >> query;
    string::size_type len = 0;
    for(string::size_type i=0; i<query.length(); i++)
    {
        for(string::size_type j=query.length()-1; j>i; j--)
        {
            string temp = query.substr(i,j);
            if(text.find(temp) != string::npos)
            {
                if((j-i)>len)
                {
                    len = j - i + 1; //i和j位置之中共有(j-i+1)个元素
                }
            }
        }
    }
    cout << len;
    return 0;
}


/*
求两个字符串最长公共子串(LCS问题)
(1)算法的基本思想：利用矩阵对角原理来实现
当字符匹配的时候，不是简单的给相应元素赋上1，而是赋上其左上角元素的值加一。
我们用两个标记变量来标记矩阵中值最大的元素的位置，在矩阵生成的过程中来判断
当前生成的元素的值是不是最大的，据此来改变标记变量的值，那么到矩阵完成的时
候，最长匹配子串的位置和长度就已经出来了。
==========================================================================
输入
字符串1：21232523311324
字符串2：312123223445
数组c的变化情况为：
 0 0 1 0 1 0 1 1 0 0 0 0
 0 1 0 2 0 0 0 0 0 0 0 0
 0 0 2 0 3 0 1 1 0 0 0 0
 1 0 0 0 0 4 0 0 2 0 0 0
 0 0 1 0 1 0 5 1 0 0 0 0
 0 0 0 0 0 0 0 0 0 0 0 1
 0 0 1 0 1 0 1 1 0 0 0 0
 1 0 0 0 0 2 0 0 2 0 0 0
 1 0 0 0 0 1 0 0 1 0 0 0
 0 2 0 1 0 0 0 0 0 0 0 0
 0 1 0 1 0 0 0 0 0 0 0 0
 1 0 0 0 0 1 0 0 1 0 0 0
 0 0 1 0 1 0 2 1 0 0 0 0
 0 0 0 0 0 0 0 0 0 1 1 0
长：14（串1的长度），宽：12（串2的长度）
最长子串为:21232
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define M 100
char* LCS(char left[],char right[])
{
    int lenLeft = strlen(left),lenRight=strlen(right);
    char *c = (char *)malloc(lenRight), *p;//注意这里要写成char型,而不是int型,否则输入整型数据时会产生错误。      //矩阵c纪录两串的匹配情况
    int start,end,len; //start表明最长公共子串的起始点，end表明最长公共子串的终止点
    end=len=0;//len表示最长公共子串的长度

    for(int i=0; i<lenLeft; i++) //串1从前向后比较
    {
        for(int j=lenRight-1; j>=0; j--) //串2从后向前比较
        {
            if(left[i] == right[j])//元素相等时
            {
                if(i==0||j==0)
                    c[j]=1;
                else
                {
                    c[j]=c[j-1]+1;
                }
            }
            else
                c[j] = 0;

            if(c[j] > len)
            {
                len=c[j];
                end=j;
            }
        }
    }

    start=end-len+1;
    p =(char*)malloc(len+1);//数组p纪录最长公共子串

    for(int i=start; i<=end; i++)
    {
        p[i-start] = right[i];
    }

    p[len]='\0';
    return p;
}
void main0032()
{
    char str1[M],str2[M];
    printf("请输入字符串1:");
    gets(str1);
    printf("请输入字符串2:");
    gets(str2);
    printf("最长子串为:");
    printf("%s\n",LCS(str1,str2));
}

void GetMaxCommStr(char *s1,char *s2,char *s3)//s1、s2 为要对比的俩个字符串，
{
    //s3用来存储最大的公共字符串
    // char *s1=stra,  *s2=strb;
    char len1 = strlen(s1);
    char len2 = strlen(s2);
    char maxlen = 0;

    for(int i = 0; i < len1; i++)
    {
        for(int j = 0; j < len2; j++)
        {
            if(s1[i] == s2[j])     //找到了第一个相等的
            {
                int as = i, bs = j, count = 1; //保存第一个相等的首地址

                while((as+1<len1) && (bs+1<len2) && (s1[++as] == s2[++bs]))     //查找最大相等长度
                    count++;

                if(count > maxlen)  //如果大于最大长度则更新
                {
                    maxlen = count;
                    //r1=i;             //存储公共子字符串的起始位
                }
            }
        }
    }

    if(maxlen>0)  //有公共子字符串
    {
        for(int i=0; i<maxlen; i++)
        {
            *(s3+i)=*(s1+i);
        }

        printf("maxlen is %d\n",maxlen);
        printf("len1 is %d\n",len1);
        printf("len2 is %d\n",len2);
    }
}

int main0033()
{
    char strd[80]= {0};
    char stra[80]="iojhklgklskljklngvnkldg";
    char strb[80]="kldfjjsfgjlkjgldakfga;";
    GetMaxCommStr(stra,strb,strd);
    printf("stra is: %s\n",stra);
    printf("strb is: %s\n",strb);
    printf("strd is: %s\n",strd);
    return 0;
}

int main003()
{
    main0031();
    return 0;
}
