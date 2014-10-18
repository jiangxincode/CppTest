/*
将第一行中含有第二行中"23"的数输出并排序
输入一行数字：123 423 5645 875 186523
在输入第二行：23
将第一行中含有第二行中“23”的数输出并排序
结果即：123 423 186523
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
