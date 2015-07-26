#include <stdlib.h>
#include "../include/gtest/gtest.h"
#include "../src/miscellaneous.h"

class MiscellaneousTest:public testing::Test
{
protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
};


TEST_F(MiscellaneousTest, plus_without_operator_test)
{
    EXPECT_EQ(7,plus_without_operator(3,4));
}

TEST_F(MiscellaneousTest, palindrome_test)
{
    EXPECT_EQ(1, palindrome(121));
    EXPECT_EQ(0, palindrome(211));
    EXPECT_EQ(0, palindrome("hello"));
    EXPECT_EQ(1, palindrome("abaaba"));
}

TEST_F(MiscellaneousTest, max_test)
{
    EXPECT_EQ(3, max1(2,3));
    EXPECT_EQ(3, max1(3,2));
    EXPECT_EQ(3, max2(2,3));
    EXPECT_EQ(3, max2(3,2));
}

TEST_F(MiscellaneousTest, swap_test)
{
    int a=15,b=17;

    swap1(&a, &b);
    EXPECT_EQ(15, b);
    EXPECT_EQ(17, a);

    swap2(&a, &b);
    EXPECT_EQ(17, b);
    EXPECT_EQ(15, a);

    swap3(&a, &b);
    EXPECT_EQ(15, b);
    EXPECT_EQ(17, a);
}
