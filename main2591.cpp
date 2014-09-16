/*
实现将输入字符串转化为浮点类型的功能，
并将该功能用函数进行封装。
例如，输入“0.142”，输出为一个double类型，其值为0.142。
不允许使用atoi、atof、atol等函数。
*/

#include <stdio.h>
#include <iostream>

using namespace std;
float atof(char *c)
{
    float f=0,t=0,te=1;
    int i,op=1,eop=0,ep=0,cf=0;;
    for (i = 0; c[i]; i++)
    {
        if (c[i]=='.')
        {
            op=0;
        }
        if (c[i]=='e'||c[i]=='E')
        {
            eop=1;
            op=2;
        }
        if (eop&&c[i]=='-')
        {
            cf=1;
        }
        else if (eop&&c[i]=='+')
        {
            cf=0;
        }
        if (op==1&&c[i]>='0'&&c[i]<='9')
        {
            f=f*10+(c[i]-'0');
        }
        else if(!op&&c[i]>='0'&&c[i]<='9')
        {
            te*=10;
            t=t*10+c[i]-'0';
        }
        else if (eop&&c[i]>='0'&&c[i]<='9')
        {
            ep=ep*10+c[i]-'0';
        }
    }
    f=f+t/te;
    te=1;

    for (i = 0; i<ep; i++)
    {
        te*=10;
    }
    if (cf)
    {
        return f/te;
    }
    else return f*te;
}
int main2591()
{
    float f=0;
    char a[]="0.142";
    f=atof(a);
    cout << f;
    return 0;
}
