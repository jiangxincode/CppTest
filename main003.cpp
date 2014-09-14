#include <iostream>
#include <string>
/*
给定一个query和一个text，均由小写字母组成。
要求在text中找出以同样的顺序连续出现在query中的最长连续字母序列的长度。
例如， query为“acbac”，text为“acaccbabb”，
那么text中的“cba”为最长的连续出现在query中的字母序列，
因此，返回结果应该为其长度3。
请注意程序效率。
2015 阿里巴巴 数据研发工程师 在线笔试
*/
using namespace std;

int main003()
{
    string text,query;
    cout << "Input text: " << endl;
    cin >> text;
    cout << "Input query: " << endl;
    cin >> query;
    string::size_type len = 0;
    for(string::size_type i=0; i<query.length(); i++)
    {
        for(string::size_type j=query.length()-1; j>i; j--)
        {
            string temp = query.substr(i,j);
            if(text.find(temp) != string::npos)
            {
                if((j-i)>len)
                {
                    len = j - i + 1; //i和j位置之中共有(j-i+1)个元素
                }
            }
        }
    }
    cout << len;
    return 0;
}
