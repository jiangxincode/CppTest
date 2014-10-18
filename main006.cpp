/*
http://wikioi.com/problem/1203/
*/
#include <iostream>
#include <cmath>

using namespace std;

int main006()
{
    float input_one,input_two;
    cin >> input_one >> input_two;

    if(abs(input_one-input_two) <= 1e-8)
    {
        cout << "yes";
    }
    else
    {
        cout << "no";
    }

    return 0;
}
