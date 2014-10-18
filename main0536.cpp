/*
���ƿƼ�������
*/

/*�Ĵ�*/
#include <iostream>

using namespace std;

class klass
{
public:
    klass() {}
    ~klass() {} //��������������Ϊ˽������
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
д�����н��������
�𰸣�
1) �����ָ��ָ�������������ô��ָ��ֻ�ܹ����û���������ĺ�����
��������ú���Ϊ�麯��������ø��������Լ��ĳ�Ա������(B2 :1)
2) ������������ָ��ָ����������������������Ե�ת�Ͳ�������������������Σ�ա�
*/
#include <cstdio>
using namespace std;
class A
{
public:
    A()
    {
        func(0);
    };
    virtual void func(int data)
    {
        printf("A1 :%d\n",data);
    }
    virtual void func(int data) const
    {
        printf("A2 :%d\n",data);
    }
    void func(const char *str)
    {
        printf("A3 %s)\n",str);
    }
};

class B:public A
{
public:
    void func()
    {
        printf("B1 :%s\n","");
    }
    void func(int data)
    {
        printf("B2 :%d\n",data);
    }
    void func(const char *str)
    {
        printf("B3 %s)\n",str);
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

int main0536()
{
    main05362();
    return 0;
}
