﻿/**
华为笔试题
写一个程序, 要求功能：求出用1，2，5这三个数不同个数组合的和为100的组合个数。
如：100个1是一个组合，5个1加19个5是一个组合。
*/
#include <iostream>

using namespace std;

/**
最容易想到的算法是：
设x是1的个数，y是2的个数，z是5的个数，number是组合数
*/

int combine1()
{
    int count = 0;

    for(int i=0; i<=100; i++)
    {
        for(int j=0; j<=50; j++)
        {
            for(int k=0; k<20; k++)
            {
                if((i+2*j+5*k) == 100)
                {
                    count ++;
                }
            }
        }
    }

    return count;
}

/**
上面这个程序一共要循环100*50*20次，效率实在是太低了
事实上，这个题目是一道明显的数学问题，而不是单纯的编程问题。我的解法如下：
因为x+2y+5z=100
所以x+2y=100-5z，且z<=20 x<=100 y<=50
所以(x+2y)<=100，且(x+5z)是偶数
对z作循环，求x的可能值如下：

z=0, x=100, 98, 96, ... 0
z=1, x=95, 93, ..., 1
z=2, x=90, 88, ..., 0
z=3, x=85, 83, ..., 1
z=4, x=80, 78, ..., 0
......
z=19, x=5, 3, 1
z=20, x=0

因此，组合总数为100以内的偶数+95以内的奇数+90以内的偶数+...+5以内的奇数+1，即为：
(51+48)+(46+43)+(41+38)+(36+33)+(31+28)+(26+23)+(21+18)+(16+13)+(11+8)+(6+3)+1
某个偶数m以内的偶数个数（包括0）可以表示为m/2+1=(m+2)/2
某个奇数m以内的奇数个数也可以表示为(m+2)/2
所以，求总的组合次数可以编程为：
number=0;
for (int m=0;m<=100;m+=5)
{
number+=(m+2)/2;
}
cout<<number<<endl;
这个程序,只需要循环21次, 两个变量，就可以得到答案,比上面的那个程序高效了许多倍
只是因为作了一些简单的数学分析。
这再一次证明了：计算机程序=数据结构+算法，而且算法是程序的灵魂，
对任何工程问题，当用软件来实现时，必须选取满足当前的资源限制，用户需求限制，
开发时间限制等种种限制条件下的最优算法。
而绝不能一拿到手，就立刻用最容易想到的算法编出一个程序了事——
这不是一个专业的研发人员的行为。
那么，那种最容易想到的算法就完全没有用吗？
不，这种算法正好可以用来验证新算法的正确性，在调试阶段，这非常有用。
在很多大公司，例如微软，都采用了这种方法：
在调试阶段，对一些重要的需要好的算法来实现的程序，
而这种好的算法又比较复杂时，同时用容易想到的算法来验证这段程序，
如果两种算法得出的结果不一致（而最容易想到的算法保证是正确的），
那么说明优化的算法出了问题，需要修改。
*/
int main()
{
    cout << combine1() << endl;
    return 0;
}