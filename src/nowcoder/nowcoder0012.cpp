/**
 * 线性插值
 * https://www.nowcoder.com/practice/91b4c0f9fa9545a582e5b38bb9f6b90e
 * 信号测量的结果包括测量编号和测量值。存在信号测量结果丢弃及测量结果重复的情况。
 * 1.测量编号不连续的情况，认为是测量结果丢弃。对应测量结果丢弃的情况，需要进行插值操作以更准确的评估信号。
 * 采用简化的一阶插值方法,由丢失的测量结果两头的测量值算出两者中间的丢失值。
 * 假设第M个测量结果的测量值为A，第N个测量结果的测量值为B。则需要进行(N-M-1)个测量结果的插值处理。进行一阶线性插值估计的第N+i个测量结果的测量值为A+( (B-A)/(N-M) )*i  (注：N的编号比M大。)
 * 例如：只有测量编号为4的测量结果和测量编号为7的测量结果，测量值分别为4和10
 * 则需要补充测量编号为5和6的测量结果。
 * 其中测量编号为5的测量值=4 + ((10-4)/(7-4))*1 = 6
 * 其中测量编号为6的测量值=4 + ((10-4)/(7-4))*2 = 8
 * 2.测量编号相同，则认为测量结果重复，需要对丢弃后来出现的测量结果。
 * 请根据以上规则进行测量结果的整理。
 * 详细描述：
 * 接口说明
 * 原型：
 * intCleanUpMeasureInfo(MEASURE_INFO_STRUCT* pOriMeasureInfo,intnOriMINum,intnMaxMIRst, MEASURE_INFO_STRUCT* pMeasureInfoRst);
 * 输入参数：
 * MEASURE_INFO_STRUCT* pOriMeasureInfo:         原始测量结果内容，以结构数组方式存放。测量编号已经按升序排列。MEASURE_INFO_STRUCT定义包含编号和测量值，见OJ.h
 * int nOriMINum:                                原始测量结果个数。
 * int nMaxMIRst:                                整理的测量结果最大个数。
 * 输入参数：
 * MEASURE_INFO_STRUCT* pMeasureInfoRst：         整理的测量结果
 * 返回值：
 * Int
 * 整理的测量结果个数
 * 首先，第一行输入两个整数m和n，m是后面要输入的(测量编号，测量结果)对的个数，n不知道干嘛用的，木有用到的说。。。这题目设计得==
 * 然后就是插值了，就是要求出不连续测量编号之间的测量结果。比如已知测量编号和测量结果为(M, A)，(N, B)，且M、N不连续，即M!=N-1，则要对M和N之间的测量编号进行插值，插值公式其实就是直线方程y-A=((B-A)/(N-M))*(x-M)，插值结果要取整。
 */

#include <iostream>
#include <cstdlib>

using namespace std;

typedef struct Node {
    int num;
    int data;
    struct Node *next;
} Node;

Node *createLinkList(int m) //新建链表，指定节点个数
{
    Node *currentNode = (Node *) malloc(sizeof(Node));
    currentNode->next = NULL;
    cin >> currentNode->num >> currentNode->data;
    Node *t = currentNode;
    if (currentNode) {
        for (int i = 1; i <= m - 1; i++) {
            Node *nextNode = (Node *) malloc(sizeof(Node));
            nextNode->next = NULL;
            cin >> nextNode->num >> nextNode->data; //
            currentNode->next = nextNode;
            currentNode = nextNode;
        }
    }
    return t;
}

Node *delSameNode(Node *head) //删除相同标号的
{
    Node *current = head;
    while (current->next != NULL) {
        if (current->next->num == current->num) {
            Node *p = current->next;
            current->next = current->next->next;
            delete p;
        } else {
            current = current->next;
        }
    }
    return head;
}

void autoInsert(Node *head) //进行插值
{
    Node *current = head;
    while (current->next != NULL) {
        int insertNum = (current->next->num) - (current->num) - 1;
        if (insertNum > 0) {
            int data = current->data;
            int nextData = current->next->data;
            int num = current->num;
            int numNext = current->next->num;
            for (int i = 1; i <= insertNum; i++) {
                Node *p = (Node *) malloc(sizeof(Node));
                p->num = current->num + 1;
                p->data = data + ((nextData - data) / (numNext - num)) * i;
                p->next = current->next;
                current->next = p;
                current = p;
            }
        }
        current = current->next;
    }
}

void displayList(Node *head) {
    Node *current = head;
    while (current) {
        cout << current->num << " " << current->data << endl;
        current = current->next;
    }
}

int main() {

    int nOriMINum;
    int nMaxMIRst; // 这个值没有用到
    while (cin >> nOriMINum >> nMaxMIRst) {
        Node *head = createLinkList(nOriMINum);
        delSameNode(head);
        autoInsert(head);
        displayList(head);
        delete[] head;
    }
    return 0;
}

