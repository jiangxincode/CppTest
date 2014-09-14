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
    //价格与折扣率计算得到结果，结果保留到10位
    result = ((int)(price*(discount/10)+5))/10*10;
    cout << result;
    return 0;
}
