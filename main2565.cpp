/*
�������µ����飬ʵ������Ԫ�ؽ���λ�ú�����void swap(int a[], int m, int n);
���磬��mΪ3��nΪ4��a�е�����Ϊ��1 2 3 4 5 6 7������ִ�к�a�е�����Ϊ��4 5 6 7 1 2 3��
*/
#include <iostream>
#include <unistd.h>

using namespace std;

int judge_pos(int i,int m,int n)
{
    if(i>=0 && i<m)
    {
        return i+n;
    }
    else if(i>=m && i<(m+n))
    {
        return i-m;
    }
    else
    {
        return -1;
    }
}
int main2565()
{
    int num_of_data;
    int i_array[1024];
    int m,n;

    cout << "How many numbers do you want to input: ";
    cin >> num_of_data;
    cout << "Input the numbers,separate with space: " << endl;
    for(int i=0;i<num_of_data;i++)
    {
        cin >> i_array[i];
    }
    cout << "Input m and n,separate with space�� " << endl;
    cin >> m >> n;

    int i = 0;
    while(i_array[i]>=0)
    {
        for(int j=0;j<(m+n);j++)
        {
            if(judge_pos(j,m,n)==i)
            {

                if(i_array[j]>0)
                {
                    int temp = i_array[i];
                    i_array[i] = -i_array[j];
                    i_array[j] = temp;
                    i=j;
                    break;
                }
                else
                {
                    i_array[i] *= (-1);
                    i=j;
                    break;
                }

            }
        }
    }
    for(int i=0;i<num_of_data;i++)
    {
        if(i<(m+n))
        {
            i_array[i] *= (-1);
        }
        cout << i_array[i] << " ";
    }
    return 0;
}
