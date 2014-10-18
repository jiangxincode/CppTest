/*
http://wikioi.com/problem/1202/
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main005()
{
    int input_num;
    int input_temp;
    vector<int> vec;
    cin >> input_num;

    for(int i=0; i<input_num; i++)
    {
        cin >> input_temp;
        vec.insert(vec.end(),input_temp);
    }

    //int sum = accumulate(vec.begin(),vec.end(),0);
    vector<int>::iterator it; //注意此处it的声明方法
    int sum = 0;

    for(it=vec.begin(); it!=vec.end(); it++)
    {
        sum += *it;
    }

    cout << sum;
    return 0;
}
