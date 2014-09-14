/*
判断回文数，是返回1，不是返回0
input 34543
output 1
*/
#include <iostream>

using namespace std;

int main0518()
{
    int input;
    int rinput = 0;
    cin >> input;

    int temp = input;
    while(temp != 0)
    {
        rinput = 10*rinput+(temp%10);
        temp /= 10;
    }
    if(input == rinput)
    {
        cout << 1;
    }
    else
    {
        cout << 0;
    }
    return 0;
}
