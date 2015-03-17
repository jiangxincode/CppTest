#include <iostream>
#include "main.h"
#include <gtest/gtest.h>

using namespace std;

//int main(int argc, char *argv[])
//{
//    string ch;
//
//    do
//    {
//        fflush(stdin); //清空输入流
//        main1730();
//        cout << "\nGo on?(n/y)";
//        cin >> ch;
//    }
//    while(ch == "y");
//
//    return 0;
//}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    return 0;
}
