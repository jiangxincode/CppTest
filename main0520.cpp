/*
有9个整数｛1，2，3，4，5，6，7，8，9｝在中间任何位置加上‘+’或这‘-’号使成为一个表达式，
这个表达式的值要等于你输入的一个整数，
要你输出有多少种这样的表达式它的值等于你输入的这个数
例如：
123-4+56-78+9=106
XXXXXXXXXXX=106
.........
XXXXXXXXXXX=106
最后输出表达式的个数
*/
#include <iostream>
#include <cmath>

using namespace std;

bool calc(int result,int target,int seq)
{
    if(result == target && seq == 10)
    {
        //cout << "success!" << endl;
        return true;
    }
    else if(seq == 10)
    {
        return false;
    }

    if(calc(result*10+seq,target,seq+1))
    {
        cout << seq;
    }

    if(calc(result+seq,target,seq+1))
    {
        cout << "+" << seq;
    }

    if(calc(result-seq,target,seq+1))
    {
        cout << "-" << seq;
    }
    return false;
}
int main0520()
{
    int target;
    string temp[(int)pow(3,8)];
    int num = 0;
    string source = "123456789";
    for(int i=2;i<9;i++)
    {
        temp[num++] = source.insert(i,"");
        temp[num++] = source.insert(i,"+");
        temp[num++] = source.insert(i,"-");
    }
    cin >> target;
    calc(1,target,2);
    cout << "1";
    return 0;
}
