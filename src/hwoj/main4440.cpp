/**
 * 可怕的阶乘
 * 题目标题：
 * 计算阶乘n!是一件可怕的事情，因为当n并不是很大时，n!将是一个很大的值。例如13! = 6227020800，已经超过了我们常用的unsigned int类型的取值范围。请设计一个程序，使其可以计算100以内的数的阶乘，结果用字符串的形式输出。
 * 详细描述：
 * 接口说明
 * 原型：
 * void CalcNN(int n, char *pOut)
 * 输入参数：
 * int n 需要计算的阶乘数
 * 输出参数：
 * char *pOut 结算结果，内存由调用者负责管理
 * 返回值：
 * 无
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

#define MAXBIT 200

void CalcNN(int n, char *pOut)
{
    int bit[MAXBIT] = {0};
    if(n < 0)
    {
        pOut[0] = '\0';
        return;
    }
    else if((n==0) || (n==1))
    {
        pOut[0] = '1';
        pOut[1] = '\0';
        return ;
    }
    bit[0] = 1;
    for(int i=2;i<=n;i++)
    {
        for(int j=0;j<MAXBIT;j++)
        {
            bit[j]=bit[j]*i;
        }

        for(int j=0;j<MAXBIT;j++)
        {
            if(bit[j]>9) //process carry
            {
                for(int k=j;k<MAXBIT;k++)
                {
                    bit[k+1] += bit[k] / 10;
                    bit[k] = bit[k] % 10;
                }
            }

        }


    }
    int temp = MAXBIT-1;

    while(bit[temp]==0)
    {
        temp--;
    }

    for(;temp>=0;temp--)
    {
        *(pOut++) = bit[temp] + '0';
    }
    *pOut='\0';

    return;
}

int main()
{
    char *p;

    p = (char *)malloc(1000);
    CalcNN(13, p);
    std::cout << (0 == strcmp(p, "6227020800")) << std::endl;
    free(p);
}
