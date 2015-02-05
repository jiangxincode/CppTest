/**
 * 两个较长的单向链表a和b，为了找出及诶单noed满足node in a并且node in b
 * 本方法算法的空间复杂度O(1)，时间复杂度O(m+n)
 */

#include <stdlib.h>

struct node
{
    int v;
    node *next;
};
/**
 * 返回链表的长度
 * 链表为空 返回0
 */
size_t listLen(node * p)
{
    size_t num = 0;

    while(p!=NULL)
    {
        num++;
        p = p->next;
    }

    return num;
}
/**
 * 如果找到了则返回指针 指向公共节点
 * 如果不存在则返回空指针
 */
node * findFirstCommonNode(node * pheada, node * pheadb)
{
    size_t lenA = listLen(pheada);
    size_t lenB = listLen(pheadb);
    node * plistA = pheada;
    node * plistB = pheadb;

    //调整长度,plistA 指向较长的一个
    if(lenA < lenB)
    {
        plistB = pheada;
        plistA = pheadb;
        size_t t = lenA;
        lenA = lenB;
        lenB = t;
    }

    while(lenA > lenB)
    {
        plistA = plistA->next;
        --lenA;
    }

    //一样长了,寻找公共节点
    while(plistA!=NULL && plistA != plistB)
    {
        plistA = plistA->next;
        plistB = plistB->next;
    }

    return plistA;
}

