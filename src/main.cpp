﻿#include <iostream>
#include "main.h"

using namespace std;

/** \cond */
int main(int argc, char *argv[])
{
    string ch;

    do
    {
        fflush(stdin); //清空输入流
        main1730();
        cout << "\nGo on?(n/y)";
        cin >> ch;
    }
    while(ch == "y");

    return 0;
}
/** \endcond */
