#include <iostream>
//#include <cstdlib>
#include "heap.h"

using namespace std;

bool compmin(int a,int b)
{
    return (a < b)?true:false;
}

bool compmax(int a,int b)
{
    return (b < a)?true:false;
}

int main001()
{
    const int MAXNUM = 20;
    int test[MAXNUM];

    for(int i=0; i<MAXNUM; i++)
    {
        test[i] = rand()%100;
    }

    for(int i=0; i<MAXNUM; i++)
    {
        cout << test[i] << " ";
    }

    cout << endl;
    heap h1(test, MAXNUM, compmax);
    h1.print_heap();

    for(int i=0; i<20; i++)
    {
        h1.push(rand()%100);
        h1.print_heap();
    }

    h1.sort();
    h1.print_heap();
    return 0;
}
