//һЩ����֪ʶ��֤
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
    for(int i=0;i<4;i++)
    {
        static int var1 = 0; //��̬����ֻ�ڳ�������ʱ��ʼ��һ��
        cout << var1++ << " ";
    }
    cout << endl;
    cout << sizeof(test); //static���㣬char����Ϊ4
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
