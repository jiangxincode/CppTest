/**
对1，2，3， 4， 5 这五个数任意取出两个数，列出他们的所有组合。
*/
#include <iostream>

using namespace std;

int main()
{
    for(int i=1; i<=5; i++)
    {
        for(int j=i+1; j<=5; j++)
        {
            cout << i << " " << j << endl;
        }
    }

    return 0;
}
