/*
http://wikioi.com/problem/2235/
*/
#include <iostream>

using namespace std;

int main008()
{
    int price;
    float discount;
    int result;
    cin >> price >> discount;
    //�۸����ۿ��ʼ���õ���������������10λ
    result = ((int)(price*(discount/10)+5))/10*10;
    cout << result;
    return 0;
}
