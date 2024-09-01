#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>

using namespace std;

//关于cin cin.getline cin.get getline gets getchar 的用法实例
int main()
{
    int a,b;
    cout << "[cin demo1]input two integer: " << endl;
    cin >> a >> b;
    cout << "[cin demo1]sum: " << a + b << endl;

    char array[10];
    cout << "[cin demo2]Test cin>>input a char array: " << endl; // 遇到Enter/Space/Tab都结束
    cin >> array;
    cout << array << endl;

    cout << "Test cin.get(字符变量名)：" << endl;
    char ch;
    cout << "[cin.get demo1]input a char:" << endl;
    cin.get(); // cin.get()主要用来舍弃输入流中不需要的字符 或者舍弃回车
    ch = cin.get(); //or cin.get(ch);
    cout << ch << endl;

    char array1[20];
    cout << "[cin.get demo2]input a char array:" << endl;
    cin.get(); // cin.get()主要用来舍弃输入流中不需要的字符 或者舍弃回车
    cin.get(array1,10); //cin.get(字符数组，接收的字符数) 用来接收一行字符串可以接收空格
    cout << array1 << endl;

    char array2[20];
    cout << "[cin.getline demo1]Input a char array:" << endl;
    cin.get(); //把之前输入的回车符号滤去
    // 接收一个字符串，可以接收空格
    // 实际上cin.get(字符数组，接收的字符数) 和cin.getline(字符数组，接收的字符数)
    // 有三个参数cin.getline(字符数组，接收字符数，结束字符) 第三个参数默认是'\0'
    cin.getline(array2,20); //接收一个字符串 可以接收空格
    cout << array2 << endl;

    string str;
    cout << "[getline demo1]Input a string:" << endl;
    getline(cin,str); //getline(cin,str)接收一个可以包含空格的字符串(这儿是string类型的) 需要包含头文件#include <string>
    cout << str << endl;

    char array4[20];
    cout << "[gets demo1]input a char array:" << endl;
    cin.get(); //把之前输入的回车符号滤去
    // The gets function reads a line from the standard input stream stdin and stores it in buffer.
    // The line consists of all characters up to and including the first newline character ('\n').
    // gets then replaces the newline character with a null character ('\0') before returning the line
    // <stdio.h>
    // 2011年12月，ANSI 采纳了 ISO/IEC 9899:2011 标准，标准中删除了非安全函数 gets()，使用一个新的更安全的函数gets_s()替代
    // 但是很多编译器厂商没有实现该函数
    // gets(array4);

    // fgets和gets虽然都是读取一行，但是前者会把换行符读到，后者不会
    fgets(array4,20,stdin);
    array4[strlen(array4)-1] = '\0'; // 删除换行符
    cout << array4 << endl;

    char ch1;
    cout << "[getchar demo1]input a char:" << endl;
    ch1 = getchar(); //getchar() 接收一个字符 需要包含头文件#include <string>
    cout << ch1 << "\n" << endl;
    //getchar()是C的函数 C++是兼容C 所以也可以使用 但尽量不用或少用
    return 0;
}



/*
测试标准输入cin和文件结束符
测试平台：Windows
*/
int test_string_one() //第一个程序：输入的是整数
{
    int num;

    while(cin>>num)
        cout << num << " ";

    return 0;
}
/*
输入：1 2 3 4 5 Ctrl+d Enter
输出：1 2 3 4 5
此处之所以循环停止，是因为遇到一个无效输入（Ctrl+d），而不是遇到了文件结束符。
因为在windows平台，结束符是Ctrl+z，然后按Enter。
例如输入：1 2 3 4 5 a Enter
输出仍是：1 2 3 4 5
当然如果该测试用例用于Linux下，那么由于系统的结束符是Ctrl+d，所以虽然输出一样，
但是之所以循环停止，是因为到达了文件结束，而不是得到了一个无效输入。
*/


int test_string_two() //第二个程序：输入的是字符串
{
    string word;

    while(cin>>word)
        cout << word << " ";

    return 0;
}
/*
输入：hello world Ctrl+z 回车
输出：hello world
此处之所以循环停止，是因为遇到一个文件结束符。
因为在windows平台，结束符是Ctrl+z，然后按Enter。
*/


