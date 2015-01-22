/**
描述:  给出一个名字，该名字有26个字符串组成，定义这个字符串的“漂亮度”是其所有字母“漂亮度”的总和。
每个字母都有一个“漂亮度”，范围在1到26之间。没有任何两个字母拥有相同的“漂亮度”。字母忽略大小写。
给出多个名字，计算每个名字最大可能的“漂亮度”。

输入:  整数N，后续N个名字(N个字符串，每个表示一个名字)
输出:  每个名称可能的最大漂亮程度

样例输入:
2
zhangsan
lisi

样例输出:
192
101
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>

using namespace std;

bool CompareByValue(pair<char,int> pair1,pair<char,int> pair2)
{
    return pair1.second > pair2.second;
}

int getBeautyDegree(string name)
{
    map<char,int> mapCharNum;
    vector<pair<char,int>> vecCharNum;
    int result = 0;
    for(string::iterator it=name.begin();it!=name.end();it++)
    {
        char ch = *it;
        if(mapCharNum.find(ch) == mapCharNum.end())
        {

            pair<char,int> pairCharNum(ch,1);
            mapCharNum.insert(pairCharNum);
        }
        else
        {
            mapCharNum[ch]++;
        }
    }

    for(map<char,int>::iterator it=mapCharNum.begin();it!=mapCharNum.end();it++)
    {
        pair<char,int> pairCharNum = *it;
        vecCharNum.push_back(pairCharNum);
    }

    //copy(mapCharNum.begin(),mapCharNum.end(),vecCharNum.begin());
    sort(vecCharNum.begin(),vecCharNum.end(),CompareByValue);

    int weight=26;
    for(vector<pair<char,int>>::iterator it=vecCharNum.begin();it!=vecCharNum.end();it++)
    {
        pair<char,int> pairNameChar(*it);
        result += pairNameChar.second*(weight--);
    }
    return result;
}

int main4238()
{
    int num;
    vector<string> vecName;
    vector<int> vecResult;
    cin >> num;
    for(int i=0;i<num;i++)
    {
        string name;
        cin >> name;
        vecName.push_back(name);
    }
    for(vector<string>::iterator it=vecName.begin();it!=vecName.end();it++)
    {
        vecResult.push_back(getBeautyDegree(*it));
    }
    for(vector<int>::iterator it=vecResult.begin();it!=vecResult.end();it++)
    {
        cout << *it << endl;
    }
    return 0;
}
