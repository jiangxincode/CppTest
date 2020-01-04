#include "../../src/common/factorial.h"
#include "gtest/gtest.h"

TEST(FactorialTest, factorial_test)
{
    ASSERT_EQ(1, factorial(1));
    ASSERT_EQ(2, factorial(2));
    ASSERT_EQ(6, factorial(3));
    ASSERT_EQ(24, factorial(4));
    ASSERT_EQ(120, factorial(5));
    ASSERT_EQ(720, factorial(6));
}
