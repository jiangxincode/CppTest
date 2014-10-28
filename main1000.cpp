/*
南京大学计算机考研 2009 上机试题
南京大学计算机系 2009 年复试第一次加入上机考察，环境为 VC++6.0。考试时间一个小时。
上机考题只有一题，具体题目在下文，满分 50 分，编译不通过 0 分处理，具体的评分细节不详。
做完后只要两个文件 intset.h和 intset.cpp放在按规定建立的一个文件夹中。
要求写一个整数集合的类，分别放在 intset.h  和 intset.cpp 中，以实现下列程序功能。

#include "intset.h"
#include <iostream>
using namespace std;

int main()
{
    IntSet s1, s2, s3, s4;
    int x;
    for(cin >> x; x != 0; cin >> x) s1.insert(x);//在 s1 中插入元素
    for(cin >> x; x != 0; cin >> x) s2.insert(x);//在 s2 中插入元素
    if(s1.IsEqual(s2))//比较 s1 与 s2 是否相等
        cout << " s1 is equal s2 ";
    s3 = s3.union2(s1, s2);//求 s1 与 s2 的交
    s4 = s4.incorporate2(s1, s2);//求 s1  与 s2 的并
    cout << "\ns1:";
    s1.print();//输出 s1  中的元素 cout << "\ns2:";
    s2.print();
    cout << "\ns3:";
    s3.print();
    cout << "\ns4:";
    s4.print();
    return 0;
}
*/

//注：为了测试方便，没有采用inset.h，都放在一个文件了
#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

class IntSet
{
    set<int> int_set;
public:
    IntSet();
    IntSet(set<int> x);
    void insert(int x);
    void print();
    bool IsEqual(IntSet x);
    IntSet union2(IntSet x,IntSet y);
    IntSet incorporate2(IntSet x,IntSet y);
};
IntSet::IntSet() {}
IntSet::IntSet(set<int> x):int_set(x){}

void IntSet::insert(int x)
{
    int_set.insert(x);
}
void IntSet::print()
{
    for(auto i : int_set)
    {
        cout << i << " ";
    }
}
bool IntSet::IsEqual(IntSet x)
{
    for(auto i : int_set)
    {
        auto result = find(x.int_set.cbegin(),x.int_set.cend(),i);

        if(result == x.int_set.cend())
        {
            return false;
        }
    }

    for(auto i : x.int_set)
    {
        auto result = find(int_set.cbegin(),int_set.cend(),i);

        if(result == int_set.cend())
        {
            return false;
        }
    }

    return true;
}
IntSet IntSet::union2(IntSet x,IntSet y)
{
    for(auto i : x.int_set)
    {
        auto result = find(y.int_set.cbegin(),y.int_set.cend(),i);

        if(result != y.int_set.cend())
        {
            int_set.insert(i);
        }
    }

    return int_set;
}
IntSet IntSet::incorporate2(IntSet x,IntSet y)
{
    for(auto i : x.int_set)
    {
        int_set.insert(i);
    }

    for(auto i : y.int_set)
    {
        int_set.insert(i);
    }

    return int_set;
}

int main1000()
{
    IntSet s1, s2, s3, s4;
    int x;

    for(cin >> x; x != 0; cin >> x)
        s1.insert(x);//在 s1 中插入元素

    for(cin >> x; x != 0; cin >> x)
        s2.insert(x);//在 s2 中插入元素

    if(s1.IsEqual(s2))//比较 s1 与 s2 是否相等
        cout << " s1 is equal s2 ";

    s3 = s3.union2(s1, s2);//求 s1 与 s2 的交
    s4 = s4.incorporate2(s1, s2);//求 s1  与 s2 的并
    cout << "\ns1:";
    s1.print();//输出 s1  中的元素
    cout << "\ns2:";
    s2.print();
    cout << "\ns3:";
    s3.print();
    cout << "\ns4:";
    s4.print();
    return 0;
}
