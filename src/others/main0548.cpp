/**
如何判断一个单链表是有环的？（注意不能用标志位，最多只能用两个额外指针）
*/
#include <cstdlib>

struct node
{
    char val;
    node* next;
};

/**
搞两个指针，一个每次递增一步，一个每次递增两步，如果有环的话两者必然重合
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

        if(slow==fast) //指针可以直接比较
        {
            return true;
        }
    }

    return false;
}

int main() {
	return 0;
}
