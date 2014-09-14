#include <iostream>

using namespace std;

int main013()
{
    int N,M=1;
    int numerator,denominator;
    int sum;
    cin >> N;
    for(;sum<N;M++)
    {
        sum += M;
    }
    M --;//注意两者的顺序
    sum -= M;
    if(M%2 == 1)
    {
        denominator = N-sum;
        numerator = (M+1)-denominator;
    }
    else
    {
        numerator = N-sum;
        denominator = (M+1)-numerator;
    }
    cout << numerator << "/" << denominator;
    return 0;
}
