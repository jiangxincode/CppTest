/*��дһ������digit(n,k)������������n�Ĵ�������ĵ�k�����֡����磺
digit(123456,3) = 4
digit(1234,5) = 0
*/
#include <iostream>

using namespace std;

int digit(int integer,int position)
{
    int result;

    for(int i=0; i<position; i++)
    {
        result = integer % 10;
        integer /= 10;
    }

    return result;
}
int main2542()
{
    int i_integer,i_position;
    cout << "Input the integer and the position: ";
    cin >> i_integer >> i_position;
    cout << digit(i_integer,i_position);
    return 0;
}

