//一些基础知识验证
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct test
{
    int i_var;
    char c_var;
    static int s_i_var;
};

int main05251()
{
    for(int i=0; i<4; i++)
    {
        static int var1 = 0; //静态变量只在程序运行时初始化一次
        cout << var1++ << " ";
    }

    cout << endl;
    cout << sizeof(test); //static不算，char对其为4
    return 0;
}
int main0525()
{
    string str = "123,45";
    double result;
    stringstream io(str);
    io >> result;
    cout << result;
    return 0;
}
