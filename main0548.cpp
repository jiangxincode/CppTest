/**
����ж�һ�����������л��ģ���ע�ⲻ���ñ�־λ�����ֻ������������ָ�룩
*/
#include <cstdlib>

struct node
{
    char val;
    node* next;
};

/**
������ָ�룬һ��ÿ�ε���һ����һ��ÿ�ε�������������л��Ļ����߱�Ȼ�غ�
*/
bool check(struct node* head)
{
    if(head==NULL)
    {
        return false;
    }

    struct node *slow=head;

    struct node *fast=head;

    while((fast!=NULL) && (fast->next!=NULL))
    {
        slow=slow->next;
        fast=fast->next->next;

        if(slow==fast) //ָ�����ֱ�ӱȽ�
        {
            return true;
        }
    }

    return false;
}
