/*
����һ���к��еڶ�����"23"�������������
����һ�����֣�123 423 5645 875 186523
������ڶ��У�23
����һ���к��еڶ����С�23���������������
�������123 423 186523
*/
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int main0519()
{
    string str;
    getline(cin,str);
    vector<string> vec;
    stringstream io(str);
    string temp;

    while(io >> temp)
    {
        vec.push_back(temp);
    }

    string sub;
    cin >> sub;

    for(vector<string>::iterator it=vec.begin(); it!=vec.end(); it++)
    {
        temp = *it;

        if(temp.find(sub)!=string::npos)
        {
            cout << temp << " ";
        }
    }

    return 0;
}
