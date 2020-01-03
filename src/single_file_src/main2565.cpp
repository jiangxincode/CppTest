/**
 * 不引入新的数组，实现数组元素交换位置函数：
 * void swap(int a[], int m, int n);
 * 要求将数组中的前m个元素和后n个元素交换位置。
 * 比如，设m为3，n为4，a中的数据为：1 2 3 4 5 6 7，函数执行后，a中的数据为：4 5 6 7 1 2 3。
 *
 * 这道题出的有些问题，没有说数组总长度total_length和(m+n)的大小关系。我们暂认为total_length >= (m+n)
 */
#include <iostream>

using namespace std;

/**
 * Print data in array, separated with space
 * @param a The array printed
 * @param length The length of the array
 */
void print_array(int a[], int length) {
    for (int i = 0; i < length; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}

/**
 * Move some data to the right
 * If the array is: [0,1,2,3,4,5], and num is 2, the result is: [2,3,4,5,0,1]
 *
 * @param p The pointer of array operated
 * @param length The length of the array
 * @param num Specify how many data in the array will be moved
 */
void move2right(int *p, int length, int num) {
    for (int i = 0; i < num; i++) {
        int tmp = p[0];
        for (int j = 1; j < length; j++) {
            p[j - 1] = p[j];
        }
        p[length - 1] = tmp;
    }
}

/**
 * Move some data to the left
 * If the array is: [0,1,2,3,4,5], and num is 2, the result is: [4,5,0,1,2,3]
 *
 * @param p The pointer of array operated
 * @param length The length of the array
 * @param num Specify how many data in the array will be moved
 */
void move2left(int *p, int length, int num) {
    for (int i = 0; i < num; i++) {
        int tmp = p[length - 1];
        for (int j = length - 1; j > 0; j--) {
            p[j] = p[j - 1];
        }
        p[0] = tmp;
    }
}

void swap(int *p, int length, int m, int n) {
    if (m >= n) {
        move2right(p, length, m);
        move2right(p, length - m, length - m - n);
    } else {
        move2left(p, length, n);
        move2left(p + n, length - n, length - m - n);
    }
}

int main() {
    int length = 10;
    int *p = new int[length]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int m = 5;
    int n = 3;
    print_array(p, length);
    swap(p, length, m, n);
    print_array(p, length);

    length = 10;
    p = new int[length]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    m = 3;
    n = 5;
    print_array(p, length);
    swap(p, length, m, n);
    print_array(p, length);

    length = 7;
    p = new int[length]{1, 2, 3, 4, 5, 6, 7};
    m = 3;
    n = 4;
    print_array(p, length);
    swap(p, length, m, n);
    print_array(p, length);

    length = 7;
    p = new int[length]{1, 2, 3, 4, 5, 6, 7};
    m = 4;
    n = 3;
    print_array(p, length);
    swap(p, length, m, n);
    print_array(p, length);

    return 0;
}
