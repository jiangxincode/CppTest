/**
 * 删除链表中的重复节点、剩余节点逆序输出
 * 题目描述：
 * 输入一个不带头节点的单向链表(链表的节点数小于100),删除链表中内容重复的节点（重复的节点全部删除），剩余的节点逆序倒排。
 * 要求实现函数：
 * void vChanProcess(strNode * pstrIn,strNode * pstrOut);
 * 【输入】 pstrIn：输入一个不带头节点的单向链表
 * 【输出】 pstrOut：删除内容重复的节点（重复的节点全部删除），剩余节点逆序输出(不带头节点,链表第一个节点的内存已经申请)。
 * 【注意】只需要完成该函数功能算法，中间不需要有任何IO的输入输出
 * 示例
 * 输入链表的内容依次为 6,7,8,8,9,10,6
 * 则输出链表的内容依次应该是 10,9,7
 *
 */
#include <stdlib.h>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>
#include "iostream"
#include <cstring>

using namespace std;

typedef struct strNode
{
    int data;
    strNode * pstrNext;
}strNode;


/*
功能:  输入一个不带头节点的单向链表(链表的节点数小于100),删除链表中内容重复的节点（重复的节点全部删除），剩余的节点逆序倒排。

输入:   pstrIn： 输入一个不带头节点的单向链表

输出:   pstrOut：删除内容重复的节点后，逆序排列的链表(不带头节点,链表第一个节点的内存已经申请)。

返回:

示例:
输入链表的内容依次为 6,7,8,8,9,10,6
则输出链表的内容依次应该是 10,9,7
*/


int iChanProcess(strNode * pstrIn,strNode * pstrOut)
{
    vector<int> vec;
    map<int,int> m;
    while (pstrIn != NULL)
    {
        if (m.find(pstrIn->data) != m.end())
        {
            m[pstrIn->data]++;
        }
        else
        {
            pair<int,int> p(pstrIn->data,1);
            m.insert(p);
        }
        pstrIn = pstrIn->pstrNext;
    }
    for (map<int,int>::iterator it=m.begin();it!=m.end();++it)
    {
        pair<int,int> p = *it;
        if (p.second == 1)
        {
            vec.push_back(p.first);
        }
    }
    sort(vec.begin(),vec.end());

    pstrOut->data = vec[vec.size()-1];
    pstrOut->pstrNext = NULL;
    strNode *p = pstrOut;
    for (int i=vec.size()-2;i>=0;i--)
    {
        strNode *temp = (strNode*)malloc(sizeof(strNode));
        temp->data = vec[i];
        temp->pstrNext = NULL;
        p->pstrNext = temp;
        p = p->pstrNext;
    }

    return 0;
}

/* 释放链表 */
void vFreeChan(strNode * pstrChan)
{

    return;
}


// for test
strNode *vCreatChan(int * piData, int iNum)
{
    int       iLoop         = 0;
    strNode * pstrChanHead  = NULL;
    strNode * pstrChanEnd   = NULL;
    strNode * pstTemp       = NULL;

    if ((NULL == piData) || (iNum < 1))
    {
        return NULL;
    }

    pstrChanHead = (strNode *)malloc(sizeof(strNode));
    pstrChanHead->data     = *piData;
    pstrChanHead->pstrNext = NULL;

    pstrChanEnd = pstrChanHead;

    for (iLoop = 1; iLoop < iNum; iLoop++)
    {
        pstTemp = (strNode *)malloc(sizeof(strNode));
        pstTemp->data = piData[iLoop];
        pstTemp->pstrNext = NULL;

        pstrChanEnd->pstrNext = pstTemp;
        pstrChanEnd = pstrChanEnd->pstrNext;
    }

    return pstrChanHead;
}

int iChanToArray(strNode *pstrChan, int * piData, int * piLenth)
{
    int      iLoop    = 0;
    strNode *pstrTemp = pstrChan;

    if ((NULL == pstrChan) || (NULL == piData) || (NULL == piLenth))
    {
        return -1;
    }

    while(NULL != pstrTemp)
    {
        *(piData + iLoop) = pstrTemp->data;
        pstrTemp = pstrTemp->pstrNext;
        iLoop++;
    }

    *piLenth = iLoop;

    return 0;
}


int main()
{
    /* TODO: 请测试时改变改用例 */
    strNode * pstrIn  = NULL;
    strNode * pstrOut = NULL;
    int  iLenth  = 0;
    int  iaDataIn[7]    = {6, 7, 8, 8 ,9, 10, 6};
    int  iaDataOut[7]   = {10,9,7};
    int  iaDataMyOut[7] = {0};

    pstrIn = vCreatChan(iaDataIn, 7);
    pstrOut = (strNode *)malloc(sizeof(strNode));
    pstrOut->pstrNext = NULL;
    /* TODO: 调用被测函数 */
    //请考生自己构造单向链表进行测试
    iChanProcess(pstrIn,pstrOut);

    /* TODO: 执行完成后可比较是否是你认为正确的值 */
    iChanToArray(pstrOut, iaDataMyOut, &iLenth);
    //printf("%d\n",pstrOut->data);
    std::cout << (3 == iLenth) << std::endl;
    std::cout << (0 == memcmp((char *)iaDataOut, (char *)iaDataMyOut, sizeof(int) * iLenth)) << std::endl;

    /* 释放内存*/
    vFreeChan(pstrIn);
    vFreeChan(pstrOut);
}
