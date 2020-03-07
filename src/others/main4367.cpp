/**
 * 数列求和
 * 题目描述
 *     编写程序，输入一个正整数n，求下列算式的值。要求定义和调用函数fact(k)计算k的阶乘。
 * 1+1/2!+ .... +1/n!
 * 计算结果保存在double类型变量中。
 * 接口说明
 * 原型：
 * void GetResult(int InputNum, double *NumResult);
 * 输入参数：
 *     Int  InputNum：输入一个正整数，进行表达式计算
 *     char *NumResult：输出表达式的值
 * 返回值：
 *     void
 *
 */
#include "iostream"


/*
void GetResult(int InputNum, double *NumResult);
输入参数：
        Int  InputNum：输入一个正整数，进行表达式计算
        char *NumResult：输出表达式的值
返回值：
        void

*/

void GetResult(int InputNum, double *NumResult)
{

    //1+1/2!+ .... +1/n!
    *NumResult = 0.0;
    if(InputNum <= 0)
    {
        return;
    }
    int s = 1;
    for(int i=1;i<=InputNum;i++)
    {
        s *= i;
        *NumResult = *NumResult+1/(double)s;
    }
    return ;
}

int main() {
    {
        int InputNum = 1;
        double NumResult = 0;

        GetResult(InputNum, &NumResult);

        std::cout << (1.000001 > NumResult && 0.999999 < NumResult) << std::endl;
    }

    {
        int InputNum = 2;
        double NumResult = 0;

        GetResult(InputNum, &NumResult);

        std::cout << (1.500001 > NumResult && 1.499999 < NumResult) << std::endl;
    }

    {
        int InputNum = 3;
        double NumResult = 0;

        GetResult(InputNum, &NumResult);

        std::cout << (1.666667 > NumResult && 1.666666 < NumResult) << std::endl;
    }

    {
        int InputNum = 4;
        double NumResult = 0;

        GetResult(InputNum, &NumResult);

        std::cout << (1.708334 > NumResult && 1.708333 < NumResult) << std::endl;
    }

    {
        int InputNum = 5;
        double NumResult = 0;

        GetResult(InputNum, &NumResult);

        std::cout << (1.716667 > NumResult && 1.716666 < NumResult) << std::endl;
    }
}
