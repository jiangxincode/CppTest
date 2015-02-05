/**
验证尼科彻斯定理，即：任何一个整数m的立方都可以写成m个连续奇数之和。
例如：
1^3=1
2^3=3+5
3^3=7+9+11
4^3=13+15+17+19

输入:
整数m(取值范围：1～100)

输出:
尼科彻斯定理成立，输出m个连续奇数(格式：“7+9+11”)；否则输出-1

样例输入: 3

样例输出: 7+9+11
*/

#include <iostream>

using namespace std;

int main4277()
{
    int m;
    cin >> m;
    int sum = 0;

    for(int i=m*m-m+1; i<=m*m+m-1; i+=2)
    {
        sum += i;
    }

    if(sum == m*m*m)
    {
        for(int i=m*m-m+1; i<=m*m+m-1; i+=2)
        {
            if(i==m*m+m-1)
            {
                cout << i;
            }
            else
            {
                cout << i << "+";
            }
        }
    }
    else
    {
        cout << -1;
    }

    return 0;
}
