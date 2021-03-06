﻿/**
魔方阵问题
魔方阵是指每行、每列及对角线上的元素之和均相等。例如，3阶魔方阵为：
8   1   6
3   5   7
4   9   2
要求生成一个n阶魔方阵（n为奇数）并输出。
n阶魔方阵生成算法（n为奇数）:
1.将1放在方阵第1行中间位置,2 ~ n*n 按以下步骤放置:
2.下一个数的位置是当前已放数的右上方（上一行右侧列）
3.若右上方已超出方阵第一行但未超出最后一列，则下一个数的位置改为最后一行右侧列。
4.若右上方超出方阵最后一列但未超出第一行，则下一个数的位置改为上一行第一列。
5.若右上方同时超出方阵第一行和最后一列或右上方未超出方阵第一行和最后一列但已放数，
则下一个数的位置改为当前已放数的正下方。
input:
3
output:
8   1   6
3   5   7
4   9   2
*/
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n; //矩阵的阶
    int k; //代表从1到n*n之间的数
    int i,j; //用于循环变量
    scanf("%11d",&n);

    if(n%2 == 0) //判断是否为奇数
    {
        perror("Invalid input, need a odd number.");
        exit(1);
    }

	int** matrix = (int**)malloc(n * sizeof(int*));
	for (int i = 0; i < n; ++i)
	{
		matrix[i] = (int*)malloc(sizeof(int) * n);
	}

    for(i=0; i<n; i++) //初始化数组
    {
        for(j=0; j<n; j++)
        {
            matrix[i][j] = 0;
        }
    }

    /**
     * 只要对i,j进行++操作，就要对n取模
     * 只要对i,j进行--操作，就要先加n，然后对n取模
     */
    for(i=0,j=n/2,k=1; k<=n*n; i--,j++,k++)
    {
        i = (i+n)%n;
        j = j%n;

        if(k != 1) //不是填充数值1
        {
            if(matrix[i][j] != 0)
            {
                i ++; //恢复循环中对i,j的操作
                j --;
                i ++; //取当前位置的下一个位置
                i = i%n;
                j = (j+n)%n;
            }
        }

        matrix[i][j] = k;
    }

    for(i=0; i<n; i++) //输出
    {
        for(j=0; j<n; j++)
        {
            printf("%d\t",matrix[i][j]);
        }

        printf("\n");
    }
	free(matrix);

    return 0;
}
