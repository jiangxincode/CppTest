/**
 * 将字符串中不同字符的个数找出
 * 描述:  找出字符串中，不同的字符的个数。
 * 输入:  输入一个字符串，'\0'作为字符串结束符。
 * 输出:  输出字符串中不同字符的个数。
 * 样例输入: 122345
 * 样例输出: 5
 *
 */
#include <iostream>
#include <string>
#include <set>

using namespace std;

int main()
{
    string str;
    set<char> setChar;
    cin >> str;

    for(string::iterator it=str.begin(); it!=str.end(); ++it)
    {
        char ch = *it;

        if(setChar.find(ch) == setChar.end())
        {
            setChar.insert(ch);
        }
    }

    cout << setChar.size();
    return 0;
}
