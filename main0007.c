/*
������2014����Ƹ������
�ٶ�2014����з�������
6.
һ��m*n�ľ��󣬴����Ҵ��ϵ��¶��ǵ����ģ���һ����elem�����Ƿ��ھ����У�
����˼·�ʹ��루���Ͼ���
*/

#include <stdio.h>
#include <stdlib.h>

/**
 * ����������
 *
 * T = O(n + n)
 *
 */
void findKey(int **matrix, int n, int m, int key)
{
    int row, col;

    for(row = 0, col = m - 1; row < n && col >= 0;)
    {
        if(matrix[row][col] == key)
        {
            printf("��%d�У���%d��\n", row + 1, col + 1);
            break;
        }
        else if(matrix[row][col] > key)
        {
            col -= 1;
        }
        else
        {
            row += 1;
        }
    }

    printf("������!\n");
}

int main0007()
{
    int i, j, key, n, m, **matrix;
    // �������
    scanf("%d %d", &n, &m);
    matrix = (int **)malloc(sizeof(int *) * n);

    for(i = 0; i < n; i ++)
        matrix[i] = (int *)malloc(sizeof(int) * m);

    for(i = 0; i < n; i ++)
    {
        for(j = 0; j < m; j ++)
            scanf("%d", &matrix[i][j]);
    }

    // ��ѯ����
    while(scanf("%d", &key) != EOF)
    {
        findKey(matrix, n, m, key);
    }

    return 0;
}
