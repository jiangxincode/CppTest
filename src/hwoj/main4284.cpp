/**
 * 数字基root
 * 描述:  求整数的Root:给定正整数,求每位数字之和;如果和不是一位数,则重复;
 * 输入:
 * 输入任意一个或多个整数
 * 输出:
 * 输出各位数字之和,直到和为个位数为止(输入异常,则返回-1)
 * 多行，每行对应一个输入数据的结果。
 * 样例输入:
 * 25
 * 865
 * 样例输出:
 * 7
 * 1
 *
 */
#include <iostream>
#include <vector>

using namespace std;


int main()
{
    int input;

    while(cin >> input)
    {
        while(input >= 10)
        {
            vector<int> vec;
            int temp = input;
            input = 0;

            while(temp)
            {
                vec.push_back(temp%10);
                temp /= 10;
            }

            for(vector<int>::iterator it=vec.begin(); it!=vec.end(); ++it)
            {
                input += *it;
            }
        }

        cout << input << endl;
    }

    return -1;
}
