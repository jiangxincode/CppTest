#include "../src/fibonacci.h"
#include "../include/gtest/gtest.h"

int fibonacci_array[25] = {
    0, 1, 1, 2, 3, 5, 8, 13, 21, 34,
    55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181,
    6765, 10946, 17711, 28657, 46368};

TEST(FibonacciTest, fibonacci_test)
{
    for(int i=0; i<25; i++)
    {
        ASSERT_EQ(fibonacci_array[i], fibonacci(i));
    }
}

TEST(FibonacciTest, fibonacci_2_test)
{
    for(int i=0; i<25; i++)
    {
        ASSERT_EQ(fibonacci_array[i], fibonacci_2(i));
    }
}
