/*

1204 寻找子串位置






 时间限制: 1 s



 空间限制: 128000 KB



 题目等级 : 青铜 Bronze

题目描述 Description


给出字符串a和字符串b，保证b是a的一个子串，请你输出b在a中第一次出现的位置。


 输入描述 Input Description


仅一行包含两个字符串a和b


输出描述 Output Description


仅一行一个整数


 样例输入 Sample Input


abcd bc


样例输出 Sample Output


2


数据范围及提示 Data Size & Hint


字符串的长度均不超过100

Pascal用户请注意：两个字符串之间可能包含多个空格

*/
#include <iostream>
#include <string>

using namespace std;

int main1204()
{
    string str_text;
    string str_query;
    cin >> str_text >> str_query;
    string::size_type pos = str_text.find(str_query);
    cout << pos+1;
    return 0;
}
