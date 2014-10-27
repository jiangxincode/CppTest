/**
C������μ��������

�ʣ�
C��32λ��int���͵����Χ��-2147483648��2147483647,
��Ҫ����-5000000 * 1374389539�����,����Ȼ��������ᵼ�������
����μ���������������

��
C �е��û������֮�����������Ѿ�̫�������ú������֮���������һ��Ҳ���٣�
���������ͨ���Ժ��������ļ�⣬ʵ�ֶԻ������������ļ�⡣
��Ϊ a * b ���� a �� b �ĺͣ�-5000000 * 1374389539 ���� -(5000000 * 1374389539)��
�������� 5000000 �� 1374389539 �ĺ͡�
�Ұ��ܼ������ĺ�������� add()�Ȼ���� multiply()���ظ����� add()��
add() ��ô��������
������Ľ���������������ֵ�Ļ��ơ����絼�����»��ƣ����絼�����ϻ��ơ��߽�״����
��1������΢�������� INT_MAX + 1 ������� INT_MIN��
��2�������ص������� INT_MAX + INT_MAX ������� -2��
��3������΢�������� INT_MIN - 1 ������� INT_MAX��
��4�������ص������� INT_MIN - INT_MIN ������� 0��
���ۣ�
��1��������������С���κ�һ����������
��2�������������������κ�һ����������
����add()�����ý��������ѡ����һ�������ж������������ѡ�Ĳ����ж�����ķ���
add()�޷��Է���ֵ�ٱ���������Բ��� strtol()�ľٱ���������ͬ�� strtol()���ǣ�
��û�������add() ��� 0 ��ֵ�� errno��multiply() ���ⷽ��� add() һ����
��Ȼ��Ӧ���������ѷ������Ƿ���������˽����ݵķ�Χ��ѡ��ǡ���ı������͡�
*/

#include<stdio.h>
#include<errno.h>   /* errno, ERANGE */
/**
 * Returns the sum of a and b, with overflow and underflow check.
 * If overflow or underflow occurred, sets errno to ERANGE, else to 0.
 */
int add(int a, int b)
{
    int result = a + b;

    if((b > 0 && result > a) || (b <= 0 && result <= a))
    {
        errno = 0;
    }
    else
    {
        errno = ERANGE;
    }

    return result;
}


/**
 * Returns the product of a and b obtained through repeated call of add( ).
 * Affects errno exactly as add() does.
 */
int multiply(int a, int b)
{

    int sign_of_a = 1, result = 0, i = 0;

    /* Keep the sign of multiplier off the loop sentinel. */
    if(a < 0)
    {
        sign_of_a = -1;
        a *= -1;
    }

    /* Have to reset errno here because it won't be updated if a is 0. */
    errno = 0;

    while(i++ < a)
    {
        result = add(result, b);
        if(errno == ERANGE)
            break;
    }
    return result * sign_of_a;
}
int main0555()
{
    int result; /* Operands too huge: sure overflow. */
    result = multiply(-5000000, 1374389539);

    if(errno == ERANGE)
    {
        perror("Uh oh");
    }
    else
    {
        printf("%d\n", result); /* Small operands: safe. */
    }
    result = multiply(49, -972);
    if(errno == ERANGE)
    {
        perror("Uh oh");
    }
    else
    {
        printf("%d\n", result);
    }
    return 0;
}
