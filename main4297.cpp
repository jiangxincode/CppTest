/**
描述:  输入一个五位以内（包括5位）的正整数，
（1）判断它是一个几位数；
（2）逆序输出其各位数字。
输入:  多组数据，每组一行
输出:  对应一行输出
样例输入: 56439
样例输出: 5 93465

*/
#include <iostream>

using namespace std;

int main4297()
{
    unsigned int num;
    cin >> num;
    unsigned int num_reverse = 0, bit = 0;

    while(num)
    {
        num_reverse = num_reverse*10 + num%10;
        num /= 10;
        bit++;
    }
    cout << bit << " " << num_reverse;
    return 0;

}
