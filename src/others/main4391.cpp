/**
 * 字符串基本操作
 * 字符串操作C语言提供了较多的库函数，本题目要求代码中不能使用字符串操作相关的库函数，可以使用malloc。
 * 用例中可以使用中提供的库函数。
 * 实现接口，每个接口实现1个基本操作：
 * unsigned int strlenth(char*s)：计算字符串的长度。
 * void strcopy(char**target,char*source)：字符串拷贝，从source拷贝到target中。
 * int strcompare(char*s,char*t)：字符串比较，比较的原则：
 * 对两个字符串的每个字符从左到右逐个比较，进行ASCⅡ比较，只要一个字符大，则整个字符大；
 * 如果每个字符相等，但是其中一个字符串长度更长，则此字符串更大。
 * 如果s>t，返回1；如果s==t，返回0；如果s<T，返回-1。
 * void strcombine(char**x,char*s,char*t)：字符串连接，将字符串t接到s后面，并存储到x中。
 * void strcatch(char*s,unsignedintindex,unsignedintlenth,char**t)：字符串截取，对字符串s中，从第index个字符开始，截取lenth长度的字符串，并把截取出来的字符串存储到t中。
 * bool strsubstr(char*s,char*sub)：子串查找，在字符串s中查找字符串sub是否存在，如果存在则返回1，否则返回0。
 * 题目框架中有17个参考用例，其它用例请执行编写。
 *
 */
#include <stdlib.h>
#include <iostream>
#include <cstring>

unsigned int strlenth(char *s)  /* 获取字符串长度 */
{
    /* 代码在这里实现 */
    unsigned int lenth = 0;
    if((!s) || (s[0]=='\0'))
    {
        return 0;
    }
    while(*s++!='\0')
    {
        lenth++;
    }
    return lenth;
}

void strcopy(char **target, char *source)  /* 字符串拷贝 */
{
    /* 代码在这里实现 */
    int i=0;
    char *p=(char *)malloc(sizeof(char)*256);

    if((!source) || (source[0]=='\0'))
    {
        p="";
        *target=p;
    }
    else
    {
        while(source[i]!='\0')
        {
            p[i]=source[i];
            i++;
        }
    }
    p[i]='\0';
    *target=p;
}

int strcompare(char *s, char *t)  /* 字符串比较，s>t，则返回1；s=t，则返回0；s<t，则返回-1 */
{
    /* 代码在这里实现 */
    while(*s!='\0'&&*t!='\0')
    {
        if(*s>*t)
            return 1;
        if(*s<*t)
            return -1;
        else
        {
            s++;
            t++;
        }
    }
    if(*s=='\0'&&*t=='\0')
        return 0;
    if(*s=='\0'&&*t!='\0')
        return -1;
    if(*s!='\0'&&*t=='\0')
        return 1;

    return 0;
}

void strcombine(char **x, char *s, char *t)  /* 字符串连接，将字符串t接到s后面，x为连接后的新串 */
{
    /* 代码在这里实现 */
    char *p=(char *)malloc(sizeof(char)*256);

    if(!s&&!t)
    {
        p="";
        *x=p;
    }
    else if(!s&&t)
    {
        int i=0;
        while(t[i]='\0')
        {
            p[i]=t[i];
            i++;
        }
        p[i]='\0';
        *x=p;
    }
    else if(s&&!t)
    {
        int i=0;
        while(s[i]!='\0')
        {
            p[i]=s[i];
            i++;
        }
        p[i]='\0';
        *x=p;

    }
    else
    {
        int i=0;

        while(s[i]!='\0')
        {
            p[i]=s[i];
            i++;
        }
        while(*t!='\0')
        {
            p[i]=*t++;
            i++;
        }
        p[i]='\0';
        *x=p;
    }
}

void strcatch(char *s, unsigned int index, unsigned int lenth, char **t)  /* 字符串截取，从第index个字符开始，截取lenth长度的字符串，并输出到字符串t */
{
    /* 代码在这里实现 */
    char *p=(char *)malloc(sizeof(char)*256);

    if(!s||(index>strlenth(s))||(lenth>strlenth(s)-index)||lenth==0)
    {
        p=0;
        *t=p;
    }
    else
    {
        int i=(int)index;
        int j=0;

        for(;i<(int )(lenth+index);i++)
        {
            p[j]=s[i];
            j++;
        }
        p[j]='\0';
        *t=p;
    }

}


