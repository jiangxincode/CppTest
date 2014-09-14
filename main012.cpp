/*
http://wikioi.com/problem/1076/
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main012()
{
    int num;
    int temp;
    vector<int> vec;
    cin >> num;
    for(int i=0;i<num;i++)
    {
        cin >> temp;
        vec.push_back(temp);
    }
    sort(vec.begin(),vec.end());
    for(vector<int>::iterator it=vec.begin();it!=vec.end();it++)
    {
        cout << *it << " ";
    }
    return 0;
}
