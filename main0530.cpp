/*
��Ϊ�ϻ���
������Ϊ2��������32λ���ȡ�Ȼ���������
*/
#include <iostream>

using namespace std;

int main0530()
{
    int num;
    string bin = "";
    cin >> num;
    while(num!=0)
    {
        bin += ((num%2)?'1':'0');
        num /=2;
    }
    while(bin.length()<32)
    {
        bin = "0"+bin;
    }
    cout << bin << endl;
    string::reverse_iterator r_it;
    for(r_it = bin.rbegin();r_it!=bin.rend();r_it++)
    {
        cout << *r_it;
    }
    return 0;
}
