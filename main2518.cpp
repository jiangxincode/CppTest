﻿#include <iostream>
#include <cmath>
using namespace std;
int main2518()
{
    cout << "请输入a,b,c的值：";
    int a,b,c;
    cin >> a >> b >> c;
    float delta = b * b - 4 * a * c;

    if(delta >= 0)
    {
        float result1 = (-b + sqrt(delta)) / float(2*a);
        float result2 = (-b - sqrt(delta)) / float(2*a);
        printf("result1 is %.2f and result2 is %.2f",result1, result2);
    }
    else
    {
        cout << "No result";
    }
    return 0;
}
