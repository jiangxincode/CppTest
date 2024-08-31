/**
 * 删除字符串中出现次数最少的字符
 * 描述:
 * 实现删除字符串中出现次数最少的字符，若多个字符出现次数一样，则都删除。
 * 输出删除这些单词后的字符串，字符串中其它字符保持原来的顺序。
 * 输入:
 * 字符串只包含小写英文字母, 不考虑非法输入，输入的字符串长度小于等于20个字节。
 * 输出:
 * 删除字符串中出现次数最少的字符后的字符串。
 * 样例输入:
 * abcdd
 * 样例输出:
 * dd
 *
 */
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <climits>

using namespace std;

int main()
{
    map<char, int> char2amount;
    string input;
    cin >> input;

    for(string::iterator it=input.begin();it!=input.end();++it)
    {
        if(char2amount.find(*it) == char2amount.end())
        {
            pair<char,int> temp(*it,1);
            char2amount.insert(temp);
        }
        else
        {
            char2amount[*it]++;
        }
    }

    int min_amount = INT_MAX;
    for(map<char,int>::iterator it=char2amount.begin();it!=char2amount.end();++it)
    {
        if((*it).second < min_amount)
        {
            min_amount = (*it).second;
        }
    }

    string result;
    for(string::iterator it=input.begin();it!=input.end();++it)
    {
        if(char2amount[*it] == min_amount)
        {
            continue;
        }
        else
        {
            result.append(string(1,*it));
        }
    }

    cout << result;

    return 0;
}
