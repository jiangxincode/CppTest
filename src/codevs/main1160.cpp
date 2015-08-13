/*

1160 蛇形矩阵






 时间限制: 1 s



 空间限制: 128000 KB



 题目等级 : 白银 Silver


题目描述 Description


小明玩一个数字游戏，取个n行n列数字矩阵（其中n为不超过100的奇数），数字的填补方法为：在矩阵中心从1开始以逆时针方向绕行，逐圈扩大，直到n行n列填满数字，请输出该n行n列正方形矩阵以及其的对角线数字之和.


输入描述 Input Description


n（即n行n列）


 输出描述 Output Description


n+1行，n行为组成的矩阵，最后一行为对角线数字之和


 样例输入 Sample Input


3



样例输出 Sample Output


5 4 3
6 1 2
7 8 9
25



数据范围及提示 Data Size & Hint
*/
#include <iostream>

using namespace std;

int main1160()
{
    int n;
    cin >> n;
    int arr[n][n];

    if(n == 1)
    {
        arr[0][0] = 1;
        cout << 1 << endl;
        cout << 1;
        return 0;
    }

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            arr[i][j] = 0;
        }
    }

    int seq = 1;
    arr[n/2][n/2] = 1;

    for(int m=3; m<=n; m+=2)
    {
        int i=n/2+(m-1)/2-1;
        int j=n/2+(m-1)/2;

        for(; i>n/2-(m-1)/2; i--)
        {
            arr[i][j] = ++seq;
        }

        for(; j>n/2-(m-1)/2; j--)
        {
            arr[i][j] = ++seq;
        }

        for(; i<n/2+(m-1)/2; i++)
        {
            arr[i][j] = ++seq;
        }

        for(; j<=n/2+(m-1)/2; j++)
        {
            arr[i][j] = ++seq;
        }
    }

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            cout << arr[i][j] << " ";
        }

        cout << endl;
    }

    int result = 0;

    for(int i=0; i<n; i++)
    {
        result += arr[i][i];
        result += arr[i][n-1-i];
    }

    result -= 1;
    cout << result;
    return 0;
}
