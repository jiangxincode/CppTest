#include <iostream>
#include <string>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <numeric>

using namespace std;

int test();

int main(int argc, char *argv[])
{
    string ch;
    do
    {
        fflush(stdin); //清空输入流
        test();
        cout << "\nGo on?(n/y)";
        cin >> ch;
    }while(ch == "y");
}



int test() {
    std::vector<int> v = { 1, 2, 3, 4, 5, 5, 4, 3, 2, 1 };
    std::cout << accumulate(v.begin(), v.end(), 0.0) << std::endl;
    return 0;
}

