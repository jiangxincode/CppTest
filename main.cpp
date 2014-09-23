#include <iostream>
#include "jiangxin.h"

using namespace std;

int main(int argc, char *argv[])
{
    string ch;
    do{
        main0539();
        cout << "\nGo on?(n/y)";
        cin >> ch;
    }while(ch == "y");

    return 0;
}

