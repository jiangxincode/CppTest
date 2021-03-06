﻿/**
 * 趋势科技笔试题（改错）
 */

#include <iostream>

using namespace std;

class klass
{
public:
    klass() {}
    ~klass() {} //析构函数不能设为私有属性
private:
    void func(int n)
    {
        cout<<"klass!!"<<endl;
    }
public:
    void test()
    {
        func(100);
    }
};

int main05361()
{
    klass k;
    k.test();
    return 0;
}

/*
写出运行结果并解释
答案：
1) 基类的指针指向派生类对象：那么该指针只能够调用基类所定义的函数，
但是如果该函数为虚函数，则调用该派生类自己的成员函数。(B2 :1)
2) 如果以派生类的指针指向基类对象，则必须事先做明显的转型操作，但是这种做法很危险。
*/

class A
{
public:
    A()
    {
        func(0);
    };
    virtual void func(int data)
    {
        cout << "A1 :" << data << endl;
    }
    virtual void func(int data) const
    {
        cout << "A2 :" << data << endl;
    }
    void func(const char *str)
    {
        cout << "A3 " << str << endl;
    }
};

class B:public A
{
public:
    void func()
    {
        cout << "B1 :" << endl;
    }
    void func(int data)
    {
        cout << "B2 :" << data << endl;
    }
    void func(const char *str)
    {
        cout << "B3 :" << str << endl;
    }
};

int main05362()
{
    A *pA;
    B b;
    const A *pcA;
    pA=&b;
    pA->func(1);
    pA->func("test");
    A().func(1);
    pcA=&b;
    pcA->func(2);
    return 0;
}

#include <iostream>

using namespace std;

void func(const int &t)
{
    cout<<t+100<<endl;
}

template<typename T>
void func(const T &t)
{
    cout<<t;
}


int main05363()
{
    func(10.3);
    func(1000);
    return 0;
}

int main()
{
    main05362();
    return 0;
}
