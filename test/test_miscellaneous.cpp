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
