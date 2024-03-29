﻿/*
 * 1430 素数判定
 * 时间限制: 1 s
 * 空间限制: 1000 KB
 * 题目等级 : 青铜 Bronze
 * 题目描述 Description
 * 质数又称素数。指在一个大于1的自然数中，除了1和此整数自身外，不能被其他自然数整除的数。
 * 素数在数论中有着很重要的地位。比1大但不是素数的数称为合数。1和0既非素数也非合数。质数是与合数相对立的两个概念，二者构成了数论当中最基础的定义之一。基于质数定义的基础之上而建立的问题有很多世界级的难题，如哥德巴赫猜想等。算术基本定理证明每个大于1的正整数都可以写成素数的乘积，并且这种乘积的形式是唯一的。这个定理的重要一点是，将1排斥在素数集合以外。如果1被认为是素数，那么这些严格的阐述就不得不加上一些限制条件。
 * 概念
 * 只有1和它本身两个约数的自然数，叫质数(Prime Number)。（如：由2÷1=2，2÷2=1，可知2的约数只有1和它本身2这两个约数，所以2就是质数。与之相对立的是合数：“除了1和它本身两个约数外，还有其它约数的数，叫合数。”如：4÷1=4，4÷2=2，4÷4=1，很显然，4的约数除了1和它本身4这两个约数以外，还有约数2，所以4是合数。）
 * 100以内的质数有2，3，5，7，11，13，17，19，23，29，31，37，41，43，47，53，59，61，67，71，73，79，83，89，97，在100内共有25个质数。
 * 注：（1）1既不是质数也不是合数。因为它的约数有且只有1这一个约数。
 * （2）2和3是所有素数中唯一两个连着的数 ．
 * 输入描述 Input Description
 * 第一行输入一个正整数n，n<=30000
 * 输出描述 Output Description
 * 如果该数是质数，则输出\t
 * 否则输出\n
 * 样例输入 Sample Input
 * 输入样例１
 * 13
 * 输入样例２
 * 8
 * 样例输出 Sample Output
 * 样例输出１
 * \t
 * 样例输出２
 * \n
 * 数据范围及提示 Data Size & Hint
 * c或c++的初学者注意，"＼"的意思
 */
#include <iostream>

using namespace std;

int main()
{
    int input;
    cin >> input;
    int i;

    for(i=2; i*i<=input; i++)
    {
        if(input%i==0)
        {
            break;
        }
    }

    if((i*i>input) && (input>2))
    {
        cout << "\\t";
        return 0;
    }

    cout << "\\n";
    return 0;
}
