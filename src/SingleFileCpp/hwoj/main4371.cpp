/**
 * 向升序单向链表中插入一个节点
 * 输入一个升序单向链表和一个链表节点，向单向链表中按升序插入这个节点。
 * 输入为空指针的情况视为异常，另外不考虑节点值相等的情况。
 * 链表结点定义如下：
 * struct ListNode
 * {
 *       int       m_nKey;
 *       ListNode* m_pNext;
 * };
 * 详细描述：
 * 接口说明
 * 原型：
 * ListNode* InsertNodeToList(ListNode* pListHead, ListNode* pInsertNode);
 * 输入参数：
 *         ListNode* pListHead  单向链表
 *          ListNode* pInsertNode 新插入节点
 * 输出参数（指针指向的内存区域保证有效）：
 *     ListNode* pListHead  单向链表
 * 返回值：
 *     正常插入节点返回链表头指针，其它异常返回空指针
 *
 */
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
        return NULL;
    }

    if(pListHead == NULL) //插入链表为空链表
    {
        pListHead = pInsertNode;
        pListHead->m_pNext = NULL;
        return pListHead;
    }

    if(pListHead->m_nKey > pInsertNode->m_nKey)
    {
        pInsertNode->m_pNext = pListHead;
        pListHead = pInsertNode;
        return pListHead;
    }

    ListNode *previous = pListHead, *current = pListHead->m_pNext;
    while((pInsertNode->m_nKey > current->m_nKey) && (current != NULL))
    {
        previous = current;
        current = current->m_pNext;
    }

    pInsertNode->m_pNext = current;
    previous->m_pNext = pInsertNode;

    return pListHead;
}

int main() {
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

        std::cout << (pListHead == &astListNode[0]) << std::endl;

        std::cout << (astListNode[0].m_nKey == 1) << std::endl;
        std::cout << (astListNode[0].m_pNext == &stInsertNode) << std::endl;

        std::cout << (stInsertNode.m_nKey == 2) << std::endl;
        std::cout << (stInsertNode.m_pNext == &astListNode[1]) << std::endl;

        std::cout << (astListNode[1].m_nKey == 3) << std::endl;
        std::cout << (astListNode[1].m_pNext == NULL) << std::endl;
    }

    {
        ListNode * astListNode = NULL;
        ListNode stInsertNode;
        ListNode *pListHead;

        stInsertNode.m_nKey = 2;
        stInsertNode.m_pNext = NULL;

        pListHead = InsertNodeToList(astListNode, &stInsertNode);

        std::cout << (pListHead == &stInsertNode) << std::endl;

        std::cout << (pListHead->m_nKey == 2) << std::endl;
        std::cout << (pListHead->m_pNext == NULL) << std::endl;
    }

}
