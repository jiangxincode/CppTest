/**
 * 报数
 * 描述:  有n个人围成一圈，顺序排号。
 * 从第一个人开始报数（从1到3报数），凡报到3的人退出，问最后留下的那位是原来第几号。
 * 输入:
 * 使用标准输入stdio.多行，每行一组数据。
 * 输出:
 * 多行，每行对应求和结果。
 * 样例输入: 3
 * 样例输出: 2
 *
 */
#include <iostream>
using namespace std;
int main()
{
    int n;

    while(cin >> n)
    {
        int *pArray = new int[n];

        for(int i=0; i<n; i++)
        {
            pArray[i] = 1;
        }

        int count = 0;
        int i = 0;

        while(count < n-1)
        {
            int temp = 1;

            while(1)
            {
                if(pArray[i%n] == 1)
                {
                    if(temp%3 == 0)
                    {
                        pArray[i%n] = 0;
                        count ++;
                        i++;
                        break ;
                    }

                    temp++;
                    i++;
                }
                else
                {
                    i ++;
                }
            }
        }

        for(int i=0; i<n; i++)
        {
            if(pArray[i] == 1)
            {
                cout << i+1 << endl;
            }
        }
        delete []pArray;
    }

    return 0;
}
