/**
 * 求某二进制数中1的个数
 * 题目标题：
 * 求某二进制数中1的个数。
 * 给定一个unsigned int型的正整数，求其二进制表示中“1”的个数，要求算法的执行效率尽可能地高。
 * 详细描述：
 * 接口说明
 * 原型：
 * int GetCount(unsigned int num)
 * 输入参数：
 *      num     给定的正整数
 * 输出参数（指针指向的内存区域保证有效）：
 *     无
 * 返回值：
 * 返回1的个数
 * 举例：
 * 输入13，则对应的二进制是1101，那么1的个数为3个。
 *          则：返回3。
 *
 */
#include "iostream"

/*
Description
         给定一个unsigned int型的正整数，求其二进制表示中“1”的个数，要求算法的执行效率尽可能地高。
Prototype
         int GetCount(unsigned int num)
Input Param
         num     给定的正整数
Output Param
         无
Return Value
         返回1的个数
*/
int GetCount(unsigned int num)
{
    /*在这里实现功能*/
    int result = 0;
    while (num != 0)
    {
        if (num % 2 == 1)
        {
            result ++;
        }
        num /= 2;
    }

    return result;
}

int main()
{
    std::cout << (GetCount(13) == 3) << std::endl;
}
