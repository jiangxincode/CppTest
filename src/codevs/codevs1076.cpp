/**
 * 1076 排序
 * 时间限制: 1 s
 * 空间限制: 128000 KB
 * 题目等级 : 白银 Silver
 * 题目描述 Description
 * 给出n和n个整数，希望你从小到大给他们排序
 * 输入描述 Input Description
 * 第一行一个正整数n
 * 第二行n个用空格隔开的整数
 * 输出描述 Output Description
 * 输出仅一行，从小到大输出n个用空格隔开的整数
 * 样例输入 Sample Input
 * 3
 * 3 1 2
 * 样例输出 Sample Output
 * 1 2 3
 * 数据范围及提示 Data Size & Hint
 * 1<=n<=100000
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int num;
    int temp;
    vector<int> vec;
    cin >> num;

    for(int i=0; i<num; i++)
    {
        cin >> temp;
        vec.push_back(temp);
    }

    sort(vec.begin(),vec.end());

    for(vector<int>::iterator it=vec.begin(); it!=vec.end(); ++it)
    {
        cout << *it << " ";
    }

    return 0;
}
