/**
 * 火车进站
 * 描述:
 * 给定一个正整数N代表火车数量，0<N<10，接下来输入火车入站的序列，
 * 一共N辆火车，每辆火车以数字1-9编号。要求以字典序排序输出火车出站的序列号。
 * 输入:
 * 有多组测试用例，每一组第一行输入一个正整数N（0<N<10），第二行包括N个正整数，范围为1到9。
 * 输出:
 * 输出以字典序排序的火车出站序列号，每个编号以空格隔开，每个输出序列换行，具体见sample。
 * 样例输入:
 * 3
 * 1 2 3
 * 样例输出:
 * 1 2 3
 * 1 3 2
 * 2 1 3
 * 2 3 1
 * 3 2 1
 *
 */
//review
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

int main()
{
    int num;
    string str="ABCDEFGHIJ",a;
    vector<string> tmp;
    cin >> num;
    getchar();
    getline(cin,a);
    str=str.substr(0,num);
    tmp.push_back(str);

    while(next_permutation(str.begin(),str.end()))
    {
        tmp.push_back(str); //得到全排列
    }

    for(vector<string>::size_type i=0; i<tmp.size(); i++)
    {
        string s=tmp[i];
        int len=s.size();

        for(int j=0; j<len; j++)
        {
            if(s[j]>s[0])
            {
                s.erase(j);
                len--;
            }
        }

        string q=s;
        sort(s.rbegin(),s.rend());

        if(q!=s)
        {
            tmp.erase(i+tmp.begin());
        }
    }

    for(vector<string>::size_type j=0; j<tmp.size(); j++)
    {
        for(int i=0; i<num; i++)
        {
            replace(tmp[j].begin(),tmp[j].end(),str[i],a[i*2]);
        }
    }

    sort(tmp.begin(),tmp.end());

    for(vector<string>::size_type i=0; i<tmp.size(); i++)
    {
        string m;
        m=tmp[i];

        for(vector<string>::size_type k=0; k<m.size(); k++)
        {
            cout<<m[k];

            if(k==m.size()-1)
            {
                cout<<endl;
            }
            else
            {
                cout<<" ";
            }
        }
    }
    return 0;
}
