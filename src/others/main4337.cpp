/**
 * 二维数组（矩阵）基本操作
 * 数据结构（结构体strmatrix）定义：
 * 二维数组行列最大规格MAXSIZE＝5
 * 所有用例能够保证rownum/columnnum和表中实际数据保持一致，无需考虑不一致的场景
 * 实现接口，每个接口实现1个基本操作：
 * 	void setnull(structstrmatrix *p)：实现数组内容清空
 * 	int getelementnum(structstrmatrix *p)：获取数组元素个数
 * 	int getxnum(structstrmatrix *p,intx)：获取数组中某个值的元素个数
 * 	void insertrow(structstrmatrix *p,inti,int*x)：在二维数组中插入一行，需考虑i为异常值，x为一维数组，长度和二维数组p的列数相等
 * 	void insertcolumn(structstrmatrix *p,inti,int*x)：在二维数组中插入一列，需考虑i为异常值，x为一维数组，长度和二维数组p的行数相等
 * 	void matrixtrans(structstrmatrix *p)：实现方矩阵的置换操作，所谓方矩阵，即行数和列行数相等的矩阵
 * 	void matrixwhirl(structstrmatrix *p)：实现方矩阵顺时针旋转90度操作
 * 	void matrixplus(structstrmatrix *plu,structstrmatrix *p,structstrmatrix *q)：实现两个矩阵相加，两个矩阵必须行数和列数都相等才能相加
 * 	void matrixmultiply(struct strmatrix *mul,struct strmatrix *p,struct strmatrix *q)：实现两个矩阵相乘，两个矩阵相乘，必须满足第一个的矩阵列数等于第二个矩阵的行数
 * 题目框架中有9个参考用例，其它用例请自行编写。
 */
#include <stdlib.h>
#include <iostream>

#define MAXSIZE 5

struct strmatrix
{
    int rownum; /* 二维数组行数 */
    int columnnum; /* 二维数组行数 */
    int matrix[MAXSIZE][MAXSIZE];
};

void setnull(struct strmatrix *p)  /*表置空*/
{
    for(int i=0; i<p->rownum; i++)
    {
        for(int j=0; j<p->columnnum; j++)
        {
            p->matrix[i][j] = 0;
        }
    }

    p->rownum = 0;
    p->columnnum = 0;
}

int getelementnum(struct strmatrix *p)  /*获取表中元素个数*/
{
    return p->rownum * p->columnnum;
}


int getxnum(struct strmatrix *p, int x) /*获得数组中等于某个值的元素的个数*/
{
    int num = 0;

    for(int i=0; i<p->rownum; i++)
    {
        for(int j=0; j<p->columnnum; j++)
        {
            if(p->matrix[i][j] == x)
            {
                num++;
            }
        }
    }

    return num;
}

void insertrow(struct strmatrix *p,int i,int *x) /* 插入1行 */
{
    if((i < 0) || (i >= MAXSIZE) || ((p->rownum+1) > MAXSIZE))
    {
        return;
    }

    for(int j=p->rownum; j>i; j--)
    {
        for(int k=0; k<p->columnnum; k++)
        {
            p->matrix[j][k] = p->matrix[j-1][k];
        }
    }

    for(int k=0; k<p->columnnum; k++)
    {
        p->matrix[i][k] = x[k];
    }

    p->rownum++;
}

void insertcolumn(struct strmatrix *p,int i,int *x) /* 插入1列 */
{
    if((i < 0) || (i >= MAXSIZE) || ((p->columnnum+1) > MAXSIZE))
    {
        return;
    }

    for(int j=p->columnnum; j>i; j--)
    {
        for(int k=0; k<p->rownum; k++)
        {
            p->matrix[k][j] = p->matrix[k][j-1];
        }
    }

    for(int k=0; k<p->rownum; k++)
    {
        p->matrix[k][i] = x[k];
    }

    p->columnnum++;
}


