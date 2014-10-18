/*
编写一个函数，判断其int型参数值是否是回文数
*/

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main2584()
{
    int i_num;
    cout << "Input a integer: ";
    cin >> i_num;
    string str_num = to_string(i_num);
    string str_num_reverse = str_num;
    auto str_num_begin = str_num.begin();
    auto str_num_end = str_num.end();
    auto str_num_reverse_begin = str_num_reverse.begin();
    reverse_copy(str_num_begin,str_num_end,str_num_reverse_begin);

    if(str_num == str_num_reverse)
    {
        cout << "The num: " << i_num << " is a palindrome number";
    }
    else
    {
        cout << "The num: " << i_num << " isn't a palindrome number";
    }
    return 0;
}
