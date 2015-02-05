/*
http://wikioi.com/problem/1430/
*/
#include <iostream>

using namespace std;

int main017()
{
    int input;
    cin >> input;
    int i;

    for(i=2; i*i<=input; i++)
    {
        if(input%i==0)
        {
            break;
        }
    }

    if((i*i>input) && (input>2))
    {
        cout << "\\t";
        return 0;
    }

    cout << "\\n";
    return 0;
}