void matrixtrans(struct strmatrix *p) /* 方矩阵置换 */
{
    for(int i=0; i<p->rownum; i++)
    {
        for(int j=i+1; j<p->columnnum; j++)
        {
            int temp = p->matrix[i][j];
            p->matrix[i][j] = p->matrix[j][i];
            p->matrix[j][i] = temp;
        }
    }
}

void matrixwhirl(struct strmatrix *p) /* 方矩阵顺时针旋转90度 */
{
    /************************************************************************
    a00 a01 a02 a03 a04                  a40 a30 a20 a10 a00
    a10 a11 a12 a13 a14                  a41 a31 a21 a11 a01
    a20 a21 a22 a23 a24                  a42 a32 a22 a12 a02
    a30 a31 a32 a33 a34                  a43 a33 a23 a13 a03
    a40 a41 a42 a43 a44                  a44 a34 a24 a14 a04
   ************************************************************************/

    int temp[MAXSIZE][MAXSIZE];
    int column = 0;
    int row = 0;

    for(int i=0;i<p->rownum;i++)
    {
        row = p->rownum;
        for(int j=0;j<p->columnnum;j++)
        {
            temp[i][j] = p->matrix[--row][column];
        }
        column++;
    }

    for (int i=0;i<p->rownum;i++)
    {
        for(int j=0;j<p->columnnum;j++)
        {
            p->matrix[i][j] = temp[i][j];
        }
    }
}

void matrixplus(struct strmatrix *plu, struct strmatrix *p, struct strmatrix *q) /* 两个矩阵相加 */
{
    if((p->columnnum != q->columnnum) || (p->rownum != q->rownum))
    {
        return;
    }

    for(int i=0;i<p->rownum;i++)
    {
        for(int j=0;j<p->columnnum;j++)
        {
            plu->matrix[i][j] = p->matrix[i][j] + q->matrix[i][j];
        }
    }

    plu->rownum = p->rownum;
    plu->columnnum = p->columnnum;
}

void matrixmultiply(struct strmatrix *mul, struct strmatrix *p, struct strmatrix *q) /* 两个矩阵相乘 */
{
    if(p->columnnum != q->rownum)
    {
        return;
    }

    mul->rownum = p->rownum;
    mul->columnnum = q->columnnum;

    for(int i=0;i<mul->rownum;i++)
    {
        for(int j=0;j<mul->columnnum;j++)
        {
            mul->matrix[i][j] = 0;
            for(int k=0;k<p->columnnum;k++)
            {
                mul->matrix[i][j] += p->matrix[i][k] * q->matrix[k][j];
            }
        }
    }
}

