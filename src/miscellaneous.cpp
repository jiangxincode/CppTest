﻿#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

/**
 *  求两个整数之和，要求在函数体内不得使用+、-、*、/四则运算符号
 */
int plus_without_operator(int i_num1, int i_num2)
{
    while(i_num2 !=0)
    {
        int temp = i_num1; //先将各bit位相加，不计进位，这一步可以用m^n实现
        i_num1 = i_num1 ^ i_num2;
        i_num2 = (temp & i_num2) << 1; //可得到进位后要加的1的位置
    }
    return i_num1;
}

/**
 * 判断一个长整数为回文数
 * 测试用例：
 * input output
 * 12321 1
 * 12345 0
 */
int palindrome(long num)
{
    long num_reverse,temp;
    temp=num;
    num_reverse=0;

    while(temp)
    {
        num_reverse=num_reverse*10+temp%10;
        temp/=10;
    }

    return(num==num_reverse);
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
