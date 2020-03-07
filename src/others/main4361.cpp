 /**
 * 求子数组的最大和
 * 输入一个整形数组。数组中连续的一个或多个整数组成一个子数组，每个子数组都有一个和。求所有子数组的和的最大值。
 * 接口
 * Int GetSubArraySum（Int* pIntArray，Int nCount）；
 * 规格
 * 要求时间复杂度为O(n)
 * 举例
 * 例如输入的数组为1, -2, 3, 10, -4, 7, 2, -5，和最大的子数组为3, 10, -4, 7, 2，
 * 因此输出为该子数组的和18
 *
 */
#include <cstdlib>
#include <iostream>

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

int main() {
    {
        int aNums[] = {1,2,3};
        std::cout << (6 == GetSubArraySum(aNums, sizeof(aNums)/ sizeof(int))) << std::endl;
    }

    {
        int aNums[] = {-2,-4,0,-6,-7,-1};
        std::cout << (0 == GetSubArraySum(aNums, sizeof(aNums)/ sizeof(int))) << std::endl;
    }

    {
        int aNums[] = {-2,-3,4,6,-6,-2};
        std::cout << (10 == GetSubArraySum(aNums, sizeof(aNums)/ sizeof(int))) << std::endl;
    }

    {
        int aNums[] = {-2,-3,4,6,-6,-2,-7,5,7};
        std::cout << (12 == GetSubArraySum(aNums, sizeof(aNums)/ sizeof(int))) << std::endl;
    }

    {
        int aNums[] = {-2,-3,4,6,-6,10,-8,-7,5,7};
        std::cout << (14 == GetSubArraySum(aNums, sizeof(aNums)/ sizeof(int))) << std::endl;
    }
}
