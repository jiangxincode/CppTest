/**
 * 1012 最大公约数和最小公倍数问题
 * 2001年NOIP全国联赛普及组
 * 时间限制: 1 s
 * 空间限制: 128000 KB
 * 题目等级 : 白银 Silver
 * 题目描述 Description
 * 输入二个正整数x0,y0(2<=x0<100000,2<=y0<=1000000),求出满足下列条件的P,Q的个数
 * 条件:
 * 1.P,Q是正整数
 * 2.要求P,Q以x0为最大公约数,以y0为最小公倍数.
 * 试求:满足条件的所有可能的两个正整数的个数.
 * 输入描述 Input Description
 * 二个正整数x0,y0
 * 输出描述 Output Description
 * 满足条件的所有可能的两个正整数的个数
 * 样例输入 Sample Input
 * 3 60
 * 样例输出 Sample Output
 * 4
 * 数据范围及提示 Data Size & Hint
 */
#include <iostream>
#include <map>
#include <utility> //for pair

using namespace std;

static int gcd(int min,int max)
{
    if(max%min == 0)
    {
        return min;
    }
    else
    {
        return gcd(max%min,min); //牛顿迭代相除法
    }
}

int lcm(int min,int max)
{
    return min*max/gcd(min,max); //最小公倍数为两者之积除以两者的最大公约数
}
int main1012()
{
    int X0,Y0;
    map<int,int> map_result;
    cin >> X0 >> Y0;

    for(int P=X0; P<=Y0; P+=X0)
    {
        for(int Q=X0; Q<=Y0; Q+=X0)
        {
            if((gcd(P,Q)==X0) && (lcm(P,Q)==Y0))
            {
                map_result.insert(pair<int,int>(P,Q)); //注意pair的用法
            }
        }
    }

//    for(map<int,int>::iterator it=map_result.begin();it!=map_result.end();it++)
//    {
//        cout << it->first << " " << it->second << endl;
//    }
    cout << map_result.size();
    return 0;
}
