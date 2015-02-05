#include <iostream>
#include <string>

using namespace std;
/*
测试标准输入cin和文件结束符
测试平台：Windows
*/
int test_string_one();
int test_string_two();
int test_string_three();

int main0502()
{
    //test_string_one();
    test_string_two();
    return 0;
}
int test_string_one() //第一个程序：输入的是整数
{
    int num;

    while(cin>>num)
        cout << num << " ";

    return 0;
}
/*
输入：1 2 3 4 5 Ctrl+d Enter
输出：1 2 3 4 5
此处之所以循环停止，是因为遇到一个无效输入（Ctrl+d），而不是遇到了文件结束符。
因为在windows平台，结束符是Ctrl+z，然后按Enter。
例如输入：1 2 3 4 5 a Enter
输出仍是：1 2 3 4 5
当然如果该测试用例用于Linux下，那么由于系统的结束符是Ctrl+d，所以虽然输出一样，
但是之所以循环停止，是因为到达了文件结束，而不是得到了一个无效输入。
*/


int test_string_two() //第二个程序：输入的是字符串
{
    string word;

    while(cin>>word)
        cout << word << " ";

    return 0;
}
/*
输入：hello world Ctrl+z 回车
输出：hello world
此处之所以循环停止，是因为遇到一个文件结束符。
因为在windows平台，结束符是Ctrl+z，然后按Enter。
*/

