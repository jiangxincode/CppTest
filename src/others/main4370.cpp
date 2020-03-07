/**
 * 兔子产子
 * 从前有一对长寿的兔子，他们每个月生出一对小兔子，第一个月新生产的兔子两个月就长大了，在第三个月初开始生他们的下一代小兔子，这样一代一代的生下去，不考虑兔子的寿命，求第n个月出生多少对小兔子

 * 简单示例:
 * 比如输入1，第一个月出生的兔子只有一对，所以输出为1
 * 比如输入2，第二个月出生的兔子只有一对，所以输出为1
 * 比如输出为3，则该月份有两对兔子出生，则输出为2
 *
 * 要求:
 *
 * 实现以下接口：
 * 输入一个正整数，表示第几个月，输出该月份生产出的小兔子的对数
 * 调用者会保证：
 * 输入的月份与生产的兔子数目都为unsigned int 能表达的数字
 *
 */
#include <stdlib.h>
#include "iostream"
// 功能：获取第nValue1个月出生多少对兔子
// 输入： nValue1为正整数
// 输出：无
// 返回：第nValue1个月出生多少对兔子

unsigned int GetBirthRabbitNum(unsigned int  nValue1)
{
    if(nValue1==1||nValue1==2)
        return 1;
    else
        return GetBirthRabbitNum(nValue1-1)+GetBirthRabbitNum(nValue1-2);
}

int main()
{
    unsigned int nResult = GetBirthRabbitNum(1);

    std::cout << (1 == nResult) << std::endl;
}
