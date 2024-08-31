/**
 * Fibonacci数列的计算和转换
 *
 * 介绍：
 * 一、Fibonacci数列：
 * 1,1,2,3,5,8,13,15,28，…
 * 它们有这样的规律：第1和第2的数字都是1，第3个数字是前2个数字之和，第4个数字是第2，第3个数字之和。
 * 即Fn = F(n-1) + F(n-2).
 * 二、扩展Fibonacci数列：
 * 扩展Fibonacci数列，前2个数字可以任意输入，例如前2个数字为
 * -1,1，那么后续的数字就是：0,1,1,2,3,5,8，…
 * 题目要求：
 * 一、请实现如下函数功能：输入扩展Fibanacci数列的前2个数字和要求的数字序号，返回这个序号对应的扩展Fibanbacci数值。
 * 例如，扩展Fibanacci的前2个数字为-1和1。
 * 输入3，则返回0。
 * 输入6，则返回2。
 * 输入10，则返回13。
 * 题目要求可以输入30以内的数字，都能返回结果。请实现函数
 * int GetExtFibonacci(int first , int second, int num)
 * 二、计算前n个序列之和。
 * 例如，扩展Fibonacci数列的前2个数字是-1和1，则该数列为：
 * -1,1,0,1,1,2,3,5,8,13…
 * 则前2个数字之和是：-1 + 1 = 0。
 * 则前3个数字之和是：-1 + 1 + 0 = 0。
 * 则前5个数字之和是：-1 + 1 + 0 + 1= 1。
 * 请实现函数：
 * int CalcTotalValueOfExtFibonacci(int first , int second, int num)
 */

#include <iostream>

using namespace std;

int GetExtFibonacci(int first, int second, int num) {
    if (num == 1) {
        return first;
    } else if (num == 2) {
        return second;
    }

    int count = 2;

    while (count < num) {
        int temp = first + second;
        first = second;
        second = temp;
        count++;
    }

    return second;
}

/**
 * CalcTotalValueOfExtFibonacci
 * 输入扩展Fibonacci数列的前2个数字first和second，和数字的序列号num
 * 输出：扩展Fibonacci数列对应的序号的数列之前（包括这个数列本身）的所有的数列之和
 */
int CalcTotalValueOfExtFibonacci(int first, int second, int num) {
    int count = 1;
    int result = 0;
    while (count <= num) {
        result += GetExtFibonacci(first, second, count);
        count++;
    }
    return result;
}

int main(int argc, char *argv[]) {
    cout << (-1 == GetExtFibonacci(-1,1,1)) << endl;
    cout << (1 == GetExtFibonacci(-1,1,2)) << endl;
    cout << (0 == GetExtFibonacci(-1,1,3)) << endl;
    cout << (1 == GetExtFibonacci(-1,1,4)) << endl;
    cout << (1 == GetExtFibonacci(-1,1,5)) << endl;
    cout << (2 == GetExtFibonacci(-1,1,6)) << endl;
    cout << (3 == GetExtFibonacci(-1,1,7)) << endl;
    cout << (5 == GetExtFibonacci(-1,1,8)) << endl;
    cout << (8 == GetExtFibonacci(-1,1,9)) << endl;
    cout << (13 == GetExtFibonacci(-1,1,10)) << endl;

    cout << (-1 == CalcTotalValueOfExtFibonacci(-1,1,1)) << endl;
    cout << (0 == CalcTotalValueOfExtFibonacci(-1,1,2)) << endl;
    cout << (0 == CalcTotalValueOfExtFibonacci(-1,1,3)) << endl;
    cout << (1 == CalcTotalValueOfExtFibonacci(-1,1,4)) << endl;
    cout << (2 == CalcTotalValueOfExtFibonacci(-1,1,5)) << endl;
    cout << (4 == CalcTotalValueOfExtFibonacci(-1,1,6)) << endl;
    cout << (7 == CalcTotalValueOfExtFibonacci(-1,1,7)) << endl;
    cout << (12 == CalcTotalValueOfExtFibonacci(-1,1,8)) << endl;
    cout << (20 == CalcTotalValueOfExtFibonacci(-1,1,9)) << endl;
    cout << (33 == CalcTotalValueOfExtFibonacci(-1,1,10)) << endl;

    return 0;
}

