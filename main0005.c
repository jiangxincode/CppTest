/**
 * ����һ��������','�ָ��������������ȥ�����ֵ����Сֵ֮��ʣ�µĸ�����
 * �������ֵ����Сֵ�����ж��
 * Smple input��3,3,5,3,6,9,7,9   Sample outPut: 3
 */

#include <stdio.h>
#include <limits.h>

#define N 100

int main0005()
{
    int min = INT_MAX, max = INT_MIN;
    int n = 0; //��¼��������ָ���
    int ch = '\0';
    int array[N] = {0};

    while(ch != '\n')
    {
        int temp;
        scanf("%20d", &temp);
        array[n++] = temp;

        if(temp < min)
        {
            min = temp;
        }

        if(temp > max)
        {
            max = temp;
        }

        ch = getchar();
    }

    int result = 0;

    for(int i=0; i<n; i++)
    {
        if(array[i]!=min && array[i]!=max)
        {
            result ++;
        }
    }
    printf("%d",result);
    return 0;
}
