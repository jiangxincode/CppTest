/**
 * 1202 求和
 * 时间限制: 1 s
 * 空间限制: 128000 KB
 * 题目等级 : 青铜 Bronze
 * 题目描述 Description
 * 求n个数的和
 * 输入描述 Input Description
 * 第一行一个整数n
 * 接下来一行n个整数
 * 输出描述 Output Description
 * 所有数的和
 * 样例输入 Sample Input
 * 4
 * 1 2 3 4
 * 样例输出 Sample Output
 * 10
 * 数据范围及提示 Data Size & Hint
 * n<=100
 * 所有数的和<=231-1
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int input_num;
    int input_temp;
    vector<int> vec;
    cin >> input_num;

    for(int i=0; i<input_num; i++)
    {
        cin >> input_temp;
        vec.insert(vec.end(),input_temp);
    }

    //int sum = accumulate(vec.begin(),vec.end(),0);
    vector<int>::iterator it; //注意此处it的声明方法
    int sum = 0;

    for(it=vec.begin(); it!=vec.end(); ++it)
    {
        sum += *it;
    }

    cout << sum;
    return 0;
}
