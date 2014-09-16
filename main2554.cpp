#include <iostream>

using namespace std;

int fib1(int n)
{
    if(n==1||n==2)
        return 1;
    return fib1(n-1)+fib1(n-2);
}
int fib2(int n)
{
    int small = 1;
    int big = 1;
    int result = 1;
    while(n>2)
    {
        result = small + big;
        small = big;
        big = result;
        n--;
    }
    return result;

}
int main2554()
{
    int num;
    cout << "Input the num: ";
    cin >> num;
    cout << "Method one: " << fib1(num) << endl;
    cout << "Method two: " << fib2(num) << endl;
    return 0;
}
