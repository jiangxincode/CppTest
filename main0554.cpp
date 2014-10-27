/**
 * �����ϳ��ĵ�������a��b��Ϊ���ҳ�������noed����node in a����node in b
 * �������㷨�Ŀռ临�Ӷ�O(1)��ʱ�临�Ӷ�O(m+n)
 */

#include <stdlib.h>

struct node
{
    int v;
    node *next;
};
/**
 * ��������ĳ���
 * ����Ϊ�� ����0
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
 * ����ҵ����򷵻�ָ�� ָ�򹫹��ڵ�
 * ����������򷵻ؿ�ָ��
 */
node * findFirstCommonNode(node * pheada, node * pheadb)
{
    size_t lenA = listLen(pheada);
    size_t lenB = listLen(pheadb);
    node * plistA = pheada;
    node * plistB = pheadb;

    //��������,plistA ָ��ϳ���һ��
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

    //һ������,Ѱ�ҹ����ڵ�
    while(plistA!=NULL && plistA != plistB)
    {
        plistA = plistA->next;
        plistB = plistB->next;
    }

    return plistA;
}

