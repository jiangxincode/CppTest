#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "oj.h"

#include <iostream>
using namespace std;

/*
功能:

输入:pIntArray:数组,nCout:数组长度

输出:

返回:返回最大值

*/

int GetSubArraySum(int* pIntArray, int nCount)
{
    /*在这里实现功能*/
    int maxSum = INT_MIN;
    int i;

    for(i=0; pIntArray[i]<=0; i++)
    {
        if(pIntArray[i] > maxSum)
        {
            maxSum = pIntArray[i];
        }
    }

    if(i == nCount) //全部为非正值，取其中的最大值
    {
        return maxSum;
    }

    //存在某个正值
    //如果只需要结果，不需要确定对应的子数列的话不需要定义索引值
    //int startIndex;
    //int endIndex1;
    //int endIndex2;
    int sumEnd1 = pIntArray[i];
    int sumEnd2 = pIntArray[i];

    for(i++; i<nCount; i++) //warning
    {
        if(pIntArray[i]>=0 && sumEnd2+pIntArray[i]>=sumEnd1)
        {
            //endIndex2 = i;
            //endIndex1 = i;
            sumEnd2 += pIntArray[i];
            sumEnd1 = sumEnd2;
            if(sumEnd1 > maxSum)
            {
                maxSum = sumEnd1;
            }
        }
        else if(pIntArray[i]>=0 && sumEnd2+pIntArray[i]<sumEnd1)
        {
            //endIndex2 = i;
            sumEnd2 += pIntArray[i];
        }
        else if(pIntArray[i]<0 && sumEnd2+pIntArray[i]>=0)
        {
            //endIndex2 = i;
            sumEnd2 += pIntArray[i];
        }
        else if(pIntArray[i]<0 && sumEnd2+pIntArray[i]<0)
        {
            if(sumEnd1 > maxSum)
            {
                maxSum = sumEnd1;
            }

            for(; i<nCount; i++)
            {
                if(pIntArray[i] > 0)
                {
                    //startIndex = i;
                    //endIndex1 = i;
                    //endIndex1 = i;
                    sumEnd1 = pIntArray[i];
                    sumEnd2 = pIntArray[i];
                    break;
                }
            }
        }
    }

    return maxSum;
}

int main4361()
{
    int aNums1[] = {1,2,3};
    cout << GetSubArraySum(aNums1,3) << endl; //6

    int aNums2[] = {-2,-4,0,-6,-7,-1};
    cout << GetSubArraySum(aNums2,6) << endl;  //0

    int aNums3[] = {-2,-3,4,6,-6,-2};
    cout << GetSubArraySum(aNums3,6) << endl;  //10

    int aNums4[] = {-2,-3,4,6,-6,-2,-7,5,7};
    cout << GetSubArraySum(aNums4,9) << endl;  //12

    int aNums5[] = {-2,-3,4,6,-6,10,-8,-7,5,7};
    cout << GetSubArraySum(aNums5,10) << endl;  //14

    return 0;
}
