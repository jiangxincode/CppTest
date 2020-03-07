/**
 * 二维数组的列排序
 * 给出一个二维数组，请将这个二维数组按第i列(i从1开始)排序，如果第i列相同，则对相同的行按第i+1列的元素排序，如果第i+1列的元素也相同，则继续比较第i+2列，以此类推，直到最后一列。如果第i列到最后一列都相同，则按原序排列。
 *
 * 实现以下接口：
 * 输入一个m*n 的整数数组，实现按规则排列，返回排列后的数组。
 * 调用者会保证：
 * 比如输入数组为：
 * 1,2,3
 * 2,3,4
 * 2,3,1
 * 1,3,1
 * 按第二列排序：
 * 输出：
 * 1,2,3
 * 2,3,1
 * 1,3,1
 * 2,3,4
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <iostream>


/**
 * 交换二维数组的两行数据
 */
void ExchangeLine(int *pArray, unsigned int row, unsigned int line1, unsigned int line2)
{
    for(unsigned int i=0; i<row; i++)
    {
        int temp = *(pArray+line1*row+i);
        *(pArray+line1*row+i) = *(pArray+line2*row+i);
        *(pArray+line2*row+i) = temp;
    }
}

/* 功能：排列一个m行n列 大小的数组
 * 输入： int * pArray 指向数组第一个元素的指针,m为行数， n为列数 ，请按第i列排列
 * 输出：按第i列排序完成后的数组放到入参指定的地址中	(i的取值范围 1 - n)
 * 返回：
 */
void RangeArray(int * pArray, unsigned int m, unsigned int n, unsigned int i)
{
    i--; //将i的范围由1-n改为0-(n-1)
    if((pArray==NULL) || (i<0) || (i>=n) || (m<=0) || (n<=0))
    {
        return;
    }

    /*将各行按照特定的顺序进行冒泡排序*/
    for(unsigned int j=1; j<m; j++)
    {
        int flag = 0;

        for(unsigned int k=m-1; k>=j; k--)
        {
            unsigned int p = i;
            while(p < n)
            {
                if(*(pArray+k*n+p) < *(pArray+(k-1)*n+p))
                {
                    ExchangeLine(pArray,n,k-1,k);
                    flag = 1;
                    break;
                }
                else if(*(pArray+k*n+p) == *(pArray+(k-1)*n+p))
                {
                    p++;
                }
                else
                {
                    break;
                }
            }
        }

        if(flag == 0)
        {
            return;
        }
    }
}

bool CmpArray(int * pRet,int * pResult,unsigned int m,unsigned int n)
{
    for (unsigned int i = 0; i < m*n;++i)
    {
        if (*(pResult+i) != *(pRet+i))
        {
            return false;
        }
    }
    return true;

}

int main() {
    {
        int pArray[2][4] = {{2,3,4,5},{3,7,8,10}};
        int RetArray[2][4] = {{2,3,4,5},{3,7,8,10}};


        RangeArray(&pArray[0][0],2,4,1);


        std::cout << (CmpArray(&RetArray[0][0],&pArray[0][0],2,4)) << std::endl;

    }

    {
        int pArray[4][3] = {{1,2,3},{2,3,4},{2,3,1},{1,3,1}};
        int RetArray[4][3] = {{1,2,3},{2,3,1},{1,3,1},{2,3,4}};


        RangeArray(&pArray[0][0],4,3,2);


        std::cout << (CmpArray(&RetArray[0][0],&pArray[0][0],4,3)) << std::endl;

    }

    {
        int pArray[1][3] = {1,2,3};
        int RetArray[1][3] = {1,2,3};


        RangeArray(&pArray[0][0],1,3,1);


        std::cout << (CmpArray(&RetArray[0][0],&pArray[0][0],1,3)) << std::endl;

    }
}








//#include <vector>
//#include <iostream>
//#include <algorithm>
//
//using namespace std;
//
//unsigned int row = 0;
//
//bool CompareBySomeRow(vector<int> vec1, vector<int> vec2) //如何正确的传参数
//{
//    return vec1[row] < vec2[row];
//}
//
//
//void RangeArrayBySomeRow(vector<vector<int>> vec, unsigned int i)
//{
//    stable_sort(vec.begin(),vec.end(),CompareBySomeRow); //泛型算法是在编译其决定么？row是否能够动态改变？
//}
//
//
//// 功能：排列一个m行n列 大小的数组
//// 输入： int * pArray 指向数组第一个元素的指针,m为行数， n为列数 ，请按第i列排列
//// 输出：按第i列排序完成后的数组放到入参指定的地址中	(i的取值范围 1 - n)
//// 返回：
//void RangeArray(int * pArray, unsigned int m, unsigned int n, unsigned int i)
//{
//    vector<vector<int>> vec;
//
//    for(unsigned int i=0; i<m; i++)
//    {
//        vector<int> temp;
//
//        for(unsigned int j=0; j<n; j++)
//        {
//            temp.push_back(*(pArray+i*n+j));
//        }
//
//        vec.push_back(temp);
//    }
//
//    //for(unsigned int j=i-1;j<n;j++)
//    for(unsigned int j=n-1; j>=i-1; j--) //注意此处一定要倒序
//    {
//        row = j;
//
//        for(unsigned int i=0; i<m; i++)
//        {
//            for(unsigned int j=0; j<n; j++)
//            {
//                cout << *(pArray+i*n+j) << " ";
//            }
//
//            cout << endl;
//        }
//
//        cout << endl;
//        RangeArrayBySomeRow(vec,j);
//    }
//
//    for(unsigned int i=0; i<m; i++)
//    {
//        vector<int> temp = vec[i];
//
//        for(unsigned int j=0; j<n; j++)
//        {
//            *(pArray+i*n+j) = temp[j];
//        }
//    }
//}
