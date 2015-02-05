/*
南京市普通出租车的收费标准是：
3公里以内（含3公里）收费9元，
超过3公里的部分，每公里收费2.4元，另外每车次加收2元燃油附加费。
设计程序，计算输入的公里数x所对应的车费y，并输出。
*/
#include <iostream>
using namespace std;

int main2525()
{
    float f_miles = 0.0,f_price = 0.0;
    cout << "请输入行驶的公里数： ";
    cin >> f_miles;

    if(f_miles <= 3)
    {
        f_price = 9.0;
    }
    else
    {
        f_price = 9.0 +(f_miles-3)*2.4+2.0;
    }

    cout << "车费为： " << f_price;
    return 0;
}
