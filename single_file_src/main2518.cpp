#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    cout << "请输入a,b,c的值：";
    int a,b,c;
    cin >> a >> b >> c;
    float delta = b * b - 4 * a * c;

    if(delta >= 0)
    {
        float result1 = (-b + sqrt(delta)) / float(2*a);
        float result2 = (-b - sqrt(delta)) / float(2*a);
        cout << "result1 is " << result1 << " and result2 is " << result2;
    }
    else
    {
        cout << "No result";
    }

    return 0;
}
