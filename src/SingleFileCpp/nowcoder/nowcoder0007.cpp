/**
 * 明明的随机数
 * https://www.nowcoder.com/practice/3245215fffb84b7b81285493eae92ff0
 * 问题描述：明明想在学校中请一些同学一起做一项问卷调查，为了实验的客观性，他先用计算机生成了N个1到1000之间的随机整数（N≤100），对于其中重复的数字，只保留一个，把其余相同的数去掉，不同的数对应着不同的学生的学号。
 * 然后再把这些数从小到大排序，按照排好的顺序去找同学做调查。请你协助明明完成“去重”与“排序”的工作。
 * Input Param
 * n               输入随机数的个数
 * inputArray      n个随机整数组成的数组
 * Return Value
 * OutputArray    输出处理后的随机整数
 * 注：测试用例保证输入参数的正确性，答题者无需验证。
 * 输入:
 * 输入多行，先输入随机整数的个数，在输入相应个数的整数
 * 输出:
 * 返回多行，处理后的结果
 * 样例输入:
 * 11
 * 10
 * 20
 * 40
 * 32
 * 67
 * 40
 * 20
 * 89
 * 300
 * 400
 * 15
 * 样例输出:
 * 10
 * 15
 * 20
 * 32
 * 40
 * 67
 * 89
 * 300
 * 400
 * 问题分析：数组输入后，重复数的删除，以及新数组的冒泡排序问题。
 */
#include <iostream>

using namespace std;

bool exit(int *a, int b, int n) {
    for (int i = 0; i < n; i++) {
        if (b == a[i])
            return true;
    }
    return false;
}

void sort(int a[], int length) {
    for (int i = 0; i < length; i++)
        for (int j = i; j < length; j++) {
            if (a[i] > a[j]) {
                int temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }

        }
}

int main() {

    int inputCount; //随机数的个数
    while (cin >> inputCount) {
        int input[1024] = {0};
        int output[1024] = {0};

        for (int i = 0; i < inputCount; i++) {
            cin >> input[i];
        }

        output[0] = input[0];
        int outputCount = 1;

        for (int i = 1; i < inputCount; i++) {
            if (!exit(output, input[i], outputCount)) {
                output[outputCount++] = input[i];
            }

        }

        sort(output, outputCount);

        for (int i = 0; i < outputCount; i++)
            cout << output[i] << endl;
    }
    return 0;
}


