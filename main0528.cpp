/*
2014 ����һ��
��[1,n]�б�3��5��������֮��
*/
#include <iostream>

using namespace std;

int main0528()
{
    int n;
    cin >> n;
    int sum1=0,sum2=0;
    sum1 = (n/3)*(3+(n/3)*3)/2;
    sum2 = (n/5)*(5+(n/5)*5)/2;
    cout << sum1+sum2;
    return 0;
}
