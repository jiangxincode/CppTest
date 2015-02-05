//unsolved 一个测试用例未通过
#include "OJ.h"

#include <iostream>

using namespace std;

long int fact(int n)
{
    if(n==0||n==1)
        return 1;
    else
        return n*fact(n-1);
}

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
    int s = 1;

    for(int i=1; i<=InputNum; i++)
    {
        s *= i;
        *NumResult = *NumResult+1/(double)s;
    }

    return ;
}

int main4367()
{
    int InputNum = 5;
    double NumResult = 0;
    GetResult(InputNum, &NumResult);
    cout << NumResult << endl;
    return 0;
//	CPPUNIT_ASSERT(1.71667 > NumResult && 1.71666 < NumResult);
}
