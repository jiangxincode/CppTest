
#include "OJ.h"

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
    if(InputNum <= 0 || pInputInteger == NULL) //warning
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

int main4368()
{
    int aInputInteger[] = {1, 2, 3, 4};
    int iMaxValue, iMaxNum, iMinValue, iMinNum;
    OutputMaxAndMin(aInputInteger, 4, &iMaxValue, &iMaxNum, &iMinValue, &iMinNum);
    cout << iMaxValue << " " << iMaxNum << " " << iMinValue << " " << iMinNum << endl;
    int aInputInteger1[] = {1, 2, 1, 4,4,5,63,64,4,64,5};
    OutputMaxAndMin(aInputInteger1, 11, &iMaxValue, &iMaxNum, &iMinValue, &iMinNum);
    cout << iMaxValue << " " << iMaxNum << " " << iMinValue << " " << iMinNum << endl;
//	CPPUNIT_ASSERT(iMaxValue  == 4);
//	CPPUNIT_ASSERT(iMaxNum == 1);
//	CPPUNIT_ASSERT(iMinValue == 1);
//	CPPUNIT_ASSERT(iMinNum == 1);
    return 0;
}


