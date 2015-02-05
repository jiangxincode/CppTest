#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

void print(int i)
{
    cout << i << " ";
}
void add_a_num(int &i)
{
    i += 10;
}
int minus_a_num(int i)
{
    return i-10;
}
bool is_odd(int i)
{
    return (i%2==0);
}
bool compare_bigger(int i,int j)
{
    if(i > j)
    {
        return false;
    }
    else
    {
        return true;
    }
}
int main0538()
{
    vector<int> coll;

    for(int i=0; i<10; i++)
    {
        coll.insert(coll.end(),i);
    }

    for_each(coll.begin(),coll.end(),print);
    cout << endl;
    for_each(coll.begin(),coll.end(),add_a_num);
    for_each(coll.begin(),coll.end(),print);
    cout << endl;
    transform(coll.begin(),coll.end(),coll.begin(),minus_a_num);
    for_each(coll.begin(),coll.end(),print);
    cout << endl;
    cout << count_if(coll.begin(),coll.end(),is_odd);
    cout << " ";
    cout << count(coll.begin(),coll.end(),5);
    cout << endl;
    cout << *min_element(coll.begin(),coll.end());
    cout << " ";
    cout << *max_element(coll.begin(),coll.end());
    cout << endl;
    deque<int> deq;
    deq = {1, 2, 7, 7, 6, 3, 9, 5, 7, 7, 7, 3, 6};
    deque<int>::iterator pos = search_n(deq.begin(),deq.end(),3,7);
    cout << *pos;
    return 0;
}
