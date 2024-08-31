/**
 * 整数排序
 * 描述:
 * 实现输入一组大于等于0的整数，根据从小到大的顺序排序后输出，
 * 排序后有连续数时，只输出连续数中最小和最大的两个数。
 * 输入:
 * 一组大于等于0的整数，不考虑非法输入，各个整数之间以逗号(“,”)分隔,
 * 输入字符串的总长度小于等于100个字节。
 * 输出:
 * 排序后的值，各个整数之间以空格分隔。
 * 样例输入:
 * 1,4,3,110,2,90,7
 * 样例输出:
 * 1 4 7 90 110
 *
 */
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <vector>

using namespace std;

int main()
{
    vector<int> vec;
    string input;
    cin >> input;
    string::size_type pos = input.find(",");

    while(pos != string::npos)
    {
        istringstream iss(input.substr(0,pos));
        int temp;
        iss >> temp;
        vec.push_back(temp);
        input = input.substr(pos+1);
        pos = input.find(",");
    }

    istringstream iss(input.substr(0,pos));
    int temp;
    iss >> temp;
    vec.push_back(temp);
    input = input.substr(pos+1);

    sort(vec.begin(),vec.end());

    for(vector<int>::size_type i=0;i<vec.size();i++)
    {
        if((i!=0) && (i!=vec.size()-1) && (vec[i]==vec[i-1]+1) && (vec[i]==vec[i+1]-1))
        {
            continue;
        }
        else
        {
            cout << vec[i] << " ";
        }
    }

    return 0;
}
