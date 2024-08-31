/**
 * 合唱队
 * 描述:  计算最少出列多少位同学，使得剩下的同学排成合唱队形
 * 说明：
 * N位同学站成一排，音乐老师要请其中的(N-K)位同学出列，使得剩下的K位同学排成合唱队形。
 * 合唱队形是指这样的一种队形：
 * 设K位同学从左到右依次编号为1，2…，K，他们的身高分别为T1，T2，…，TK，
 * 则他们的身高满足存在i（1<=i<=K）使得Ti<T2<......<Ti-1<Ti>Ti+1>......>TK。
 * 你的任务是，已知所有N位同学的身高，计算最少需要几位同学出列，
 * 可以使得剩下的同学排成合唱队形。
 * 输入:
 * 整数N
 * 一行整数，空格隔开，N位同学身高
 * 输出:
 * 最少需要几位同学出列
 * 样例输入:
 * 8
 * 186 186 150 200 160 130 197 200
 * 样例输出:
 * 4
 */
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int n; //合唱队总人数
    int arr[100]; //合唱队身高数组
    int answer = 0; //符合条件的最大合唱队人数

    cin >> n;

    for(int i=0; i<n; i++)
    {
        cin >> arr[i];
    }

    int *listrise = new int[n]; //最长上升子序列

    for(int i=0; i<n; i++)
    {
        listrise[i] = 1;

        for(int j=0; j<i; j++)
        {
            if((arr[i]>arr[j]) && (listrise[j]+1>listrise[i]))
            {
                listrise[i] = listrise[j]+1;
            }
        }
    }

    int *listdown = new int[n]; //最长下降子序列

    for(int i=n-1; i>=0; i--)
    {
        listdown[i] = 1;

        for(int j=n-1; j>i; j--)
        {
            if((arr[i]>arr[j]) && (listdown[j]+1>listdown[i]))
            {
                listdown[i] = listdown[j] + 1;
            }
        }
    }

    for(int i=0; i<n; i++) //符合条件的最长子序列
    {
        if(listrise[i] + listdown[i] - 1 > answer)
        {
            answer = listrise[i] + listdown[i] - 1;
        }
    }

    cout << n-answer << endl;
    delete []listdown;
    delete []listrise;
    return 0;
}
