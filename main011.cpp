/*
http://wikioi.com/problem/1075/
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main011()
{
    int number;
    int temp;
    vector<int> vec;
    cin >> number;

    for(int i=0; i<number; i++)
    {
        cin >> temp;
        vec.push_back(temp);
    }

    sort(vec.begin(),vec.end());
    //ע��ȥ�صķ���
    vector<int>::iterator unique_it = unique(vec.begin(),vec.end());
    vec.erase(unique_it,vec.end()); //�˴�һ��Ҫɾ����
    cout << vec.size() << endl;
    vector<int>::iterator pos;

    for(pos=vec.begin(); pos!=vec.end(); pos++)
    {
        cout << *pos << " ";
    }

    return 0;
}
