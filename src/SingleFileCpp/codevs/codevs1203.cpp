/**
 * 1203 判断浮点数是否相等
 * 时间限制: 1 s
 * 空间限制: 128000 KB
 * 题目等级 : 青铜 Bronze
 * 题目描述 Description
 * 给出两个浮点数，请你判断这两个浮点数是否相等
 * 输入描述 Input Description
 * 输入仅一行，包含两个浮点数
 * 输出描述 Output Description
 * 输出仅一行，如果相等则输出yes，否则输出no。
 * 样例输入 Sample Input
 * 2.980000001 2.9800000000001
 * 样例输出 Sample Output
 * yes
 * 数据范围及提示 Data Size & Hint
 * 我们一般认为两个浮点数相等，当且当他们之间的误差不超过1e-8。
 */
#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    float input_one,input_two;
    cin >> input_one >> input_two;

    if(abs(input_one-input_two) <= 1e-8)
    {
        cout << "yes";
    }
    else
    {
        cout << "no";
    }

    return 0;
}
