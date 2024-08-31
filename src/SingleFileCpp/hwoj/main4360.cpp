/**
 * 求圆的面积
 * 题目背景
 * 计算半径为1到10的圆的面积，若面积在40到90之间请输出
 * 接口
 * int OutPutRotundityArea（float* pResultArray，int &ArrayCount）
 * float* pResultArray ：float型数组
 * Int ArrayCount：数组长度
 * 规格
 * 要求时间复杂度为O(n)
 * π = 3.14
 *
 */
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <iostream>

using namespace std;

/*
功能:

输入:

输出:	arrValue:存储返回的符合范围之内的圆面积，内存在函数外已经申请
		nValue:返回数组的行数

返回:

*/

void OutputRotundityArea(float *arrValue,int &nValue)
{
    nValue = 0;
    for(int i=1;i<=10;i++)
    {
        float area = 3.14f*i*i;
        if(area>40 && area<90)
        {
            arrValue[nValue++] = area;
        }
    }
    return ;
}

int main()
{
    float fResArray[10];
    for (int i = 0; i < 10; ++i)
    {
        fResArray[i] = 0.0;
    }
    int nArrayCount = 0 ;
    OutputRotundityArea(fResArray, nArrayCount);

    std::cout << (2 == nArrayCount) << std::endl;
    std::cout << (fabs(50.24 -fResArray[0])<0.001) << std::endl;
    std::cout << (fabs(78.5 -fResArray[1]) <0.001) << std::endl;
}