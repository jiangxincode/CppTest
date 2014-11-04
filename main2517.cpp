#include <iostream>

using namespace std;

int main2517()
{
    int i,j,k;

    for(i=0; i<=3; i++)
    {
        for(j=0; j<=2-i; j++)
            cout << " ";

        for(k=0; k<=2*i; k++)
            cout << "*";

        cout << endl;
    }

    for(i=0; i<=2; i++)
    {
        for(j=0; j<=i; j++)
            cout << " ";

        for(k=0; k<=4-2*i; k++)
            cout << "*";

        cout << endl;
    }

    return 0;
}
