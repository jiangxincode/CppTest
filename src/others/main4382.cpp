/**
 * 找出升序数组中和为给定值的两个数字
 * 输入一个已经按升序排序过的数组和一个数字，在数组中查找两个数，使得它们的和正好是输入的那个数字。如果有多对数字的和等于输入的数字，输出任意一对即可。
 * 详细描述：
 * 接口说明
 * 原型：
 * bool FindTwoNumbersWithSum(int aData[], unsignedint uiLength, int sum, int *pNum1, int *pNum2);
 * 输入参数：
 *         int aData[]           // 升序数组
 *          unsigned int uiLength // 数组元素个数
 *       int sum,              // 给定两个数组的和
 * 输出参数（指针指向的内存区域保证有效）：
 *         int*pNum1            // 第一个数字，对应数组索引小的
 *       int *pNum2            // 第二个数字，对应数组索引大的
 * 返回值：
 *     找到返回true，异常返回false
 *
 */
#include <stdlib.h>
#include <iostream>

/*
功能: 输入一个已经按升序排序过的数组和一个数字，在数组中查找两个数，使得它们的和正好是输入的那个数字。如果有多对数字的和等于输入的数字，输出任意一对即可。

输入: int aData[]           // 升序数组
      unsigned int uiLength // 数组元素个数
      int sum,              // 给定两个数组的和

输出: int *pNum1            // 第一个数字，对应数组索引小的
      int *pNum2            // 第二个数字，对应数组索引大的

返回: 找到返回true，异常返回false
*/
bool FindTwoNumbersWithSum(int aData[], unsigned int uiLength, int sum, int *pNum1, int *pNum2)
{
    /*在这里实现功能*/
    if((aData == NULL) || (uiLength < 2))
    {
        return false;
    }
    for(unsigned int i=0;i<uiLength-1;i++)
    {
        for (unsigned int j=i+1;j<uiLength;j++)
        {
            if(aData[i]+aData[j] == sum)
            {
                *pNum1 = aData[i];
                *pNum2 = aData[j];
                return true;
            }
            else if(aData[i]+aData[j] > sum)
            {
                break;
            }
            else
            {
                continue;
            }
        }
    }
    return false;
}

int main()
{
    int  aData[] = {1, 2, 4, 7, 11, 15};
    int  iNum1, iNum2;
    bool bReturn;

    bReturn = FindTwoNumbersWithSum(aData, 6, 15, &iNum1, &iNum2);

    std::cout << (true == bReturn) << std::endl;
    std::cout << (4  == iNum1) << std::endl;
    std::cout << (11 == iNum2) << std::endl;
}
