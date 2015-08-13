/**
 * 1206 保留两位小数
 * 时间限制: 1 s
 * 空间限制: 128000 KB
 * 题目等级 : 青铜 Bronze
 * 题目描述 Description
 * 保留两位小数输出一个浮点数。
 * 输入描述 Input Description
 * 一个浮点数。double范围内
 * 输出描述 Output Description
 * 保留两位小数输出
 * 样例输入 Sample Input
 * 11
 * 样例输出 Sample Output
 * 11.00
 * 数据范围及提示 Data Size & Hint
 * C++用 printf("%.2lf",a);
 * Pascal用 writeln(a:0:2);
 * C++和Pascal用户都请使用double类型，不要使用float,real,extended类型。
 */
#include <iostream>
#include <iomanip>

using namespace std;

int main1206()
{
    double input;
    cin >> input;
    cout << fixed << setprecision(2) << input << setprecision(6);
    return 0;
}
