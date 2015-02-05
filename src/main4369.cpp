#include <stdlib.h>
#include "oj.h"

// 功能：判断输入 nValue 是否为水仙花数
// 输入： nValue为正整数
// 输出：无
// 返回：如果输入为水仙花数，返回1，否则返回0

/**
水仙花数又称阿姆斯特朗数。
水仙花数是指一个n 位数( n≥3 )，它的每个位上的数字的n 次幂之和等于它本身。
（例如：1^3 + 5^3 + 3^3 = 153）
求输入的数字是否为水仙花数
*/

#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

unsigned int IsDaffodilNum(unsigned int  nValue)
{
    vector<unsigned int> vec;
    unsigned int temp = nValue;

    while(temp > 0)
    {
        unsigned int bit = temp%10;
        vec.push_back(bit);
        temp /= 10;
    }

    unsigned int sum = 0;

    for(vector<unsigned int>::iterator it=vec.begin(); it!=vec.end(); ++it)
    {
        unsigned int temp = *it;
        unsigned int mul = 1;

        for(unsigned int i=0; i<vec.size(); i++)
        {
            mul *= temp;
        }

        sum += mul;
    }

    if(sum == nValue)
    {
        return 1;
    }

    return 0;
}

int main4369()
{
    cout << IsDaffodilNum(153) << endl;
    cout << IsDaffodilNum(151) << endl;
    return 0;
}
