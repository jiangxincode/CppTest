#include <iostream>
#include "main.h"
#include "gtest/gtest.h"

using namespace std;

int main(int argc, char *argv[])
{

#define TEST_METHOD

#ifdef TEST_METHOD
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
#else
    return 0;
#endif // TEST_METHOD

}

