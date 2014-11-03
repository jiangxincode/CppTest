#include <iostream>
#include "main.h"

using namespace std;

int fun(int x)
{
    int coutnx = 0;
    while(x)
    {
        coutnx ++;
        x = x&(x-1);
    }
    return coutnx;
}
int main(int argc, char *argv[])
{
    string ch;
    do
    {
        short a[100];
        cout << sizeof(a);
        cout << "\nGo on?(n/y)";
        cin >> ch;
    }
    while(ch == "y");

    return 0;
}

