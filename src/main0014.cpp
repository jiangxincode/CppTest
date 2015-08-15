/**
 * 一个学生的信息是：姓名，学号，性别，年龄等信息，
 * 用一个链表，把这些学生信息连在一起，
 * 给出一个age, 在些链表中删除学生年龄等于age的学生信息。
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stu
{
    char name[20];
    char sex;
    int no;
    int age;
    struct stu * next;
};

/** \brief 创建链表
 *
 * \param n 学生人数
 * \return 创建成功则返回所创建链表的头结点，否则返回NULL
 *
 */

struct stu *create_list(int n)
{
    if(n <= 0)
    {
        return NULL;
    }

    struct stu *head,*previous,*current; //head为头结点，previous为前一结点，current为当前结点

    printf("Please input the information of the student: name sex no age:\n");

    head = (struct stu *)malloc(sizeof(struct stu));

    memset(head, 0, sizeof(struct stu));

    scanf("%19s %c %11d %11d",head->name,&(head->sex),&(head->no),&(head->age));

    head->next = NULL;

    previous = head;

    for(int i=1; i<n; i++)
    {
        current = (struct stu *)malloc(sizeof(struct stu));
        previous->next = current;
        printf("Please input the information of the student: name sex no age:\n");
        scanf("%19s %c %11d %11d",current->name,&(current->sex),&(current->no),&(current->age));
        current->next = NULL;
        previous = current;
    }

    return(head);
}

/** \brief 删除指定年龄的节点
 *
 * \param list 所要操作的链表
 * \param age 指定需要删除的年龄
 * \return 返回新的链表头结点
 *
 */

struct stu* delete_node(struct stu *list,int age)
{
    struct stu *previous = list;

    while((previous->age == age) && (previous != NULL))
    {
        struct stu *temp = previous;
        previous = previous->next;
        free(temp);
    }

    if(previous == NULL)
    {
        return NULL;
    }

    list = previous; //设置新的头结点
    struct stu *current = previous->next;

    while(current != NULL)
    {
        if(current->age == age)
        {
            previous->next = current->next;
            free(current);
            current = previous->next;
        }
        else
        {
            previous = current;
            current = current->next;
        }
    }

    return list;
}

/** \brief 打印链表
 *
 * \param list 待打印链表
 * \return 无
 *
 */

void display_list(struct stu *list)
{
    while(list != NULL)
    {
        printf("%s %c %d %d\n",list->name,list->sex,list->no,list->age);
        list = list->next;
    }
}

/** \cond */
void main0014()
{
    struct stu *s;
    int n,age;
    printf("Please input the length of the list:\n");
    scanf("%11d",&n);
    s = create_list(n);
    display_list(s);
    printf("Please input the age:\n");
    scanf("%11d",&age);
    s = delete_node(s,age);
    display_list(s);
}
/** \endcond */

