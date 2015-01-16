#include <stdlib.h>
#include <iostream>

using namespace std;

#include "oj.h"


unsigned int  GetLastThreeNumOfResult(unsigned int  m, unsigned int  n)
{

    unsigned int lastThreeNum = m % 1000;
    unsigned int result = 1;

    for(unsigned int i=0;i<n;i++)
    {
        result = (result % 1000) * lastThreeNum;
    }

    return result % 1000;
}

int main4357()
{
    cout << GetLastThreeNumOfResult(5,3) << endl;
    cout << GetLastThreeNumOfResult(34567,9) << endl;
    cout << GetLastThreeNumOfResult(4562,2) << endl;
    return 0;
}
