/**
 * 查找兄弟单词(4426/4429)
 * 题目描述
 * 实现一个可存储若干个单词的字典。用户可以：
 * - 在字典中加入单词。
 * - 查找指定单词在字典中的兄弟单词个数。
 * - 查找指定单词的指定序号的兄弟单词，指定序号指字典中兄弟单词按字典顺序排序后的序号（从1开始）
 * - 清空字典中所有单词。
 * 定义，格式说明
 * 单词
 * 由小写英文字母组成，不含其它字符。
 * 兄弟单词
 * 给定一个单词X，如果通过任意交换单词中字母的位置得到不同的单词Y，那么定义Y是X的兄弟单词。
 * 字典顺序
 * 两个单词(字母按照自左向右顺序)，先以第一个字母作为排序的基准，如果第一个字母相同，就用第二个字母为基准，如果第二个字母相同就以第三个字母为基准。依此类推，如果到某个字母不相同，字母顺序在前的那个单词顺序在前。如果短单词是长单词从首字母开始连续的一部分，短单词顺序在前。
 * 举例：bca是abc的兄弟单词；abc与abc是相同单词，不是兄弟单词
 * 规格
 * - 0<=字典中所含单词个数<=1000
 * - 1<=单词所含字母数<=50
 * 测试用例保证，接口中输入不会超出如上约束。
 * 待实现接口
 * 原型：int AddOneWord (char* Word);
 * 功能：在字典中增加一个单词
 * 输入参数：
 * Word 单词字符串，调用者保证Word指针不为空，指向的是合法单词
 * 输出参数：
 * 无
 * 返回值：
 * -1 失败（单词在字典中已存在等情况）
 * 0  成功
 * 说明： Word字符串可能在函数外被释放，请自行分配字符串中单词的存储空间。
 * 原型： int FindSimilarWordNum (char* Word);
 * 功能：查找指定单词在字典中的兄弟单词个数
 * 输入参数：
 * Word 指定单词字符串，调用者保证Word指针不为空，指向的是合法单词
 * 输出参数：
 * 无
 * 返回值：
 * 返回指定单词在字典中的兄弟单词总个数。如果不存在兄弟单词，返回0
 * 原型：int FindOneSimilarWord (char* Word, int Seq, char* SimilarWord);
 * 功能：查找指定单词的指定序号的兄弟单词，指定序号指字典中兄弟单词按字典顺序（参见Page 3）排序后的序号（从1开始）
 * 输入参数：
 * Word 指定单词字符串，调用者保证Word指针不为空，指向的是合法单词
 * Seq 指定序号（大于等于1）
 * 输出参数：
 * SimilarWord 返回兄弟单词字符串，指针不为空，指向的内存由调用者预先分配，占51个字节长度，输出的兄弟单词必须紧跟’\0’结束。如果不存在指定序号的兄弟单词，输出空串。
 * 返回值：
 * -1 失败（如果不存在指定序号的兄弟单词，返回失败）
 * 0  成功
 * 原型：void ClearAllWords(void);
 * 功能：清空字典中所有单词
 * 输入参数：
 * 无
 * 输出参数：
 * 无
 * 返回值：
 * 无
 */
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;


#define MAX_DICT_WORD_NUM 1000 //0<=字典中所含单词个数<=1000
#define MAX_WORD_LENGTH 50 //1<=单词所含字母数<=50

struct BWord {
    char value[MAX_WORD_LENGTH + 1];
    struct BWord *pnext;
};

struct BDict {
    char key[MAX_WORD_LENGTH + 1];
    struct BWord *next;
} head[MAX_DICT_WORD_NUM];

int size = 0;

/******************************************************************************
原    型：int AddOneWord (char* Word);
功    能：在字典中增加一个单词
输入参数：
          Word 单词字符串，调用者保证Word指针不为空，指向的是合法单词
输出参数：
          无
返回值：
        -1 失败（单词在字典中已存在等情况）
        0  成功

********************************************************************************/
int AddOneWord(char *Word) {
    int i;
    char tWord[MAX_WORD_LENGTH + 1];

    if (!Word) {
        return -1;
    }
    if ((strlen(Word) < 1) || (strlen(Word) > MAX_WORD_LENGTH)) {
        return -1;
    }

    strcpy(tWord, Word);
    sort(tWord, tWord + strlen(tWord));

    for (i = 0; i < size; i++) {
        if (strcmp(tWord, head[i].key) != 0) {
            continue;
        }

        struct BWord *p = head[i].next, *q = NULL;
        while (p != NULL) {
            if (strcmp(p->value, Word) > 0) {
                struct BWord *t = (struct BWord *) malloc(sizeof(struct BWord));
                strcpy(t->value, Word);
                t->pnext = NULL;

                if (q == NULL) {
                    head[i].next = t;
                } else {
                    q->pnext = t;
                }
                t->pnext = p;
                break;
            } else if (strcmp(p->value, Word) == 0) {
                return -1;
            }
            q = p;
            p = p->pnext;
        }
        if (p == NULL) {
            struct BWord *t = (struct BWord *) malloc(sizeof(struct BWord));
            strcpy(t->value, Word);
            t->pnext = NULL;
            q->pnext = t;
        }

        break;
    }


    if (i == size) {
        strcpy(head[size].key, tWord);
        struct BWord *t = (struct BWord *) malloc(sizeof(struct BWord));
        strcpy(t->value, Word);
        t->pnext = NULL;
        head[size].next = t;
        size++;
    }

    return 0;
}

