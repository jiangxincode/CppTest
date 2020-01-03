#include <iostream>
#include <vector>

using namespace std;

/**
 * 系统测试
 */
int main()
{
#ifdef __WIN32__
    cout << "WIN32" << endl;
#endif // WIN32

#ifdef __LINUX
    cout << "LINUX" << endl;
#endif // LINUX
    return 0;
}

/**
 * 创建一个int型变量，对其赋值；
 * 再创建一个长度为5的int型动态数组，从键盘输入数组元素的值；
 * 然后输出动态变量和动态数组的值
 */
int main2579()
{
    int i_num;
    cout << "Input an integer: ";
    cin >> i_num;
    vector<int> vec_num(5);
    cout << "Input 5 numbers:";

    for(int i=0; i<5; i++)
    {
        int temp;
        cin >> temp;
        vec_num[i] = temp;
    }

    cout << "The integer is: " << i_num << endl;
    cout << "The array is: " << endl;

    for(int i=0; i<5; i++)
    {
        cout << vec_num[i] << " ";
    }

    return 0;
}
