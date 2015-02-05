#include <stdlib.h>
#include <string.h>
#include "oj.h"

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

    for(int i=1; i<=10; i++)
    {
        float area = 3.14*i*i;

        if(area>40 && area<90)
        {
            arrValue[nValue++] = area;
        }
    }

    return ;
}

int main4360()
{
    float fResArray[10];

    for(int i = 0; i < 10; ++i)
    {
        fResArray[i] = 0.0;
    }

    int nArrayCount = 0 ;
    OutputRotundityArea(fResArray, nArrayCount);
    cout << nArrayCount << " " << fResArray[0] << " " << fResArray[1] << endl;
    return 0;
// 	CPPUNIT_ASSERT(2 == nArrayCount);
// 	CPPUNIT_ASSERT(fabs(50.24 -fResArray[0])<0.001);
//	CPPUNIT_ASSERT(fabs(78.5 -fResArray[1]) <0.001);
}
