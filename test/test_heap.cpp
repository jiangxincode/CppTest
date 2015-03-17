#include "../src/heap.h"
#include <gtest/gtest.h>

bool compmin(int a,int b)
{
    return (a < b)?true:false;
}

bool compmax(int a,int b)
{
    return (b < a)?true:false;
}

TEST(HeapTest, Test01) //最大堆
{
    const int MAXNUM = 20;
    int in[MAXNUM];

    for(int i=0; i<MAXNUM; i++)
    {
        in[i] = rand()%100;
    }

    heap h1(in, MAXNUM, compmax);

    for(int i=0; i<MAXNUM; i++) //验证是否形成最大堆
    {
        if(2*i+1 < h1.size())
        {
            EXPECT_GE(h1.at(i), h1.at(2*i+1));
        }

        if(2*i+2 < h1.size())
        {
            EXPECT_GE(h1.at(i), h1.at(2*i+2));
        }
    }
}

TEST(HeapTest, Test02) //最大堆
{
    const int MAXNUM = 20;
    heap h1(MAXNUM, compmax);

    for(int i=0; i<MAXNUM; i++)
    {
        h1.push(rand()%100);
    }

    h1.sort();

    for(int i=0; i<MAXNUM-1; i++) //验证是否非递减排序
    {
        EXPECT_LE(h1.at(i), h1.at(i+1));
    }
}
