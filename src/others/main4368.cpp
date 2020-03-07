/**
 * 数字统计
 * 题目标题：
 * 对输入的整型数组，输出数组元素中的最大值、最大值的个数、最小值和最小值的个数
 * 详细描述：
 * 接口说明
 * 原型：
 * voidOutputMaxAndMin(int * pInputInteger,intInputNum,int * pMaxValue,int * pMaxNum,int * pMinValue,int * pMinNum);
 * 输入参数：
 *     Int * pInputInteger：整型数组指针
 * Int   InputNum：数组元素个数
 * 输出参数（指针指向的内存区域保证有效）：
 *     int* pMaxValue：数组中最大值
 *      int* pMaxNum：数组中最大值的个数
 *      int* pMinValue：数组中最小值
 * int* pMinNum：数组中最小值的个数
 * 返回值：
 *     void
 * 涉及知识点：
 * C语言基础：数组、比较
 * 性能要求：
 * 无
 * 圈复杂度要求：
 * 这个不由出题者提供，由后续判题系统全局配置
 * 如：函数圈复杂度低于10，类公函数小于20等
 * 代码工程和用例：
 * C/C++:
 * VS2005代码工程
 * 嵌入工程的CPPUNIT用例
 *
 */

#include <iostream>
using namespace std;

/*
功能:对输入的整型数组，输出数组元素中的最大值、最大值的个数、最小值和最小值的个数

输入:int * pInputInteger：整型数组指针
	 int * InputNum：数组元素个数

输出:int * pMaxValue：数组中最大值
  	 int * pMaxNum：数组中最大值的个数
	 int * pMinValue：数组中最小值
     int * pMinNum：数组中最小值的个数

返回:void
*/
void OutputMaxAndMin(int * pInputInteger, int InputNum, int * pMaxValue, int * pMaxNum, int * pMinValue, int * pMinNum)
{
    /*在这里实现功能*/
    if(InputNum <= 0 || pInputInteger == NULL)
    {
        *pMaxNum =0;
        *pMinNum = 0;
        *pMaxValue = 0;
        *pMinValue = 0;
        return ;
    }

    (*pMaxValue) = pInputInteger[0];
    (*pMinValue) = pInputInteger[0];
    (*pMaxNum) = 0;
    (*pMinNum) = 0;

    for(int i=0; i<InputNum; i++)
    {
        if(pInputInteger[i] > (*pMaxValue))
        {
            (*pMaxValue) = pInputInteger[i];
            (*pMaxNum) = 1;
        }
        else if(pInputInteger[i] == (*pMaxValue))
        {
            (*pMaxNum) ++;
        }

        if(pInputInteger[i] < (*pMinValue))
        {
            (*pMinValue) = pInputInteger[i];
            (*pMinNum) = 1;
        }
        else if(pInputInteger[i] == (*pMinValue))
        {
            (*pMinNum) ++;
        }
    }

    return;
}

int main() {
    {
        int aInputInteger[] = {1, 2, 3, 4};
        int iMaxValue, iMaxNum, iMinValue, iMinNum;

        OutputMaxAndMin(aInputInteger, 4, &iMaxValue, &iMaxNum, &iMinValue, &iMinNum);

        std::cout << (iMaxValue  == 4) << std::endl;
        std::cout << (iMaxNum == 1) << std::endl;
        std::cout << (iMinValue == 1) << std::endl;
        std::cout << (iMinNum == 1) << std::endl;
    }

    {
        int aInputInteger[] = {1, 2, 1, 4, 4, 5, 63, 64, 4, 64, 5};
        int iMaxValue, iMaxNum, iMinValue, iMinNum;

        OutputMaxAndMin(aInputInteger, 11, &iMaxValue, &iMaxNum, &iMinValue, &iMinNum);

        std::cout << (iMaxValue  == 64) << std::endl;
        std::cout << (iMaxNum == 2) << std::endl;
        std::cout << (iMinValue == 1) << std::endl;
        std::cout << (iMinNum == 2) << std::endl;
    }
}
