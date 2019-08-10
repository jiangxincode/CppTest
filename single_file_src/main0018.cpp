/**
C语言如何检测溢出情况

问：
C中32位机int类型的最大范围是-2147483648到2147483647,
我要处理-5000000 * 1374389539的情况,很显然这种情况会导致溢出，
我如何检测出这种溢出情况？

答：
C 中调用积运算符之后做溢出检测已经太晚，但调用和运算符之后做检测则一点也不迟，
所以你可以通过对和运算结果的检测，实现对积运算溢出结果的检测。
因为 a * b 即是 a 个 b 的和：-5000000 * 1374389539 等于 -(5000000 * 1374389539)。
括号里是 5000000 个 1374389539 的和。
我把能检测溢出的和运算包在 add()里，然后在 multiply()里重复调用 add()。
add() 怎么检测溢出？
和运算的结果若溢出将导致数值的环绕。上溢导致往下环绕，下溢导致往上环绕。边界状况：
（1）最轻微的上溢是 INT_MAX + 1 ：结果是 INT_MIN。
（2）最严重的上溢是 INT_MAX + INT_MAX ：结果是 -2。
（3）最轻微的下溢是 INT_MIN - 1 ：结果是 INT_MAX。
（4）最严重的下溢是 INT_MIN - INT_MIN ：结果是 0。
结论：
（1）所有上溢结果都小于任何一个操作数。
（2）所有下溢结果都大于任何一个操作数。
所以add()可以用结果和任意选定的一个参数判断溢出，并以落选的参数判断溢出的方向。
add()无法以返回值举报溢出，所以采用 strtol()的举报方法。不同于 strtol()的是，
若没有溢出，add() 会把 0 赋值给 errno。multiply() 在这方面跟 add() 一样。
当然，应付溢出的最佳方法还是防范：充分了解数据的范围，选择恰当的变量类型。
*/

#include <stdio.h>
#include <errno.h>   /* errno, ERANGE */
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
        {
            break;
        }
    }

    return result * sign_of_a;
}

/** \cond */
int main()
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
/** \endcond */
