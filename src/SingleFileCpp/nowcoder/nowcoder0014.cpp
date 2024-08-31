/**
 * 图片整理
 * https://www.nowcoder.com/practice/2de4127fda5e46858aa85d254af43941
 * 描述:
 * Lily上课时使用字母数字图片教小朋友们学习英语单词，
 * 每次都需要把这些图片按照大小（ASCII码值从小到大）排列收好。请大家给Lily帮忙，通过C语言解决。
 * 输入:
 * Lily使用的图片包括"A"到"Z"、"a"到"z"、"0"到"9"。输入字母或数字个数不超过1024。
 * 输出:
 * Lily的所有图片按照从小到大的顺序输出
 * 样例输入: Ihave1nose2hands10fingers
 * 样例输出: 0112Iaadeeefghhinnnorsssv

 */
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    string input;
    while (cin >> input) {
        stable_sort(input.begin(),input.end());
        cout << input << endl;
    }
    return 0;
}