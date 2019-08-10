/*
输出正整数 d1~d2 之间（含d1、d2）不能被整数 d3 整除的整数
（用户每输入一次d1、d2、d3的值，就输出一次结果，输入0结束）。
*/
#include <iostream>
using namespace std;
int main()
{
    int d1,d2,d3;
    cout << "\nInput d1,d2 and d3: ";
    cin >> d1 >> d2 >> d3;

    while(d3!=0)
    {
        for(int i=d1; i<=d2; i++)
        {
            if(i%d3!=0)
            {
                cout << i << "\t";
            }
        }

        cout << "\nInput d1,d2 and d3: ";
        cin >> d1 >> d2 >> d3;
    }

    return 0;
}
