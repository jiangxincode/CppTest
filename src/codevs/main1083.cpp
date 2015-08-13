/**
 *
1083 Cantor表
 1999年NOIP全国联赛普及组





 时间限制: 1 s



 空间限制: 128000 KB



 题目等级 : 白银 Silver

题目描述 Description


现代数学的著名证明之一是Georg Cantor证明了有理数是可枚举的。他是用下面这一张表来证明这一命题的： 1/1 1/2 1/3 1/4 1/5 … 2/1 2/2 2/3 2/4 … 3/1 3/2 3/3 … 4/1 4/2 … 5/1 … … 我们以Z字形给上表的每一项编号。第一项是1/1，然后是1/2，2/1，3/1，2/2，…


输入描述 Input Description


整数N（1≤N≤10000000）


 输出描述 Output Description


表中的第N项


 样例输入 Sample Input


7


样例输出 Sample Output


1/4


数据范围及提示 Data Size & Hint


见描述
 *
 */
#include <iostream>

using namespace std;

int main1083()
{
    int N,M=1;
    int numerator,denominator;
    int sum = 0;
    cin >> N;

    for(; sum<N; M++)
    {
        sum += M;
    }

    M --;//注意两者的顺序
    sum -= M;

    if(M%2 == 1)
    {
        denominator = N-sum;
        numerator = (M+1)-denominator;
    }
    else
    {
        numerator = N-sum;
        denominator = (M+1)-numerator;
    }

    cout << numerator << "/" << denominator;
    return 0;
}
