/**
 * 成绩排序
 * https://www.nowcoder.com/practice/8e400fd9905747e4acc2aeed7240978b
 * 输入任意（用户，成绩）序列，可以获得成绩从高到低或从低到高的排列,相同成绩都按先录入排列在前的规则处理。
 * 例示：
 * jack      70
 * peter     96
 * Tom       70
 * smith     67
 * 从高到低  成绩
 * peter     96
 * jack      70
 * Tom       70
 * smith     67
 * 从低到高
 * smith     67
 * Tom       70
 * jack      70
 * peter     96
 * -----------------------------------------
 * 输入多行，先输入要排序的人的个数，然后分别输入他们的名字和成绩，以一个空格隔开
 * 用户名字，字符串,非空串,长度不超过20;
 * 成绩，整数，范围【0，100】
 * 输入排序方式，0或1，0表示成绩从高到低方式输出名字和成绩，1表示成绩从低到高方式输出名字和成绩
 * -----------------------------------------
 * 样例输入：
 * 3
 * 0
 * fang 90
 * yang 50
 * ning 70
 * 样例输出：
 * fang 90
 * ning 70
 * yang 50
 */

#include <iostream>
#include <algorithm>

using namespace std;

struct student {
    char name[1000];
    int score;
};

bool compare1(student A, student B) {
    return A.score > B.score;
}

bool compare2(student A, student B) {
    return A.score < B.score;
}

int main() {
    int n;
    while (cin >> n) {
        int rank_way;
        cin >> rank_way;
        student arr[1000];
        for (int i = 0; i < n; i++) {
            cin >> arr[i].name >> arr[i].score;
        }

        if (rank_way == 0) {
            stable_sort(arr, arr + n, compare1);
        } else {
            stable_sort(arr, arr + n, compare2);
        }
        for (int i = 0; i < n; i++) {
            cout << arr[i].name << " " << arr[i].score << endl;
        }

    }
    return 0;
}