/******************************************************************************
原    型：int FindSimilarWordNum (char* Word);
功    能：查找指定单词在字典中的兄弟单词个数
输入参数：
          Word 指定单词字符串，调用者保证Word指针不为空，指向的是合法单词
输出参数：
          无
返回值：
          返回指定单词在字典中的兄弟单词总个数。如果不存在兄弟单词，返回0
*******************************************************************************/
int FindSimilarWordNum(char *Word) {
    /* 在这里实现功能 */
    char iWord[MAX_WORD_LENGTH + 1];
    int i;
    int num;
    struct BWord *p;

    if (!Word) {
        return 0;
    }

    strcpy(iWord, Word);
    sort(iWord, iWord + strlen(iWord));

    num = 0;
    for (i = 0; i < size; i++) {
        if (strcmp(iWord, head[i].key) != 0) {
            continue;
        }

        p = head[i].next;
        while (p != NULL) {
            if (strcmp(Word, p->value) != 0) {
                num++;
            }
            p = p->pnext;
        }
        break;
    }

    if (i == size) {
        return 0;
    }

    return num;
}

/******************************************************************************
原    型：int FindOneSimilarWord (char* Word, int Seq, char* SimilarWord);
功    能：查找指定单词的指定序号的兄弟单词，指定序号指字典中兄弟单词按字典顺序
          排序后的序号（从1开始）
输入参数：
          Word 指定单词字符串，调用者保证Word指针不为空，指向的是合法单词
          Seq 指定序号（大于等于1）
输出参数：
          SimilarWord 返回兄弟单词字符串，指针不为空，指向的内存由调用者预先分配，
          占51个字节长度，输出的兄弟单词必须紧跟’\0’结束。如果不存在指定序号的
          兄弟单词，输出空串。
返回值：
          -1 失败（如果不存在指定序号的兄弟单词，返回失败）
          0  成功
*******************************************************************************/
int FindOneSimilarWord(char *Word, int Seq, char *SimilarWord) {
    /* 在这里实现功能 */
    char iWord[MAX_WORD_LENGTH + 1];
    int i;
    int num;
    struct BWord *p;

    if (!Word || !SimilarWord) return 0;

    strcpy(iWord, Word);
    sort(iWord, iWord + strlen(iWord));

    num = 0;
    for (i = 0; i < size; i++) {
        if (strcmp(iWord, head[i].key) != 0) {
            continue;
        }

        p = head[i].next;
        while (p != NULL) {
            if (strcmp(Word, p->value) != 0) {
                num++;
            }
            if (num == Seq) {
                strcpy(SimilarWord, p->value);
                return 0;
            }
            p = p->pnext;
        }
        break;
    }
    strcpy(SimilarWord, "");
    return -1;
}


/******************************************************************************
原    型：void ClearAllWords(void);
功    能：清空字典中所有单词
输入参数：
          无
输出参数：
          无
返回值：
          无

*******************************************************************************/
void ClearAllWords(void) {
    /* 在这里实现功能 */

    for (int i = 0; i < size; i++) {
        struct BWord *p = head[i].next;
        while (p != NULL) {
            struct BWord *t = p;
            p = p->pnext;
            free(t);
        }
    }
    size = 0;
}



int main() {

    char *Test_Word[7] = {
            "mock",
            "aabc",
            "abc",
            "ckom",
            "bcaa",
            "abca",};

    AddOneWord(Test_Word[0]);
    AddOneWord(Test_Word[1]);
    AddOneWord(Test_Word[2]);
    AddOneWord(Test_Word[3]);
    AddOneWord(Test_Word[4]);
    AddOneWord(Test_Word[5]);

    int Expectnumber = 1;
    int ActualNumber;
    int Ret;

    ActualNumber = FindSimilarWordNum(Test_Word[0]);
    std::cout << (Expectnumber == ActualNumber) << std::endl;

    char *ExpectWord = {"bcaa"};
    char SimilarWord[51] = {'\0'};
    int Seq = 2;
    Ret = FindOneSimilarWord(Test_Word[1], Seq, SimilarWord);
    std::cout << (0 == Ret) << std::endl;
    std::cout << (!memcmp(ExpectWord, SimilarWord, strlen(ExpectWord) + 1)) << std::endl;
    ClearAllWords();
}
