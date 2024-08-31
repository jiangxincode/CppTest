/**
 * 24点游戏算法 Game24
 * 题目
 * 问题描述：给出4个1-10的数字，通过加减乘除，得到数字为24就算胜利
 * 输入：
 * 4个1-10的数字。[数字允许重复，测试用例保证无异常数字]
 * 输出：
 * True or False
 *
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <iostream>

double const PRECISION = 1e-6; // 精度
bool Game24(int n,double a[])
{
    if (n <= 0)
    {
        return false;
    }
    if (n == 1)
    {
        if(fabs(a[0]-24) < PRECISION)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            double b = a[i];
            double c = a[j];
            a[j] = a[n-1];

            a[i] = b + c;
            if(Game24(n-1,a))
            {
                return true;
            }

            a[i] = b-c;
            if (Game24(n-1,a))
            {
                return true;
            }

            a[i] = c-b;
            if (Game24(n-1,a))
            {
                return true;
            }

            a[i] = b * c;
            if(Game24(n-1,a))
            {
                return true;
            }

            if(c != 0)
            {
                a[i]=b/c;
                if(Game24(n-1,a))
                {
                    return true;
                }
            }

            if(b != 0)
            {
                a[i]=c/b;
                if(Game24(n-1,a))
                {
                    return true;
                }
            }
            a[i]=b;
            a[j]=c;
        }
    }
    return false;
}

bool Game24Points(int a, int b, int c, int d)
{
    double d_array[4];
    d_array[0] = (double)a;
    d_array[1] = (double)b;
    d_array[2] = (double)c;
    d_array[3] = (double)d;
    return Game24(4,d_array);
}

int main() {
    std::cout << (Game24Points(7, 2, 1, 10) == true) << std::endl;
    std::cout << (Game24Points(1, 2, 3, 4) == true) << std::endl;
    std::cout << (Game24Points(7, 7, 7, 7) == false) << std::endl;
}

