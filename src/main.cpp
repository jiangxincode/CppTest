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
    string ch;
    do
    {
        fflush(stdin); //清空输入流
        main2566();
        cout << "\nGo on?(n/y)";
        cin >> ch;
    }
    while(ch == "y");
    return 0;
#endif // TEST_METHOD

}

