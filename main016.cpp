/*
http://wikioi.com/problem/1212/
*/
#include <iostream>

using namespace std;

int gcd016(int min,int max)
{
    if(max%min == 0)
    {
        return min;
    }
    else
    {
        return gcd016(max%min,min); //Å£¶Ùµü´úÏà³ý·¨
    }
}

int main016()
{
    int A,B;
    cin >> A >> B;
    cout << gcd016(min(A,B),max(A,B));
    return 0;
}
