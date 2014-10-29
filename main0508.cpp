#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

/**
 * 判断一个长整数为回文数
 * 测试用例：
 * input output
 * 12321 1
 * 12345 0
 */
bool palindrome1(long num)
{
    long num_reverse,temp;
    temp=num;
    num_reverse=0;

    while(temp)
    {
        temp=num_reverse*10+temp%10;
        temp/=10;
    }

    return(num==num_reverse);
}

int palindrome2(long num)
{
    string str = to_string(num);
    string str_reverse = str;
    reverse_copy(str.begin(),str.end(),str_reverse.begin());
    if(str == str_reverse)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    return 0;
}
/**
 * 判断字符串是否为回文数字
 * 最好使用string，不用考虑最后的'\0'
*/
int palindrome(const char *str)
{
    string str_origin(str);
    string str_reverse(str_origin);
    reverse_copy(str_origin.begin(),str_origin.end(),str_reverse.begin());
    if(str_origin == str_reverse)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


int main0508()
{
    return 0;
}

