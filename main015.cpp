/*
http://wikioi.com/problem/1012/
*/
#include <iostream>
#include <map>
#include <utility> //for pair

using namespace std;

int gcd(int min,int max)
{
    if(max%min == 0)
    {
        return min;
    }
    else
    {
        return gcd(max%min,min); //ţ�ٵ��������
    }
}

int lcm(int min,int max)
{
    return min*max/gcd(min,max); //��С������Ϊ����֮���������ߵ����Լ��
}
int main015()
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
                map_result.insert(pair<int,int>(P,Q)); //ע��pair���÷�
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
