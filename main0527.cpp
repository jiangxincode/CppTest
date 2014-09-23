/*
2014 美团一面
矩阵输出
输入M N
则随机产生矩阵：
    0   184    63   265   191   157   114
  293   269   244    57   281   232   168
   99     4    29   119    48    54   323
  146    39     1     2   123   174   187
然后按序输出
114
157 168
191 232 323
265 281 54 187
63 57 48 174
184 244 119 123
0 269 29 2
293 4 1
99 39
146
*/
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main0527()
{
    int M,N;
    cin >> M >> N;
    int test[M][N];
    for(int i=0;i<M;i++)
    {
        for(int j=0;j<N;j++)
        {
            test[i][j] = rand()/100;
        }
    }
    for(int i=0;i<M;i++)
    {
        for(int j=0;j<N;j++)
        {
            cout << setw(5) << test[i][j] << " ";
        }
        cout << endl;
    }
    if(M <= N)
    {
        for(int j=N-1;j>N-M;j--)
        {
            int temp = j;
            for(int i=0;temp<N;temp++,i++)
            {
                cout << test[i][temp] << " ";
            }
            cout << endl;
        }
        for(int j=N-M;j>=0;j--)
        {
            int temp = j;
            for(int i=0;i<M;temp++,i++)
            {
                cout << test[i][temp] << " ";
            }
            cout << endl;
        }
        for(int i=1;i<M;i++)
        {
            int temp = i;
            for(int j=0;temp < M;temp++,j++)
            {
                cout << test[temp][j] << " ";
            }
            cout << endl;
        }
    }
    else
    {
        for(int j=N-1;j>0;j--)
        {
            int temp = j;
            for(int i=0;temp<N;temp++,i++)
            {
                cout << test[i][temp] << " ";
            }
            cout << endl;
        }
        for(int i=0;i<N-1;i++)
        {
            int temp = i;
            for(int j=0;j<N;j++,temp++)
            {
                cout << test[temp][j] << " ";
            }
            cout << endl;
        }
        for(int i=N-1;i<M;i++)
        {
            int temp = i;
            for(int j=0;temp<M;temp++,j++)
            {
                cout << test[temp][j] << " ";
            }
            cout << endl;
        }
    }

    return 0;
}
