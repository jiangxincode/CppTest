/**
 * 字符串最后一个单词的长度
 * https://www.nowcoder.com/practice/8c949ea5f36f422594b306a2300315da
 * 描述:  计算字符串最后一个单词的长度，单词以空格隔开。
 * 输入:一行字符串，长度小于128。
 * 输出:整数N，最后一个单词的长度。
 * 样例输入: hello world
 * 样例输出: 5
 */
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <cstdio>
#include <cstring>

using namespace std;

int main4418_1() {
    string strInput;
    getline(cin, strInput);
    string strInputReverse = strInput;  //warning
    reverse_copy(strInput.begin(), strInput.end(), strInputReverse.begin());
    istringstream iss(strInputReverse);
    string word;
    iss >> word;
    cout << word.length();
    return 0;
}

int main() {
    char s[1024];
    while (~(scanf("%s", s)));
    printf("%d\n", strlen(s));
    return 0;
}
