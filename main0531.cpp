/*
给定一些硬币，求给定金额下，最少硬币的组合
*/

#include <iostream>
#include <limits>
#include <cstdlib>
#include <cstring>

using namespace std;

void multiPacket(int cost,int a[],int Volume,int weight,int backtrace[])
{
    for(int v = cost; v <=Volume; ++v)
    {
        if(a[v-cost] == numeric_limits<int>::max())
            continue;

        if(a[v-cost] + weight < a[v])
        {
            a[v] = a[v-cost] +weight;
            backtrace[v] = cost;
        }
    }
}

void print(int backtrace[], int acount)
{
    if(acount > 0)
    {
        cout<<backtrace[acount]<<" ";
        int rest = acount - backtrace[acount];

        if(rest > 0)
        {
            print(backtrace,rest);
        }
    }
}

void minChange(int coin[],int n, int acount)
{
    int a[1000];
    int backtrace[1000]; //backtrace[n]，在总数为n时，选择的最后一个零钱的面额
    a[0] = 0;

    for(int i=1; i < 1000; ++i)
    {
        a[i] = numeric_limits<int>::max();
    }

    for(int i = 0; i < n ; ++i)
        multiPacket(coin[i],a,acount,1,backtrace);

    cout<<"minNum: "<<a[acount]<<" coins: ";
    print(backtrace,acount);
}

int main0531()
{
    int money [] = {25, 21, 10, 5, 1};
    minChange(money,5,34);
    return 0;
}
