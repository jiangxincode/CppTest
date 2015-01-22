/**
描述:  输入2个数字，最后输出2个数字的最大公约数
输入:  2个整数
输出:  输出数字1和2的最大公约数
样例输入: 2 3
样例输出: 1
*/
#include <iostream>

using namespace std;


int gcd1(int min,int max)
{
    if(max%min == 0)
    {
        return min;
    }
    else
    {
        return gcd1(max%min,min); //牛顿迭代相除法
    }
}

int main4257()
{
    int num1,num2,result;
    cin >> num1 >> num2;
    if(num1 < num2)
    {
        result = gcd1(num1,num2);
    }
    else
    {
        result = gcd1(num2,num1);
    }
    cout << result;
    return 0;
}
