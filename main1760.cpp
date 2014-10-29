#include <cstdio>
#include <iostream>
#include "LinkedSet.h"

using namespace std;

int main6_15()
{
    LinkedSet<int> myset;

    for(int i=1; i<=100; i++)
    {
        if(!(myset.addMember(i)))
        {
            cout << "Allocate error!" <<endl;
        }
    }

    myset.display();
    SetNode<int> *first = myset.getFirst();
    SetNode<int> *temp;
    temp = myset.Search(first,first,0);
    cout << temp;
    return 0;
}
