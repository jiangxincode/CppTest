/*
http://wikioi.com/problem/1160/
*/
#include <iostream>

using namespace std;

int main014()
{
    int n;
    cin >> n;
    int arr[n][n];

    if(n == 1)
    {
        arr[0][0] = 1;
        cout << 1 << endl;
        cout << 1;
        return 0;
    }

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            arr[i][j] = 0;
        }
    }

    int seq = 1;
    arr[n/2][n/2] = 1;

    for(int m=3; m<=n; m+=2)
    {
        int i=n/2+(m-1)/2-1;
        int j=n/2+(m-1)/2;

        for(; i>n/2-(m-1)/2; i--)
        {
            arr[i][j] = ++seq;
        }

        for(; j>n/2-(m-1)/2; j--)
        {
            arr[i][j] = ++seq;
        }

        for(; i<n/2+(m-1)/2; i++)
        {
            arr[i][j] = ++seq;
        }

        for(; j<=n/2+(m-1)/2; j++)
        {
            arr[i][j] = ++seq;
        }
    }

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            cout << arr[i][j] << " ";
        }

        cout << endl;
    }

    int result = 0;

    for(int i=0; i<n; i++)
    {
        result += arr[i][i];
        result += arr[i][n-1-i];
    }

    result -= 1;
    cout << result;
    return 0;
}
