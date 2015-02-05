/**
描述:
输入一个10进制数字，请计算该数字对应二进制中0的个数，注意左数第一个1之前的所有0都不需要计算。
不需要考虑负数的情况。

输入:  要计算的十进制非负数

输出:  二进制中第一个1之后0 的个数

样例输入: 2

样例输出: 1

*/
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main4248()
{
    unsigned int input;
    unsigned int result = 0;
    string str = "";
    cin >> input;

    while(input != 0)
    {
        str += '0'+input%2;
        input /= 2;
    }

    string strReverse = str;
    reverse_copy(str.begin(),str.end(),strReverse.begin());

    for(string::iterator it=strReverse.begin(); it!=strReverse.end(); ++it)
    {
        if((*it) == '1')
        {
            for(string::iterator temp=it; temp!=strReverse.end(); ++temp)
            {
                if((*temp) == '0')
                {
                    result++;
                }
            }

            break ;
        }
    }

    cout << result;
    return 0;
}
