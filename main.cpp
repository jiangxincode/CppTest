#include <iostream>
#include "main.h"

using namespace std;

int main(int argc, char *argv[])
{
    string ch;
    do
    {
        main0542();
        cout << "\nGo on?(n/y)";
        cin >> ch;
    }
    while(ch == "y");

    return 0;
}

