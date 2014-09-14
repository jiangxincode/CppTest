#include <iostream>

using namespace std;

int main0500() //求两个整数之和，要求在函数体内不得使用+、-、*、/四则运算符号
{
    int i_num1,i_num2; // The numbers that user inputs
    cout << "Input two int nums like this: 34 56 Enter" << endl;
    cin >> i_num1 >> i_num2;
    while(i_num2 !=0 )
    {
        int temp = i_num1; //先将各bit位相加，不计进位，这一步可以用m^n实现
        i_num1 = i_num1 ^ i_num2;
        i_num2 = (temp & i_num2) << 1; //可得到进位后要加的1的位置
    }
    cout << "The result of is: " << i_num1 << endl;
    return 0;
}
