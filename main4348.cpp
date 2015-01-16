//unsolved 结果错误，包括本地，需要仔细debug

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "oj.h"

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

unsigned int row = 0;

bool CompareBySomeRow(vector<int> vec1, vector<int> vec2) //如何正确的传参数
{
    return vec1[row] < vec2[row];
}


void RangeArrayBySomeRow(vector<vector<int>> vec, unsigned int i)
{
    stable_sort(vec.begin(),vec.end(),CompareBySomeRow); //泛型算法是在编译其决定么？row是否能够动态改变？
}


// 功能：排列一个m行n列 大小的数组
// 输入： int * pArray 指向数组第一个元素的指针,m为行数， n为列数 ，请按第i列排列
// 输出：按第i列排序完成后的数组放到入参指定的地址中	(i的取值范围 1 - n)
// 返回：
void RangeArray(int * pArray,unsigned int  m, unsigned int  n,unsigned int  i)
{
    vector<vector<int>> vec;
    for(unsigned int i=0;i<m;i++)
    {
        vector<int> temp;
        for(unsigned int j=0;j<n;j++)
        {
            temp.push_back(*(pArray+i*n+j));
        }
        vec.push_back(temp);
    }
    //for(unsigned int j=i-1;j<n;j++)
    for(unsigned int j=n-1;j>=i-1;j--) //注意此处一定要倒序
    {
        row = j;
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<n;j++)
            {
                cout << *(pArray+i*n+j) << " ";
            }
            cout << endl;
        }
        cout << endl;
        RangeArrayBySomeRow(vec,j);
    }
    for(unsigned int i=0;i<m;i++)
    {
        vector<int> temp = vec[i];
        for(unsigned int j=0;j<n;j++)
        {
            *(pArray+i*n+j) = temp[j];
        }
    }

}
int main4348()
{
//    int pArray[2][4] = {2,3,4,5,3,7,8,10};
//    RangeArray(&pArray[0][0],2,4,1);
//    for(unsigned int i=0;i<2;i++)
//    {
//        for(unsigned int j=0;j<4;j++)
//        {
//            cout << pArray[i][j] << " ";
//        }
//        cout << endl;
//    }
//
//    int RetArray[2][4] = {2,3,4,5,3,7,8,10};
//    for(unsigned int i=0;i<2;i++)
//    {
//        for(unsigned int j=0;j<4;j++)
//        {
//            cout << RetArray[i][j] << " ";
//        }
//        cout << endl;
//    }

    int pArray[4][3] = {1,2,3,2,3,4,2,3,1,1,3,1};
    RangeArray(&pArray[0][0],4,3,2);
    for(unsigned int i=0;i<4;i++)
    {
        for(unsigned int j=0;j<3;j++)
        {
            cout << pArray[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;

    int RetArray[4][3] = {1,2,3,2,3,1,1,3,1,2,3,4};
    for(unsigned int i=0;i<4;i++)
    {
        for(unsigned int j=0;j<3;j++)
        {
            cout << RetArray[i][j] << " ";
        }
        cout << endl;
    }



    return 0;
}




