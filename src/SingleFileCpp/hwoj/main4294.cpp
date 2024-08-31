/**
 * 整数分隔
 * 描述:
 * 一个整数总可以拆分为2的幂的和，例如：
 * 7=1+2+4
 * 7=1+2+2+2
 * 7=1+1+1+4
 * 7=1+1+1+2+2
 * 7=1+1+1+1+1+2
 * 7=1+1+1+1+1+1+1
 * 总共有六种不同的拆分方式。
 * 再比如：4可以拆分成：4 = 4，4 = 1 + 1 + 1 + 1，4 = 2 + 2，4=1+1+2。
 * 用f(n)表示n的不同拆分的种数，例如f(7)=6.
 * 要求编写程序，读入n(不超过1000000)，输出f(n)%1000000000。
 * 输入:
 * 每组输入包括一个整数：N(1<=N<=1000000)。
 * 输出:
 * 对于每组数据，输出f(n)%1000000000。
 * 输出有多行，每行一个结果。
 * 输入数据如果超出范围，输出-1。
 * 样例输入:
 * 7  4
 * 样例输出:
 * 6
 * 4
 */
/**
 * 思路：
 * i 为 奇数时，拆分跟前面的i-1是一样的，自己写几组就知道了，不用多说。
 * 关键是 i 为偶数时：当拆分中不含1时，则拆分情况最小分到2，则拆分情况跟i/2是一一对应的；
 * 当拆分中含有1时，先把这个1拿出来，剩下的i-1进行拆分，情况跟i-1的拆分时一一对应的；
 * 而这两种拆分情况是互不相交的（因为一种没1，一种有1），则加起来就是 i 为偶数时的拆分情况。
*/

#include <iostream>

using namespace std;

int searchArray[1000002]={0};

int main()
{
    int input = 0, i;
    searchArray[0] = 1, searchArray[1] = 1;

    for(i=1; i<=500000; i++)
    {
        searchArray[2 * i] = (searchArray[2 * i - 2] + searchArray[i]) % 1000000000;
        searchArray[2 * i + 1] = searchArray[2 * i];
    }
    while(cin >> input)
    {
        if((input >= 1) && (input <= 1000000))
        {
            cout << searchArray[input] << endl;
        }
        else
        {
            cout << -1 << endl;
        }
    }
    return 0;
}


/* 该方法计算量过大导致时间超限
long split(long n)
{
    if(n == 1)
    {
        return 1;
    }

    if(n%2 == 1)
    {
        return split(n-1);
    }
    else
    {
        return split(n/2) + split(n-1);
    }
}

int main4294()
{
    long input;

    while(cin >> input)
    {
        if((input > 1000000) || (input < 1))
        {
            cout << -1 << endl;
            continue;
        }

        cout << split(input) % 1000000000 << endl;
    }
    return 0;
}
*/

