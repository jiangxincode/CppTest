//单链表模板类
#include <iostream>
#include <cstdlib>
#include <cstdio>

#include "linear_list.h"

using namespace std;

template <class T>
struct LinkNode //链表节点类的定义
{
    T data; //数据域
    LinkNode<T> *link; //链指针域
    LinkNode(LinkNode<T> *ptr=NULL) //构造函数（只初始化指针成员）
    {
        link = ptr;
    }

    LinkNode(const T& item,LinkNode<T> *ptr=NULL) //构造函数（初始化指针成员和数据）
    {
        data = item;
        link = ptr;
    }
};

template <class T>
class List
{
public:
    List()
    {
        first = new LinkNode<T>;   //构造函数
    }
    List(const T& x)
    {
        first = new LinkNode<T>(x);   //构造函数
    }
    List(List<T>& L); //复制构造函数
    ~List()
    {
        makeEmpty();   //析构函数
    }
    void makeEmpty(); //将链表置为空表
    int Length()const; //计算链表的长度
    LinkNode<T> *getHead()const
    {
        return first;
    }; //返回附加头结点地址
    LinkNode<T> *Search(T x)const; //搜索含数据x的元素
    LinkNode<T> *Locate(int i); //所搜第i个元素所在的地址
    bool getData(int i,T& x); //取出第i个元素的值
    bool setData(int i,T& x); //用x修改第i个元素的值
    bool Insert(int i,T& x); //在第i个位置后插入x
    bool Remove(int i,T& x); //删除第i个元素，x返回该元素的值
    bool IsEmpty()const //判表空否？不满则返回ture
    {
        return first->link == NULL?true:false;
    }
    bool IsFull()const
    {
        return false;   //判表满否？不满则返回false
    }
    void Sort() {} //排序
    void input() {} //输入
    void inputFront(T endTag); //前插法
    void inputRear(T endTag); //后插法
    void output(); //输出
    List<T>& operator=(List<T>& L);
protected:
    LinkNode<T> *first;
};

template<class T>
List<T>::List(List<T>& L) //复制构造函数
{
    T temp;
    LinkNode<T> *scrptr = L.getHead(); //被复制表的附加头结点地址
    LinkNode<T> *desptr = first = new LinkNode<T>;

    while(scrptr->link != NULL) //逐个复制头结点
    {
        temp = scrptr->link->data;
        desptr->link = new LinkNode<T>(temp);
        desptr = desptr->link;
        scrptr = scrptr->link;
    }

    desptr->link = NULL;
};

template<class T>
void List<T>::makeEmpty() //将链表置为空表，仅保留一个附加表头结点
{
    LinkNode<T> *temp;

    while(first->link != NULL)
    {
        temp = first->link;
        first->link = temp->link;
        delete temp;
    }
};

template<class T>
int List<T>::Length()const //计算带附加头结点的单链表的长度
{
    LinkNode<T> *p = first->link;
    int count = 0;

    while(p != NULL)
    {
        p = p->link;
        count++;
    }

    return count;
};

template<class T>
LinkNode<T> *List<T>::Search(T x)const //在表中搜索含数据x的结点，搜索成功则返回该结点地址否则返回NULL
{
    LinkNode<T> *current = first->link;

    while(current != NULL)
    {
        if(current->data == x)
            break;
        else
            current = current->link;
    }

    return current;
}

template<class T>
LinkNode<T> *List<T>::Locate(int i) //返回表中第i个元素的地址，若i<0或超出表中结点的数目，返回NULL
{
    if(i < 0)
        return 0;

    LinkNode<T> *current = first;
    int temp = 0;

    while(current != NULL && temp < i)
    {
        current = current.link;
        temp++;
    }

    return current;
}

template<class T>
bool List<T>::getData(int i,T& x) //取出链表中第i个元素的值
{
    if(i < 0)
        return false;

    LinkNode<T> *current = Locate(i);

    if(current == NULL)
        return false;
    else
    {
        x = current->data;
        return true;
    }
};
template<class T>

bool List<T>::setData(int i,T& x) //设置链表中第i个元素的值
{
    if(i < 0)
        return false;

    LinkNode<T> *current = Locate(i);

    if(current == NULL)
        return false;
    else
    {
        current->data = x;
        return true;
    }
};

template<class T>
bool List<T>::Insert(int i,T& x) //将新元素x插入在链表中第i个结点之后
{
    LinkNode<T> *current = Locate(i);

    if(current == NULL)
        return false;

    LinkNode<T> *newNode = new LinkNode<T>(x);

    if(newNode == NULL)
    {
        cerr<<"存储分配错误"<<endl;
        exit(1);
    }

    newNode->link = current->link;
    current->link = newNode;
    return true;
}

template<class T>
bool List<T>::Remove(int i,T& x) //将链表中的第i个元素删去，通过引用型参数返回该元素的值
{
    LinkNode<T> *current = Locate(i-1);

    if(current == NULL || current.link == NULL)
    {
        return false;
    }

    LinkNode<T> *del = current->link;
    current->link = del->link;
    x = del->data;
    delete del;
    return true;
}

template<class T>
void List<T>::output() //单链表的输出函数，将单链表的所用数据按逻辑顺序输出到屏幕上
{
    LinkNode<T> *current = first->link;

    while(current != NULL)
    {
        cout<<current->data<<" ";
        current = current->link;
    }

    cout<<endl;
};

template<class T>
List<T>& List<T>::operator=(List& L) //重载赋值操作
{
    T temp;
    LinkNode<T> *scrptr = L.getHead(); //被复制表的附加头结点地址
    LinkNode<T> *desptr = first = new LinkNode<T>;

    while(scrptr->link != NULL) //逐个复制头结点
    {
        temp = scrptr->link->data;
        desptr->link = new LinkNode<T>(temp);
        desptr = desptr->link;
        scrptr = scrptr->link;
    }

    desptr->link = NULL;
    return *this;
};

template <class T>
void List<T>::inputFront(T endTag) //endTag是约定的输入序列结束的标志。如果输入序列是正整数，endTag可以是0或正整数;
//如果输入序列是字符，endTag可以是字符集中不会出现的字符，如"\0"。
{
    LinkNode<T> *newNode;
    T val;
    makeEmpty();
    cout<<"Input the data:"<<endl;
    cin >> val;

    while(val != endTag)
    {
        newNode = new LinkNode<T>(val);

        if(newNode == NULL)
        {
            cerr << "存储分配错误" <<endl;
            exit(1);
        }

        newNode->link = first->link;
        first->link = newNode;
        cin >> val;
    }
};

template <class T>
void List<T>::inputRear(T endTag) //endTag是约定的输入序列结束的标志。如果输入序列是正整数，endTag可以是0或正整数;
//如果输入序列是字符，endTag可以是字符集中不会出现的字符，如"\0"。
{
    LinkNode<T> *newNode,*last;
    T val;
    makeEmpty();
    cout<<"Input the data:"<<endl;
    cin >> val;
    last = first;

    while(val != endTag)
    {
        newNode = new LinkNode<T>(val);

        if(newNode == NULL)
        {
            cerr << "存储分配错误" <<endl;
            exit(1);
        }

        last->link = newNode;
        last= newNode;
        cin >> val;
    }

    last->link = NULL;
};
