#include <iostream>

using namespace std;

void main0504()
{
    for(int i=5;i<=11;i++)
    {
        for(int j=1;j<=6;j++)
        {
            for(int k=1;k<=4;k++)
            {
                int m = i*j*k;
                int condition = (m-i>=22) && (m<60) && (i+j+k == 13) && (i>=j) && (j>=k);
                if(condition)
                {
                    cout << i << " " << j << " " << k << " " << m << endl;
                }
            }
        }
    }
}
