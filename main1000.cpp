/*
�Ͼ���ѧ��������� 2009 �ϻ�����
�Ͼ���ѧ�����ϵ 2009 �긴�Ե�һ�μ����ϻ����죬����Ϊ VC++6.0������ʱ��һ��Сʱ��
�ϻ�����ֻ��һ�⣬������Ŀ�����ģ����� 50 �֣����벻ͨ�� 0 �ִ������������ϸ�ڲ��ꡣ
�����ֻҪ�����ļ� intset.h�� intset.cpp���ڰ��涨������һ���ļ����С�
Ҫ��дһ���������ϵ��࣬�ֱ���� intset.h  �� intset.cpp �У���ʵ�����г����ܡ�

#include "intset.h"
#include <iostream>
using namespace std;

int main()
{
    IntSet s1, s2, s3, s4;
    int x;
    for(cin >> x; x != 0; cin >> x) s1.insert(x);//�� s1 �в���Ԫ��
    for(cin >> x; x != 0; cin >> x) s2.insert(x);//�� s2 �в���Ԫ��
    if(s1.IsEqual(s2))//�Ƚ� s1 �� s2 �Ƿ����
        cout << " s1 is equal s2 ";
    s3 = s3.union2(s1, s2);//�� s1 �� s2 �Ľ�
    s4 = s4.incorporate2(s1, s2);//�� s1  �� s2 �Ĳ�
    cout << "\ns1:";
    s1.print();//��� s1  �е�Ԫ�� cout << "\ns2:";
    s2.print();
    cout << "\ns3:";
    s3.print();
    cout << "\ns4:";
    s4.print();
    return 0;
}
*/

//ע��Ϊ�˲��Է��㣬û�в���inset.h��������һ���ļ���
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
        s1.insert(x);//�� s1 �в���Ԫ��

    for(cin >> x; x != 0; cin >> x)
        s2.insert(x);//�� s2 �в���Ԫ��

    if(s1.IsEqual(s2))//�Ƚ� s1 �� s2 �Ƿ����
        cout << " s1 is equal s2 ";

    s3 = s3.union2(s1, s2);//�� s1 �� s2 �Ľ�
    s4 = s4.incorporate2(s1, s2);//�� s1  �� s2 �Ĳ�
    cout << "\ns1:";
    s1.print();//��� s1  �е�Ԫ��
    cout << "\ns2:";
    s2.print();
    cout << "\ns3:";
    s3.print();
    cout << "\ns4:";
    s4.print();
    return 0;
}
