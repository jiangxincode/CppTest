/**
 * 菲波那契数列
 * https://www.nowcoder.com/practice/c245af6cfdce49ceb5435f649ee14f89
 * https://www.nowcoder.com/practice/c6c7742f5ba7442aada113136ddea0c3
 * 题目描述
 * 菲波那契数列是指这样的数列：数列的第一个和第二个数都为1，接下来每个数都等于前面2个数之和。给出一个正整数K，要求菲波那契数列中第k个数是多少。
 * 输入描述:
 * 输入一行，包含一个正整数k。(0<k<47)
 * 输出描述:
 * 输出一行，包含一个正整数，表示菲波那契数列中第k个数的大小
 * 示例1
 * 输入
 * 复制
 * 19
 * 输出
 * 复制
 * 4181
 */

#include <iostream>
#include <cerrno>
#include <cstring>

using namespace std;

/** \brief 斐波拉契/斐波那契/Fibonacci/Fib
 * f(1)=1
 * f(2)=1
 * f(n)=f(n-1)+f(n-2) n>2
 * \param 非负整数n
 * \return 正常情况下返回实际结果，出错返回-1
 * 输入小于0:EDOM
 * 输入过大，导致结果溢出:ERANGE
 */

int fibonacci(int n) {
    errno = 0; //清除errno
    int result;
    int smaller = 0, bigger = 1;

    if (n < 0) //错误输入
    {
        errno = EDOM;
        return -1;
    } else if (n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else {
        for (int i = 2; i <= n; i++) {
            result = smaller + bigger;

            /**
             * 说明在上次result = smaller+bigger发生了上溢，
             * result一定比smaller和bigger都小
             */
            if (result < smaller) {
                errno = ERANGE;
                return -1;
            }

            smaller = bigger;
            bigger = result;
        }
    }

    return result;
}

/**
 * 递归算法
 */
int fibonacci_2(int n) {
    if (n < 0) {
        return -1;
    } else if (n == 0) {
        return 0;
    } else if (n == 1 || n == 2) {
        return 1;
    } else {
        return fibonacci_2(n - 1) + fibonacci_2(n - 2);
    }
}

int main() {
    int input;

    while (cin >> input) {
        cout << fibonacci(input) << endl;
    }

    return 0;
}
