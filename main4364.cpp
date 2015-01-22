/**
爱因斯坦出了一道这样的数学题：有一条长阶梯，
若每步跨2阶，则最最后剩一阶，
若每步跨3 阶，则最后剩2阶，
若每步跨5阶，则最后剩4阶，
若每步跨6阶则最后剩5阶。
只有每次跨7阶，最后才正好一阶不剩。
请问这条阶梯共有多少阶？

*/

#include <stdlib.h>
#include "oj.h"

#include <iostream>

using namespace std;

// 功能：计算满足条件的楼梯的长度
// 输入： 无
// 输出：无
// 返回： 无

unsigned int  GetStairNum ()
{
	unsigned int StairNum;
	for(unsigned int i=0;;i+=7)
    {
        if(i%6==5 && i%5==4 && i%3==2 && i%2==1)
        {
            StairNum = i;
            return StairNum;
        }
    }
	return 0;
}

int main4364()
{
    cout << GetStairNum() << endl; //119
    return 0;
}
