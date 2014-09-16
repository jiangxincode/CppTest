/*
某淘宝商家根据客户购买宝贝件数n给出不同的折扣率discnt与快递费f优惠策略。
分析下列折扣率与快递费计算程序片段的优劣，提出改进方案，并给出改进程序。
*/
#include <iostream>
#include <cstdio>
using namespace std;
int main2527()
{
    int f = 10, n = 0;
    double discnt = 0;
    double d_prince = 0.0;
    scanf("%d", &n);
    if(n <= 0)
    {
        printf("Error!");
    }
    else
    {
        if(n <= 9)
            ;
        else if(n <= 19)
            discnt = 0.05;
        else if(n <= 29)
            discnt = 0.1;
        else if(n <= 49)
            discnt = 0.2;
        else if(n > 49)
        {
            discnt = 0.2;
            f = 0;
        }
    }
}
