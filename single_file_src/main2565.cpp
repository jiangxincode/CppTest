/**
 * 不引入新的数组，实现数组元素交换位置函数：
 * void swap(int a[], int m, int n);
 * 要求将数组中的前m个元素和后n个元素交换位置。
 * 比如，设m为3，n为4，a中的数据为：1 2 3 4 5 6 7，函数执行后，a中的数据为：4 5 6 7 1 2 3。
 *
 * 感觉这道题出的有些问题，没有说数组总长度total_lenght和(m+n)的大小关系。
 * 鉴于网上给出的一般答案，我们暂时认为total_lenght == (m+n)
 */
#include <iostream>
#include <unistd.h>

using namespace std;

void print_array(int a[], int length)
{
	for (int i=0; i<length; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}

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

void swap(int a[], int m, int n)
{
	int i = 0;
	while (a[i] >= 0)
	{
		for (int j = 0; j < (m + n); j++)
		{
			if (judge_pos(j, m, n) == i)
			{
				if (a[j] > 0)
				{
					int temp = a[i];
					a[i] = -a[j];
					a[j] = temp;
					i = j;
					break;
				}
				else
				{
					a[i] *= (-1);
					i = j;
					break;
				}
			}
		}
	}
}

int main()
{
    int length;
    int a[1024];
    int m,n;
    cout << "Array length:";
    cin >> length;
    cout << "Array data(separated with space):" << endl;

    for(int i=0; i < length; i++)
    {
        cin >> a[i];
    }

    cout << "m and n(separated with space):" << endl;
    cin >> m >> n;

	swap(a, m, n);

    for(int i=0; i < length; i++)
    {
        if(i<(m+n))
        {
            a[i] *= (-1);
        }

        cout << a[i] << " ";
    }

    print_array(a, length);

    return 0;
}
