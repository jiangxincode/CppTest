#include <iostream>
#include <string>
#include <cstdio>
#include <cassert>
#include "main.h"

using namespace std;

int main(int argc, char *argv[])
{

#ifdef ONLINE_JUDGE
    string filename = "main4418";
    string filename_in = "test\\" + filename;
    string filename_out = "temp\\" + filename;
    if(freopen((filename_in + ".in").c_str(), "r", stdin) == NULL)
    {
        perror("Something error!");
    }
    if(freopen((filename_out + ".out").c_str(), "w", stdout) == NULL)
    {
        perror("Something error!");
    }
    maintest();
    if(freopen("CON", "r", stdin) == NULL)
    {
        perror("Something error!");
    }
    if(freopen("CON", "w", stdout) == NULL)
    {
        perror("Something error!");
    }

    if(compare_file_text((filename_in + ".result"), (filename_out + ".out")))
    {
        cerr << "success" << endl;
    }
    else
    {
        cerr << "fail" << endl;
    }
#endif // ONLINE_JUDGE
#define COMMON_TEST
#ifdef COMMON_TEST
    string ch;
    do
    {
        fflush(stdin); //清空输入流
        maintest();
        cout << "\nGo on?(n/y)";
        cin >> ch;
    }while(ch == "y");
#endif
}

