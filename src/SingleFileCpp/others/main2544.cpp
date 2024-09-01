/**
 * Hermit多项式
 * 分别写出计算Hermit多项式Hn(x)值的迭代和递归函数。Hn(x)定义如下：
 * H0(x) = 1
 * H1(x) = 2x
 * Hn(x) = 2x Hn-1(x)-2(n-1) Hn-2(x)    (n>1)
*/
#include <iostream>

using namespace std;

int hermit2(int n, int x) {
    if (n == 0) {
        return 1;
    } else if (n == 1) {
        return 2 * x;
    } else {
        return 2 * x * hermit2(n - 1, x) - 2 * (n - 1) * hermit2(n - 2, x);
    }
}

int hermit1(int n, int x) {
    if (n == 0) {
        return 1;
    } else if (n == 1) {
        return 2 * x;
    } else {
        int result = 0;
        int h0 = 1, h1 = 2 * x;

        for (int i = 2; i <= n; i++) {
            result = 2 * x * h1 - 2 * (i - 1) * h0;
            h0 = h1;
            h1 = result;
        }

        return result;
    }
}

int main() {
    int x = 1;
    int n = 10;

    for (int i = 0; i <= n; i++) {
        cout << "Method1: The result is: " << hermit1(i, x) << " when n=" << i << " and x=" << x << endl;
        cout << "Method2: The result is: " << hermit2(i, x) << " when n=" << i << " and x=" << x << endl;
    }

    return 0;
}
