/*
趋势科技笔试题
以下的代码可放在VC++6.0里面运行。
题目是要求输出：TrendMicroSoftUSCN然后要求修改程序，使程序能输出以上结果． 代码如下：
#include <iostream>
#include <string>
using namespace std;
int main(int argc,char * argv[])
{
    string strArr1[] = { "Trend", "Micro", "soft"};
    string *p = new string[2];
    p[0] = "US";
    p[1] = "CN";
    for(int i=0;i < sizeof(strArr1)/sizeof(string);i++)
        cout << strArr1[i];
    for(i=0;i < sizeof(p)/sizeof(string);i++)
        cout << p[i];
    cout << endl;
}
*/
#include <iostream>
#include <string>
using namespace std;
int main()
{
    string strArr1[]= { "Trend", "Micro", "soft"};
    string *p=new string[2];
    p[0] = "US";
    p[1] = "CN";
    cout << sizeof(strArr1) << endl;
    cout << sizeof(p) << endl;
    cout << sizeof(string) << endl;

    for(size_t i=0; i < sizeof(strArr1)/sizeof(string); i++)
        cout << strArr1[i];

    for(size_t i=0; i < sizeof(p)*2/sizeof(string); i++)
        cout << p[i];

    cout <<endl;
    return 0;
}

/*
首先要明确sizeof 不是函数，也不是一元运算符，是个类似宏定义的特殊关键字，
sizeof（）；括号内在编译过程中是不被编译的，而是被替代类型，
如 int a=8；sizeof（a）；在编译过程中，它不管a的值是什么，只是被替换成类型 sizeof（int）；
结果为4.
如果sizeof（a=6）；呢,也是一样的转换成a的类型，但是要注意因为a=6是不被编译的，
所以执行完sizeof（a=6）；a的值还是6，是不变的！

记住以下几个结论：
1.unsigned影响的只是最高位bit的意义（正负），数据长度不会被改变的。
所以sizeof(unsigned int) == sizeof(int)；
2.自定义类型的sizeof取值等同于它的类型原形。
如typedef short WORD;sizeof(short) == sizeof(WORD)。
3.对函数使用sizeof，在编译阶段会被函数返回值的类型取代。如：int f1(){return 0;};
cout < <sizeof(f1()) < <endl; // f1()返回值为int，因此被认为是int
4.只要是指针，大小就是4。如：cout < <sizeof(string*) < <endl; // 4
5.数组的大小是各维数的乘积*数组元素的大小。如：char a[] = "abcdef ";
int b[20] = {3, 4};
char c[2][3] = { "aa ", "bb "};
cout < <sizeof(a) < <endl; // 7
cout < <sizeof(b) < <endl; // 20*4
cout < <sizeof(c) < <endl; // 6
数组a的大小在定义时未指定，编译时给它分配的空间是按照初始化的值确定的，
也就是7，包括‘\0’的。
6.字符串的sizeof和strlen，用例子说明：
char a[] = "abcdef ";
char b[20] = "abcdef ";
string s = "abcdef ";
cout < <strlen(a) < <endl; // 6，字符串长度
cout < <sizeof(a) < <endl; // 7，字符串容量
cout < <strlen(b) < <endl; // 6，字符串长度
cout < <sizeof(b) < <endl; // 20，字符串容量
cout < <sizeof(s) < <endl; // 16, 这里不代表字符串的长度，而是string类的大小
cout < <strlen(s) < <endl; // 错误！s不是一个字符指针。
a[1] = '\0 ';
cout < <strlen(a) < <endl; // 1
cout < <sizeof(a) < <endl; // 7，sizeof是恒定的

所以你的问题就解决的差不多了，sizeof(string)=16如yi-0220所说，
给出的答案是：for(i=0;i <sizeof(p)/sizeof(string);i++)
改为for(i=0;i <sizeof(p)*2/sizeof(string);i++) 答案也是不对的，sizeof（p)只是指针大小 为4， 要想求出数组p指向数组的成员个数，应该为sizeof(*p)*8/sizeof(string)，为什么？
指针p指向数组，则*p就是指向数组中的成员了，成员的类型是什么，string型，ok那么sizeof(*p)为16，乘以2才是整个数组的大小
*/

