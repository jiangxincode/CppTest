/**
 * 查找非素数
 * 描述:  查找出所有大于1小于等于整数m（m < 100）的非素数。
 * 例如，若输入:17，则应输出:4 6 8 9 10 12 14 15 16。
 * 输入:  输入一个大于1小于100的整数，如 17。
 * 输出:  输出所有查找到的非素数。
 * 样例输入: 17
 * 样例输出: 4 6 8 9 10 12 14 15 16
 *
 */
#include <iostream>
using namespace std;
int prime(int n)
{
    int flag = 0,i;

    if(n <= 1)
    {
        return 0;
    }

    for(i=2; i<n; i++)
    {
        if((n%i)==0)
            flag++;
    }

    if(flag == 0)
        return 1;
    else
        return 0;
}

int main()
{
    int input;
    cin >> input;

    for(int i=2; i<=input; i++)
    {
        if(!prime(i))
        {
            cout << i << " ";
        }
    }

    return 0;
}
