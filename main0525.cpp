#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct test
{
    int i_var;
    char c_var;
    static int s_i_var; //problem 如何访问该变量
};

/** \brief 验证一些基础知识
 *
 * \param 无
 * \return 正常执行返回0
 *
 */

int main0525()
{
    for(int i=0; i<4; i++)
    {
        static int var = 0; //静态变量只在程序运行时初始化一次
        cout << var++ << " ";
    }
    cout << "\n" << sizeof(test); //static不算，char对齐为4，所以总共为8
    struct test test1;
    struct test test2;
    test1.i_var = 1;
    test1.c_var = '1';

    test2.i_var = 2;
    test2.c_var = '2';

    cout << "test1 " << test1.i_var << " " << test1.c_var << endl;
    cout << "test2 " << test2.i_var << " " << test2.c_var << endl;

    string str = "123,45";
    double result;
    stringstream io(str);
    io >> result;
    cout << "\n" << result;

    return 0;
}
