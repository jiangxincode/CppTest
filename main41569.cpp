/**
描述:  输出7有关数字的个数，包括7的倍数，还有包含7的数字（如17，27，37...70，71，72，73...）的个数
输入:  一个正整数N。(N不大于30000)
输出:  不大于N的与7有关的数字个数，例如输入20，与7有关的数字包括7,14,17.
样例输入: 20
样例输出: 3
*/

#include <iostream>
#include <vector>

using namespace std;

bool isProper(unsigned int n)
{
    if(n%7 == 0)
    {
        return true;
    }
    vector<unsigned int> vec;
    while(n != 0)
    {
        vec.push_back(n%10);
        n /= 10;
    }

    for(vector<unsigned int>::iterator it=vec.begin();it!=vec.end();it++)
    {
        if(*it == 7)
        {
            return true;
        }
    }
    return false;
}
int main41569()
{
    unsigned int input;
    unsigned int result = 0;
    cin >> input;
    for(unsigned int i=1;i<=input;i++)
    {
        if(isProper(i))
        {
            result++;
        }
    }
    cout << result;
    return 0;
}
