/**
 * 1201 最小数和最大数
 * 时间限制: 1 s
 * 空间限制: 128000 KB
 * 题目等级 : 青铜 Bronze
 * 题目描述 Description
 * 输入n个数，n<=100，找到其中最小的数和最大的数
 * 输入描述 Input Description
 * 第一行一个整数n
 * 接下来一行n个整数，每个整数不超过231 -1
 * 输出描述 Output Description
 * 最小和最大的数
 * 样例输入 Sample Input
 * 4
 * 1 2 3 4
 * 样例输出 Sample Output
 * 1 4
 * 数据范围及提示 Data Size & Hint
 * 无
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

    int min = *min_element(vec.begin(),vec.end());
    int max = *max_element(vec.begin(),vec.end());
    cout << min << " " << max;
    return 0;
}
