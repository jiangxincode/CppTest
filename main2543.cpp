/*
设有一头小母牛，从出生第三年起每两年生一头小母牛，
出生的每头小母牛都按此规律生小牛，第N年时有几头母牛？
给出递归和循环两种实现。
*/
#include <iostream>
#include <cmath>

using namespace std;

int calc_num1(int year)
{
    return pow(2,((year-1)/2));
}
int calc_num2(int year)
{
    if(year==1 || year==2)
    {
        return 1;
    }
    else
    {
        return 2*calc_num2(year-2);
    }
}
int main2543()
{
    int year = 10;
    for(int i=1;i<=year;i++)
    {
        cout << "Method 1: The number is: " << calc_num1(i) << " in year " << i << endl;
        cout << "Method 2: The number is: " << calc_num2(i) << " in year " << i << endl;
    }
    return 0;
}