bool strsubstr(char *s, char *sub)  /* 字符串子串查找，如果子串sub在s中存在，则返回1，否则返回0 */
{
    bool result = 0;

    /* 代码在这里实现 */
    if(!s||!sub||(s[0]=='\0')||(sub[0]=='\0'))
        return  result;

    int count=0;
    while(sub[count]!='\0')
        count++;

    for(int i=0;s[i]!='\0';i++)
    {
        int temp=i,j=0;
        while(s[temp]==sub[j]&&(s[temp]!='\0')&&(sub[j]!='\0'))
        {
            temp++;
            j++;
        }
        if((temp-i)==count)
        {
            return 1;
            break;
        }
    }
    return result;
}

int main() {
    /* －－－－－－－－－－获取字符串长度类用例－－－－－－－－－－－－－ */
    {
        char s[] = "china";
        unsigned int lenth = 0;

        lenth = strlenth(s);

        std::cout << (lenth == 5) << std::endl;
    }

    {
        char s[] = "";
        unsigned int lenth = 0;

        lenth = strlenth(s);

        std::cout << (lenth == 0) << std::endl;
    }
    /* －－－－－－－－－－获取字符串长度类用例－－－－－－－－－－－－－ */

    /* －－－－－－－－－－字符串拷贝类用例－－－－－－－－－－－－－ */
    {
        char s[] = "china";
        char *t = 0;
        unsigned int lenth = 0;

        strcopy(&t, s);

        std::cout << (strcmp(s, t) == 0) << std::endl;

        free(t);
    }
    /* －－－－－－－－－－字符串拷贝类用例－－－－－－－－－－－－－ */

    /* －－－－－－－－－－字符串比较类用例－－－－－－－－－－－－－ */
    {
        char s[] = "china";
        char t[] = "american";
        int result = 0;

        result = strcompare(s, t);

        std::cout << (result == 1) << std::endl;
    }

    {
        char s[] = "China";
        char t[] = "china";
        int result = 0;

        result = strcompare(s, t);

        std::cout << (result == -1) << std::endl;
    }

    {
        char s[] = "china";
        char t[] = "china";
        int result = 0;

        result = strcompare(s, t);

        std::cout << (result == 0) << std::endl;
    }

    {
        char s[] = "china";
        char t[] = "chinagood";
        int result = 0;

        result = strcompare(s, t);

        std::cout << (result == -1) << std::endl;
    }

    {
        char s[] = "chinagood";
        char t[] = "china";
        int result = 0;

        result = strcompare(s, t);

        std::cout << (result == 1) << std::endl;
    }
    /* －－－－－－－－－－字符串比较类用例－－－－－－－－－－－－－ */

    /* －－－－－－－－－－字符串连接类用例－－－－－－－－－－－－－ */
    {
        char s[] = "chin";
        char t[] = "ese";
        char *x;

        strcombine(&x, s, t);

        char y[] = "chinese";
        std::cout << (strcmp(x, y) == 0) << std::endl;

        free(x);
    }
    /* －－－－－－－－－－字符串连接类用例－－－－－－－－－－－－－ */

    /* －－－－－－－－－－字符串截取类用例－－－－－－－－－－－－－ */
    {
        char s[] = "chinese is great";
        char *x;

        strcatch(s, 8, 2, &x);

        char y[] = "is";
        std::cout << (strcmp(x, y) == 0) << std::endl;

        free(x);
    }

    {
        char s[] = "chinese is great";
        char *x = 0;

        strcatch(s, 8, 0, &x);

        std::cout << (x == 0) << std::endl;
    }

    {
        char s[] = "chinese is great";
        char *x = 0;

        strcatch(s, 8, 17, &x);

        std::cout << (x == 0) << std::endl;
    }

    {
        char s[] = "chinese is great";
        char *x = 0;

        strcatch(s, 8, 9, &x);

        std::cout << (x == 0) << std::endl;
    }
    /* －－－－－－－－－－字符串截取类用例－－－－－－－－－－－－－ */

    /* －－－－－－－－－－子串查找类用例－－－－－－－－－－－－－ */
    {
        char s[] = "chinese is good";
        char t[] = "ese";
        bool result = 0;

        result = strsubstr(s, t);

        std::cout << (result == 1) << std::endl;
    }

    {
        char s[] = "chinese is good";
        char t[] = "chinese is good";
        bool result = 0;

        result = strsubstr(s, t);

        std::cout << (result == 1) << std::endl;
    }

    {
        char s[] = "chinese is good";
        char t[] = "chinese is good!";
        bool result = 0;

        result = strsubstr(s, t);

        std::cout << (result == 0) << std::endl;
    }

    {
        char s[] = "chinese is good";
        char t[] = "est";
        bool result = 0;

        result = strsubstr(s, t);

        std::cout << (result == 0) << std::endl;
    }
    /* －－－－－－－－－－子串查找类用例－－－－－－－－－－－－－ */
}
