#include "../src/sort.h"
#include <gtest/gtest.h>

TEST(testbubblesort, testbubblesort1)
{
    int data[10] = {10,12,4,6,7,3,8,50,39,20};
    int result[10] = {3,4,6,7,8,10,12,20,39,50};
    bubblesort(data, 10);
    for(int i=0;i<10;i++)
    {
        EXPECT_EQ(data[i], result[i]);
    }
}


