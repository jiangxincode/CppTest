#include <iostream>
#include <string>
#include <cstdio>
#include <cassert>
#include "main.h"
#include "gtest/gtest.h"

using namespace std;

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

