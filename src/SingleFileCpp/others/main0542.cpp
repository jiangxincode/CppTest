/**
 * 2015 阿里巴巴 数据研发工程师 在线笔试
 * Longest Common String 最长公共子串
 * 给定一个query和一个text
 * 要求在text中找出以同样的顺序连续出现在query中的最长连续序列的长度。
 * 例如， query为“acbac”，text为“acaccbabb”，
 * 那么text中的“cba”为最长的连续出现在query中的字母序列，
 * 因此，返回结果应该为其长度3
 */

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int LCS1(const string &text, const string &query) {
    string::size_type len = 0;

    for (string::size_type i = 0; i < query.length(); i++) {
        for (string::size_type j = query.length() - 1; j > i; j--) {
            string temp = query.substr(i, j - i + 1);

            if (text.find(temp) != string::npos) {
                if ((j - i) > len) {
                    len = j - i + 1; //i和j位置之中共有(j-i+1)个元素
                }
            }
        }
    }

    return len;
}


/**
 * 算法的基本思想：利用矩阵对角原理来实现
 * 当字符匹配的时候，不是简单的给相应元素赋上1，而是其左上角元素的值加1
 * 用两个标记变量来标记矩阵中值最大的元素的位置，在矩阵生成的过程中来判断
 * 当前生成的元素的值是不是最大的，据此来改变标记变量的值，那么到矩阵完成的时
 * 候，最长匹配子串的位置和长度就已经出来了。

 * 输入
 * 字符串1：21232523311324
 * 字符串2：312123223445
 * 数组c的变化情况为：
 * 0 0 1 0 1 0 1 1 0 0 0 0
 * 0 1 0 2 0 0 0 0 0 0 0 0
 * 0 0 2 0 3 0 1 1 0 0 0 0
 * 1 0 0 0 0 4 0 0 2 0 0 0
 * 0 0 1 0 1 0 5 1 0 0 0 0
 * 0 0 0 0 0 0 0 0 0 0 0 1
 * 0 0 1 0 1 0 1 1 0 0 0 0
 * 1 0 0 0 0 2 0 0 2 0 0 0
 * 1 0 0 0 0 1 0 0 1 0 0 0
 * 0 2 0 1 0 0 0 0 0 0 0 0
 * 0 1 0 1 0 0 0 0 0 0 0 0
 * 1 0 0 0 0 1 0 0 1 0 0 0
 * 0 0 1 0 1 0 2 1 0 0 0 0
 * 0 0 0 0 0 0 0 0 0 1 1 0
 * 长：14（串1的长度），宽：12（串2的长度）
 * 最长子串为:21232
 */

int LCS2(const char left[], const char right[], int &pos) {
    int *arr = new int[strlen(right)];
    int len = 0;

    for (size_t i = 0; i < strlen(left); i++) {
        for (int j = strlen(right) - 1; j >= 0; j--) //此处不能使用size_t
        {
            if (left[i] == right[j]) {
                if (i == 0 || j == 0)
                    arr[j] = 1;
                else {
                    arr[j] = arr[j - 1] + 1;
                }
            } else
                arr[j] = 0;

            if (arr[j] > len) {
                len = arr[j];
                pos = j;
            }
        }
    }
    delete[] arr;
    pos = pos - len + 1;
    return len;
}


void GetMaxCommStr(char *s1, char *s2, char *s3)//s1、s2 为要对比的俩个字符串，
{
    //s3用来存储最大的公共字符串
    char len1 = strlen(s1);
    char len2 = strlen(s2);
    char maxlen = 0;

    for (int i = 0; i < len1; i++) {
        for (int j = 0; j < len2; j++) {
            if (s1[i] == s2[j])     //找到了第一个相等的
            {
                int as = i, bs = j, count = 1; //保存第一个相等的首地址

                while ((as + 1 < len1) && (bs + 1 < len2) && (s1[++as] == s2[++bs]))     //查找最大相等长度
                    count++;

                if (count > maxlen)  //如果大于最大长度则更新
                {
                    maxlen = count;
                }
            }
        }
    }

    if (maxlen > 0)  //有公共子字符串
    {
        for (int i = 0; i < maxlen; i++) {
            *(s3 + i) = *(s1 + i);
        }

        cout << "maxlen is " << maxlen << endl;
        cout << "len1 is " << len1 << endl;
        cout << "len2 is " << len2 << endl;
    }
}

int main05423() {
    char strd[80] = {0};
    char stra[80] = "iojhklgklskljklngvnkldg";
    char strb[80] = "kldfjjsfgjlkjgldakfga;";
    GetMaxCommStr(stra, strb, strd);
    cout << "stra is: " << stra << endl;
    cout << "strb is: " << strb << endl;
    cout << "strd is: " << strd << endl;
    return 0;
}

int main() {
    cout << LCS1("hello", "llohghdfja") << endl;
    int pos;
    cout << LCS2("hello", "llohghdfja", pos) << endl;
    cout << pos << endl;
    return 0;
}
