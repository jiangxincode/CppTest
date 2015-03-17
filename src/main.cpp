#include <iostream>
#include "main.h"
#include <gtest/gtest.h>

using namespace std;

#define TEST_METHOD

#ifdef TEST_METHOD
int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    return 0;
}
#else
int main(int argc, char *argv[])
{
    string ch;

    do
    {
        fflush(stdin); //清空输入流
        main0556();
        cout << "\nGo on?(n/y)";
        cin >> ch;
    }
    while(ch == "y");

    return 0;
}
#endif // TEST_METHOD
