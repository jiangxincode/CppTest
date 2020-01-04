#include "../../src/common/sort.h"
#include "gtest/gtest.h"
#include <stdlib.h>

#define MAX_RANDOM_NUM 100

class SortTest:public testing::Test
{
protected:
    virtual void SetUp()
    {
        p_random = (int*)malloc(sizeof(int)*MAX_RANDOM_NUM);
        srand(1); //set the seed of the rand engine.
        for(int i=0;i<MAX_RANDOM_NUM;i++)
        {
            p_random[i] = rand();
        }
    }

    virtual void TearDown()
    {
        free(p_random);
    }
    int* p_random;
};



TEST_F(SortTest, bubblesor_test)
{
    bubblesort(p_random, MAX_RANDOM_NUM);
    for(int i=0;i<MAX_RANDOM_NUM-1;i++)
    {
        EXPECT_LE(p_random[i],p_random[i+1]);
    }
}

TEST_F(SortTest, insertsort_test)
{
    insertsort(p_random, MAX_RANDOM_NUM);
    for(int i=0;i<MAX_RANDOM_NUM-1;i++)
    {
        EXPECT_LE(p_random[i],p_random[i+1]);
    }
}

TEST_F(SortTest, quicksort_test)
{
    quicksort(p_random, 0, MAX_RANDOM_NUM-1);
    for(int i=0;i<MAX_RANDOM_NUM-1;i++)
    {
        EXPECT_LE(p_random[i],p_random[i+1]);
    }
}

TEST_F(SortTest, shellsort_test)
{
    shellsort(p_random, MAX_RANDOM_NUM);
    for(int i=0;i<MAX_RANDOM_NUM-1;i++)
    {
        EXPECT_LE(p_random[i],p_random[i+1]);
    }
}

TEST_F(SortTest, mergesort_recursive_test)
{
    mergesort_recursive(p_random, 0, MAX_RANDOM_NUM-1);
    for(int i=0;i<MAX_RANDOM_NUM-1;i++)
    {
        EXPECT_LE(p_random[i],p_random[i+1]);
    }
}

TEST_F(SortTest, mergesort_test)
{
    mergesort(p_random, MAX_RANDOM_NUM);
    for(int i=0;i<MAX_RANDOM_NUM-1;i++)
    {
        EXPECT_LE(p_random[i],p_random[i+1]);
    }
}