int main() {

/* －－－－－－－－－－数组清空类用例－－－－－－－－－－－－－ */
        {
            int j = 0;
            int k = 0;
            int a[MAXSIZE][MAXSIZE] = { 1,  2,  3,  0,  0,
                                        4,  5,  6,  0,  0,
                                        7,  8,  9,  0,  0,
                                        0,  0,  0,  0,  0,
                                        0,  0,  0,  0,  0};
            struct strmatrix p = {0};
            p.rownum = 3;
            p.columnnum = 3;
            for(j = 0; j < MAXSIZE; j++)
            {
                for(k = 0; k < MAXSIZE; k++)
                {
                    p.matrix[j][k] = a[j][k];
                }
            }

            setnull(&p);

            std::cout << (p.rownum == 0) << std::endl;
            std::cout << (p.columnnum == 0) << std::endl;
            for(j = 0; j < MAXSIZE; j++)
            {
                for(k = 0; k < MAXSIZE; k++)
                {
                    std::cout << (p.matrix[j][k] == 0) << std::endl;
                }
            }
        }
/* －－－－－－－－－－数组清空类用例－－－－－－－－－－－－－ */

/* －－－－－－－－－－获取数组长度类用例－－－－－－－－－－－－－ */
        {
            int j = 0;
            int k = 0;
            int elementnum = 0;
            int a[MAXSIZE][MAXSIZE] = { 1,  2,  3,  4,  5,
                                        6,  7,  8,  9, 10,
                                        11, 12, 13, 14, 15,
                                        16, 17, 18, 19, 20,
                                        0,  0,  0,  0,  0};

            struct strmatrix p = {0};
            p.rownum = 4;
            p.columnnum = 5;
            for(j = 0; j < MAXSIZE; j++)
            {
                for(k = 0; k < MAXSIZE; k++)
                {
                    p.matrix[j][k] = a[j][k];
                }
            }

            elementnum = getelementnum(&p);

            std::cout << (elementnum == 20) << std::endl;
        }
/* －－－－－－－－－－获取数组长度类用例－－－－－－－－－－－－－ */

/* －－－－－－－－－－使用获取数组中某值的元素个数类用例－－－－－－－－－－－－－ */
        {
            int j = 0;
            int k = 0;
            int xnum = 0;
            int a[MAXSIZE][MAXSIZE] = { 1,  2,  3,  4,  5,
                                        6,  5,  8,  9, 10,
                                        11, 12, 13, 14, 15,
                                        16, 17, 18,  5, 20,
                                        0,  0,  0,  0,  0};

            struct strmatrix p = {0};
            p.rownum = 4;
            p.columnnum = 5;
            for(j = 0; j < MAXSIZE; j++)
            {
                for(k = 0; k < MAXSIZE; k++)
                {
                    p.matrix[j][k] = a[j][k];
                }
            }

            xnum = getxnum(&p, 5);

            std::cout << (xnum == 3) << std::endl;
        }
/* －－－－－－－－－－使用下标获取数组元素类用例－－－－－－－－－－－－－ */

/* －－－－－－－－－－矩阵中插入1行类用例－－－－－－－－－－－－－ */
        {
            int j = 0;
            int k = 0;
            int a[MAXSIZE][MAXSIZE] = { 1,  2,  3,  4,  0,
                                        5,  6,  7,  8,  0,
                                        9, 10, 11, 12,  0,
                                        13, 14, 15, 16,  0,
                                        0,  0,  0,  0,  0};

            struct strmatrix p = {0};
            p.rownum = 4;
            p.columnnum = 4;
            for(j = 0; j < MAXSIZE; j++)
            {
                for(k = 0; k < MAXSIZE; k++)
                {
                    p.matrix[j][k] = a[j][k];
                }
            }

            int x[4] = {17,18,19,20};

            insertrow(&p, 2, x);

            int b[MAXSIZE][MAXSIZE] =   { 1,  2,  3,  4,  0,
                                          5,  6,  7,  8,  0,
                                          17, 18, 19, 20,  0,
                                          9, 10, 11, 12,  0,
                                          13, 14, 15, 16,  0};

            std::cout << (p.rownum == 5) << std::endl;
            std::cout << (p.columnnum == 4) << std::endl;
            for(j = 0; j < MAXSIZE; j++)
            {
                for(k = 0; k < MAXSIZE; k++)
                {
                    std::cout << (p.matrix[j][k] == b[j][k]) << std::endl;
                }
            }
        }
/* －－－－－－－－－－矩阵中插入1行类用例－－－－－－－－－－－－－ */

/* －－－－－－－－－－矩阵中插入1列类用例－－－－－－－－－－－－－ */
        {
            int j = 0;
            int k = 0;
            int a[MAXSIZE][MAXSIZE] = { 1,  2,  3,  4,  0,
                                        5,  6,  7,  8,  0,
                                        9, 10, 11, 12,  0,
                                        13, 14, 15, 16,  0,
                                        0,  0,  0,  0,  0};

            struct strmatrix p = {0};
            p.rownum = 4;
            p.columnnum = 4;
            for(j = 0; j < MAXSIZE; j++)
            {
                for(k = 0; k < MAXSIZE; k++)
                {
                    p.matrix[j][k] = a[j][k];
                }
            }

            int x[4] = {17,18,19,20};

            insertcolumn(&p, 2, x);

            int b[MAXSIZE][MAXSIZE] =   { 1,  2, 17, 3,  4,
                                          5,  6, 18, 7,  8,
                                          9, 10, 19, 11, 12,
                                          13, 14, 20, 15, 16,
                                          0,  0,  0,  0,  0};

            std::cout << (p.rownum == 4) << std::endl;
            std::cout << (p.columnnum == 5) << std::endl;
            for(j = 0; j < MAXSIZE; j++)
            {
                for(k = 0; k < MAXSIZE; k++)
                {
                    std::cout << (p.matrix[j][k] == b[j][k]) << std::endl;
                }
            }
        }
/* －－－－－－－－－－矩阵中插入1列类用例－－－－－－－－－－－－－ */


/* －－－－－－－－－－方矩阵置换类用例－－－－－－－－－－－－－ */
        {
            int j = 0;
            int k = 0;
            int a[MAXSIZE][MAXSIZE] = { 1,  2,  3,  4,  0,
                                        5,  6,  7,  8,  0,
                                        9, 10, 11, 12,  0,
                                        13, 14, 15, 16,  0,
                                        0,  0,  0,  0,  0};

            struct strmatrix p = {0};
            p.rownum = 4;
            p.columnnum = 4;
            for(j = 0; j < MAXSIZE; j++)
            {
                for(k = 0; k < MAXSIZE; k++)
                {
                    p.matrix[j][k] = a[j][k];
                }
            }

            matrixtrans(&p);

            int b[MAXSIZE][MAXSIZE] =   { 1,  5,  9, 13,  0,
                                          2,  6, 10, 14,  0,
                                          3,  7, 11, 15,  0,
                                          4,  8, 12, 16,  0,
                                          0,  0,  0,  0,  0};

            std::cout << (p.rownum == 4) << std::endl;
            std::cout << (p.columnnum == 4) << std::endl;
            for(j = 0; j < MAXSIZE; j++)
            {
                for(k = 0; k < MAXSIZE; k++)
                {
                    std::cout << (p.matrix[j][k] == b[j][k]) << std::endl;
                }
            }
        }
/* －－－－－－－－－－方矩阵置换类用例－－－－－－－－－－－－－ */


/* －－－－－－－－－－方矩顺时针旋转90度用例－－－－－－－－－－－－－ */
        {
            int j = 0;
            int k = 0;
            int a[MAXSIZE][MAXSIZE] = { 1,  2,  3,  4,  0,
                                        5,  6,  7,  8,  0,
                                        9, 10, 11, 12,  0,
                                        13, 14, 15, 16,  0,
                                        0,  0,  0,  0,  0};

            struct strmatrix p = {0};
            p.rownum = 4;
            p.columnnum = 4;
            for(j = 0; j < MAXSIZE; j++)
            {
                for(k = 0; k < MAXSIZE; k++)
                {
                    p.matrix[j][k] = a[j][k];
                }
            }

            matrixwhirl(&p);

            int b[MAXSIZE][MAXSIZE] =   { 13,  9,  5,  1,  0,
                                          14, 10,  6,  2,  0,
                                          15, 11,  7,  3,  0,
                                          16, 12,  8,  4,  0,
                                          0,  0,  0,  0,  0};

            std::cout << (p.rownum == 4) << std::endl;
            std::cout << (p.columnnum == 4) << std::endl;
            for(j = 0; j < MAXSIZE; j++)
            {
                for(k = 0; k < MAXSIZE; k++)
                {
                    std::cout << (p.matrix[j][k] == b[j][k]) << std::endl;
                }
            }
        }
/* －－－－－－－－－－方矩顺时针旋转90度用例－－－－－－－－－－－－－ */


/* －－－－－－－－－－矩阵相加类用例－－－－－－－－－－－－－ */
        {
            int j = 0;
            int k = 0;
            struct strmatrix plu = {0};
            int a[MAXSIZE][MAXSIZE] = { 1,  2,  3,  0,  0,
                                        4,  5,  6,  0,  0,
                                        7,  8,  9,  0,  0,
                                        10, 11, 12,  0,  0,
                                        0,  0,  0,  0,  0};
            int b[MAXSIZE][MAXSIZE] = { 1,  2,  3,  0,  0,
                                        4,  5,  6,  0,  0,
                                        7,  8,  9,  0,  0,
                                        10, 11, 12,  0,  0,
                                        0,  0,  0,  0,  0};


            struct strmatrix p = {0};
            p.rownum = 4;
            p.columnnum = 3;

            struct strmatrix q = {0};
            q.rownum = 4;
            q.columnnum = 3;

            for(j = 0; j < MAXSIZE; j++)
            {
                for(k = 0; k < MAXSIZE; k++)
                {
                    p.matrix[j][k] = a[j][k];
                    q.matrix[j][k] = b[j][k];
                }
            }

            matrixplus(&plu, &p, &q);

            int c[MAXSIZE][MAXSIZE] =   {  2,  4,  6,  0,  0,
                                           8, 10, 12,  0,  0,
                                           14, 16, 18,  0,  0,
                                           20, 22, 24,  0,  0,
                                           0,  0,  0,  0,  0};

            std::cout << (plu.rownum == 4) << std::endl;
            std::cout << (plu.columnnum == 3) << std::endl;
            for(j = 0; j < MAXSIZE; j++)
            {
                for(k = 0; k < MAXSIZE; k++)
                {
                    std::cout << (plu.matrix[j][k] == c[j][k]) << std::endl;
                }
            }
        }
/* －－－－－－－－－－矩阵相加类用例－－－－－－－－－－－－－ */


/* －－－－－－－－－－矩阵相乘类用例－－－－－－－－－－－－－ */
        {
            int j = 0;
            int k = 0;
            struct strmatrix mul = {0};
            int a[MAXSIZE][MAXSIZE] = { 1,  2,  3,  0,  0,
                                        4,  5,  6,  0,  0,
                                        7,  8,  9,  0,  0,
                                        10, 11, 12,  0,  0,
                                        0,  0,  0,  0,  0};
            int b[MAXSIZE][MAXSIZE] = { 1,  2,  3,  4,  0,
                                        5,  6,  7,  8,  0,
                                        9, 10, 11, 12,  0,
                                        0,  0,  0,  0,  0,
                                        0,  0,  0,  0,  0};

            struct strmatrix p = {0};
            p.rownum = 4;
            p.columnnum = 3;

            struct strmatrix q = {0};
            q.rownum = 3;
            q.columnnum = 4;

            for(j = 0; j < MAXSIZE; j++)
            {
                for(k = 0; k < MAXSIZE; k++)
                {
                    p.matrix[j][k] = a[j][k];
                    q.matrix[j][k] = b[j][k];
                }
            }

            matrixmultiply(&mul, &p, &q);

            int c[MAXSIZE][MAXSIZE] =   {  38,  44,  50,  56,  0,
                                           83,  98, 113, 128,  0,
                                           128, 152, 176, 200,  0,
                                           173, 206, 239, 272,  0,
                                           0,   0,   0,   0,  0};

            std::cout << (mul.rownum == 4) << std::endl;
            std::cout << (mul.columnnum == 4) << std::endl;
            for(j = 0; j < MAXSIZE; j++)
            {
                for(k = 0; k < MAXSIZE; k++)
                {
                    std::cout << (mul.matrix[j][k] == c[j][k]) << std::endl;
                }
            }
        }
/* －－－－－－－－－－矩阵相乘类用例－－－－－－－－－－－－－ */

};
