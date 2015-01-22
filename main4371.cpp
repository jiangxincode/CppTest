//unsolved
#include "OJ.h"
#include <iostream>
#include <cstdlib>

using namespace std;

struct ListNode

{

      int       m_nKey;

      ListNode* m_pNext;

};
/*
功能: 输入一个升序单向链表和一个链表节点，向单向链表中按升序插入这个节点。
	  输入为空指针的情况视为异常，另外不考虑节点值相等的情况。

输入: ListNode* pListHead  单向链表
      ListNode* pInsertNode 新插入节点

输出: ListNode* pListHead  单向链表

返回: 正常插入节点返回链表头指针，其它异常返回空指针
*/
ListNode* InsertNodeToList(ListNode* pListHead, ListNode* pInsertNode)
{
	/*在这里实现功能*/
	if(pInsertNode == NULL) //插入结点为空结点
    {
        return pListHead;
    }

    if(pListHead == NULL) //插入链表为空链表
    {
        pListHead = pInsertNode;
        pListHead->m_pNext = NULL;
    }

    if(pListHead->m_nKey > pInsertNode->m_nKey)
    {
        pInsertNode->m_pNext = pListHead;
        pListHead = pInsertNode;
    }

    ListNode *previous = pListHead, *current = pListHead->m_pNext;
    while(pInsertNode->m_nKey > current->m_nKey)
    {
        previous = current;
        current = current->m_pNext;
    }
    pInsertNode->m_pNext = current;
    previous->m_pNext = pInsertNode;

	return pListHead;
}

int main4371()
{
	ListNode astListNode[2];
	ListNode stInsertNode;
	ListNode *pListHead;

	astListNode[0].m_nKey = 1;
	astListNode[0].m_pNext = &astListNode[1];

	astListNode[1].m_nKey = 3;
	astListNode[1].m_pNext = NULL;

	stInsertNode.m_nKey = 2;
	stInsertNode.m_pNext = NULL;

	pListHead = InsertNodeToList(astListNode, &stInsertNode);

	cout << (pListHead == &astListNode[0]) << endl;

	cout << (astListNode[0].m_nKey == 1) << endl;
	cout << (astListNode[0].m_pNext == &stInsertNode) << endl;

	cout << (stInsertNode.m_nKey == 2) << endl;
	cout << (stInsertNode.m_pNext == &astListNode[1]) << endl;

	cout << (astListNode[1].m_nKey == 3) << endl;
	cout << (astListNode[1].m_pNext == NULL) << endl;

//	CPPUNIT_ASSERT(pListHead == &astListNode[0]);
//
//	CPPUNIT_ASSERT(astListNode[0].m_nKey == 1);
//	CPPUNIT_ASSERT(astListNode[0].m_pNext == &stInsertNode);
//
//	CPPUNIT_ASSERT(stInsertNode.m_nKey == 2);
//	CPPUNIT_ASSERT(stInsertNode.m_pNext == &astListNode[1]);
//
//	CPPUNIT_ASSERT(astListNode[1].m_nKey == 3);
//	CPPUNIT_ASSERT(astListNode[1].m_pNext == NULL);
    return 0;
}
