#include <iostream>
#include <cstdlib>

#include "linear_list.h"

using namespace std;
const int defaultSize=100;

template<class T>
class SeqList:public LinearList<T>
{
protected:
    T *data; //存放数组
    int maxSize; //最大可容纳表项的数目
    int last; //当前已存表项的最后位置（从0开始）
    void reSize(int newSize); //改变data数组空间大小
public:
    SeqList(int size=defaultSize);
    SeqList(SeqList<T>& L);
    ~SeqList()
    {
        delete[] data;
    }
    int Size()const //计算表最大可容纳表项个数
    {
        return maxSize;
    }
    int Length()const //计算表长度
    {
        return last+1;
    }
    int Search(T& x)const; //搜索x在表中位置，函数返回表项序号
    int Locate(int i)const; //定位第i个表项，函数返回表项序号
    bool getData(int i,T& x)const //取第i个表项的值
    {
        if(i>0&&i<=last+1)
        {
            x=data[i-1];
            return true;
        }
        else
            return false;
    }
    void setData(int i,T& x) //用x修改第i个表项的值
    {
        if(i>0&&i<=last+1)
        {
            data[i-1]=x;
        }
    }
    bool Insert(int i,T& x); //插入第i个表项，通过x返回表项的值
    bool Remove(int i,T& x); //删除第i个表项，通过x返回表项的值
    bool IsEmpty() //判表空否，满则返回true；否则返回false
    {
        return (last==-1)?true:false;
    }
    bool IsFull() //判表满否，满则返回true；否则返回false
    {
        return (last==maxSize-1)?true:false;
    }
    void input(); //输入
    void output(); //输出
    SeqList<T> operator=(SeqList<T>& L); //表整体赋值
};

template <class T>
SeqList<T>::SeqList(int sz)
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
SeqList<T>::SeqList(SeqList<T>& L)
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
