#ifndef LINEARLIST_H
#define LINEARLIST_H
#endif // LINEARLIST_H

#include <cstdio>

using namespace std;

template <class T>
class linear_list
{
public:
    linear_list() {}
    ~linear_list() {}
    virtual int size()const=0; //获取表的最大容量
    virtual int length()const=0; //获取表长度
    virtual bool empty()const=0; //判表空
    virtual bool full()const=0; //判表满
    virtual void sort()=0; //排序
};

template<class T>
class sequence:public linear_list<T>
{
protected:
    T *data; //存放数组
    int maxSize; //最大可容纳表项的数目
    int last; //当前已存表项的最后位置（从0开始）
    void resize(int newSize); //改变data数组空间大小
public:
    sequence(int size=BUFSIZ);
    sequence(sequence<T>& L);
    ~sequence()
    {
        delete[] data;
    }
    int size()const //计算表最大可容纳表项个数
    {
        return maxSize;
    }
    int length()const //计算表长度
    {
        return last+1;
    }
    int search(T& x)const; //搜索x在表中位置，函数返回表项序号
    int locate(int i)const; //定位第i个表项，函数返回表项序号
    bool get(int i,T& x)const //取第i个表项的值
    {
        if(i>0&&i<=last+1)
        {
            x=data[i-1];
            return true;
        }
        else
            return false;
    }
    void set(int i,T& x) //用x修改第i个表项的值
    {
        if(i>0&&i<=last+1)
        {
            data[i-1]=x;
        }
    }
    bool insert(int i,T& x); //插入第i个表项，通过x返回表项的值
    bool remove(int i,T& x); //删除第i个表项，通过x返回表项的值
    bool empty() //判表空否，满则返回true；否则返回false
    {
        return (last==-1)?true:false;
    }
    bool full() //判表满否，满则返回true；否则返回false
    {
        return (last==maxSize-1)?true:false;
    }
    void input(); //输入
    void output(); //输出
    sequence<T> operator=(sequence<T>& L); //表整体赋值
};


/**
 * 单链表模板类
 */

template <class T>
struct LinkNode //链表节点类的定义
{
    T data; //数据域
    LinkNode<T> *link; //链指针域
    LinkNode(const T& item,LinkNode<T> *ptr=NULL):data(item),link(ptr) {} //构造函数（初始化指针成员和数据）
};

template <class T>
class linked_list:public linear_list<T>
{
public:
    linked_list():first(NULL) {}
    linked_list(const T& x)
    {
        first = new LinkNode<T>(x);
    }
    linked_list(linked_list<T>& L); //复制构造函数
    ~linked_list()
    {
        make_empty();   //析构函数
    }
    void make_empty(); //将链表置为空表
    int size()const
    {
        return 0;
    }
    int length()const; //计算链表的长度
    LinkNode<T> *getHead()const
    {
        return first;
    }; //返回附加头结点地址
    LinkNode<T> *search(T x)const; //搜索含数据x的元素
    LinkNode<T> *locate(int i); //所搜第i个元素所在的地址
    bool get(int i,T& x); //取出第i个元素的值
    bool set(int i,T& x); //用x修改第i个元素的值
    bool insert(int i,T& x); //在第i个位置后插入x
    bool remove(int i,T& x); //删除第i个元素，x返回该元素的值
    bool empty()const //判表空否？不满则返回ture
    {
        return first->link == NULL?true:false;
    }
    bool full()const
    {
        return false;   //判表满否？不满则返回false
    }
    void sort() {} //排序
    void input() {} //输入
    void inputFront(T endTag); //前插法
    void inputRear(T endTag); //后插法
    void output(); //输出
    linked_list<T>& operator=(linked_list<T>& L);


protected:
    LinkNode<T> *first;
};


#include <iostream>
#include <cstdlib>

using namespace std;

template <class T>
sequence<T>::sequence(int sz)
{
    if(sz>0)
    {
        maxSize=sz;
        last=-1;
        data=new T[maxSize];

        if(data==NULL)
        {
            cerr<<"存储分配错误！"<<endl;
            exit(1);
        }
    }
}

template <class T>
sequence<T>::sequence(sequence<T>& L)
{
    maxSize=L.Size();
    last=L.Length()-1;
    data=new T[maxSize];

    if(data==NULL)
    {
        cerr<<"存储分配错误"<<endl;
        exit(1);
    }

    for(int i=1; i<=last+1; i++)
    {
        data[i-1]=L.getData(i);
    }
}


template<class T>
linked_list<T>::linked_list(linked_list<T>& L) //复制构造函数
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
void linked_list<T>::make_empty() //将链表置为空表，仅保留一个附加表头结点
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
int linked_list<T>::length()const //计算带附加头结点的单链表的长度
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
LinkNode<T> *linked_list<T>::search(T x)const //在表中搜索含数据x的结点，搜索成功则返回该结点地址否则返回NULL
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
LinkNode<T> *linked_list<T>::locate(int i) //返回表中第i个元素的地址，若i<0或超出表中结点的数目，返回NULL
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
bool linked_list<T>::get(int i,T& x) //取出链表中第i个元素的值
{
    if(i < 0)
        return false;

    LinkNode<T> *current = locate(i);

    if(current == NULL)
        return false;
    else
    {
        x = current->data;
        return true;
    }
};
template<class T>

bool linked_list<T>::set(int i,T& x) //设置链表中第i个元素的值
{
    if(i < 0)
        return false;

    LinkNode<T> *current = locate(i);

    if(current == NULL)
        return false;
    else
    {
        current->data = x;
        return true;
    }
};

template<class T>
bool linked_list<T>::insert(int i,T& x) //将新元素x插入在链表中第i个结点之后
{
    LinkNode<T> *current = locate(i);

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
bool linked_list<T>::remove(int i,T& x) //将链表中的第i个元素删去，通过引用型参数返回该元素的值
{
    LinkNode<T> *current = locate(i-1);

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
void linked_list<T>::output() //单链表的输出函数，将单链表的所用数据按逻辑顺序输出到屏幕上
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
linked_list<T>& linked_list<T>::operator=(linked_list& L) //重载赋值操作
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
void linked_list<T>::inputFront(T endTag) //endTag是约定的输入序列结束的标志。如果输入序列是正整数，endTag可以是0或正整数;
//如果输入序列是字符，endTag可以是字符集中不会出现的字符，如"\0"。
{
    LinkNode<T> *newNode;
    T val;
    make_empty();
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
void linked_list<T>::inputRear(T endTag) //endTag是约定的输入序列结束的标志。如果输入序列是正整数，endTag可以是0或正整数;
//如果输入序列是字符，endTag可以是字符集中不会出现的字符，如"\0"。
{
    LinkNode<T> *newNode,*last;
    T val;
    make_empty();
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
