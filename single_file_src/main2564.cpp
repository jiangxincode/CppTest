/**
 * 假设一整型数组中的元素按从小到大的顺序排列，编写C语言函数，删除其中的重复元素。
 * 比如，若一维数组中的数据是：2 2 2 3 4 4 5 6 6 6 6 7 7 8 9 9 10 10 10，
 * 函数执行后，该一维数组中的数据是：2 3 4 5 6 7 8 9 10。
 */
#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main() {
    vector<int> in{2, 2, 2, 3, 4, 4, 5, 6, 6, 6, 6, 7, 7, 8, 9, 9, 10, 10, 10};
    vector<int> out;
    set<int> my_set;

    for (int i : in) {
        my_set.insert(i);
    }

    for (int i : my_set) {
        out.push_back(i);
    }

    for (int i : out) {
        cout << i << " ";
    }

    return 0;
}
