/**
 * 矩阵相乘2
 * 题目描述：
 * 矩阵相乘
 * 输入：两个N*N阶矩阵相乘
 * 输出：结果矩阵
 * 样例输入：
 * {1, 2, 3}, {4, 5, 6}, {7, 8, 9}
 * {1, 2, 3}, {4, 5, 6}, {7, 8, 9}
 * 样例输出：
 * {30, 36, 42}, {66, 81, 96}, {102, 126, 150}
 * 接口说明：
 * 原型：
 * int matrix(int **MatrixA, int **MatrixB, int **MatrixC, int N);
 * 输入参数：
 *    int **MatrixA  指向二维数组A
 *        int **MatrixB  指向二维数组A
 *        int N          二维数组大小
 * 输出参数：
 *     int **MatrixC
 * 返回值：0：成功  1：失败
 *
 */
#include "iostream"
#include "cstring"
/*
功能: 矩阵相乘

输入: MatrixA,MatrixB

输出: MatrixC

返回: 0

*/

int matrix(int **MatrixA, int **MatrixB, int **MatrixC, int N)
{
    int* A = (int*)MatrixA;
    int* B = (int*)MatrixB;
    int* C = (int*)MatrixC;

    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            *(C+i*N+j) = 0;
            for(int k=0;k<N;k++)
            {
                *(C+i*N+j) += *(A+i*N+k) * *(B+k*N+j);
            }
        }
    }
    return 0;
}

int main()
{
    int A[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int C[3][3], ExpectC[3][3] = {{30, 36, 42}, {66, 81, 96}, {102, 126, 150}};

    matrix((int**)A, (int**)A, (int**)C, 3);

    std::cout << (0 == memcmp(C, ExpectC, sizeof(C))) << std::endl;
}
