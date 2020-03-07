/**
 * 双链表基本操作 DoubleLink
 * 详细描述：
 * 数据结构（结构体strlnode）定义：
 * •	data保存节点的值
 * •	plast指向上一个节点
 * •	pnext指向下一个节点
 * 下面的所有接口实现中，头结点也表示一个保存实际值的节点
 * 实现接口，每个接口实现1个基本操作：
 * •	void create(struct strlnode **p,int x)：创建1个头节点，头节点表示第0个节点，x表示头节点保存的值，该函数已经实现。
 * •	void insertnode(struct strlnode **p,int i,int x)：在链表的第i个位置插入数值为x的节点，需考虑i异常。
 * •	void deletenode(struct strlnode **p,int i)：删除链表的第i个节点，需释放该节点占用的内存，需考虑i异常。
 * •	int getnodenum(struct strlnode **p)：获取链表的节点个数，空链表返回0。
 * •	void bignumberplus(struct strlnode **plus,struct strlnode **p,struct strlnode **q)：实现两个大整数相加，链表p和链表q中存储两个大整数，相加后的整数存储到plus中。
 * •	void readtolnode(struct strlnode **p,int *a,int size)：将数组a中的数据存储到链表p当中，size为存储的数值的个数。该函数已经实现，举例如下：
 * 123＋4567＝4690
 * p: [plast|data=1|pnext]<-> [plast|data=2|pnext] <-> [plast|data=3|pnext]
 *
 * q:[plast|data=4|pnext]<-> [plast|data=5|pnext] <-> [plast|data=6|pnext] <-> [plast|data=7|pnext]
 *
 * plus:[plast|data=4|pnext]<-> [plast|data=6|pnext] <-> [plast|data=9|pnext] <-> [plast|data=0|pnext]
 *
 * a[3] = {1,2,3}，存储到链表中的顺序和在数组中顺序保持一致：
 * [plast|data=1|pnext]<-> [plast|data=2|pnext] <-> [plast|data=3|pnext]
 * •	void writetosqlist(int *a,struct strlnode *p)：将链表p中的数据存储到数组a中。该函数已经实现，举例如下：
 * [plast|data=1|pnext]<-> [plast|data=2|pnext] <-> [plast|data=3|pnext]，存储到数组中的顺序和在链表中的顺序保持一致：a[3] = {1,2,3}
 * •	题目框架中有7个参考用例，其它用例请执行编写
 * •	重要说明：代码没有实现之前跑用例会访问越界，不用急于解决，代码实现之后问题消失。
 * 涉及知识点：
 * •	双链表基本操作
 * •	数组基本操作
 * •	指针的指针
 * •	动态内存申请和释放
 * •	数组和链表之间的转换
 * •	异常场景用例设计
 * 性能要求：
 * •	无。
 * 建议代码行：
 * •	NBNC：200行以内
 * 圈复杂度要求：
 * •	<= 10
 * 代码工程和用例：
 * C/C++:
 * •	VS2008代码工程
 * •	嵌入工程的CPPUNIT用例
 *
 */
#include <stdlib.h>
#include <string.h>
#include <iostream>

#define null 0
#define MAXSIZE 50

struct strlnode
{
    int data;
    struct strlnode *plast;
    struct strlnode *pnext;
};

int getnodenum(struct strlnode **p);
void readtolnode(struct strlnode **p, int *a, int size);
void writetosqlist(int *a, struct strlnode *p);

/**
 * 创建双链表(表头节点)
 */
void create(struct strlnode **p, int x)
{
    struct strlnode *q = (struct strlnode *)malloc(sizeof(struct strlnode));
    q->data = x;
    q->plast = null;
    q->pnext = null;

    *p = q;

    return;
}

/**
 * 在链表第i个位置插入数据等于x的节点
 */
void insertnode(struct strlnode **p, int i, int x)
{
    if((*p == null) || (i < 0) || (i > getnodenum(p)))
    {
        return;
    }

    struct strlnode *q = *p;
    struct strlnode *r = q->plast;
    int j = 0;

    while(j < i)
    {
        r = q;
        q = q->pnext;
        j++;
    }
    struct strlnode *temp = (struct strlnode*)malloc(sizeof(struct strlnode));
    temp->data = x;
    temp->plast = r;
    temp->pnext = q;
    if(q != null)
    {
        q->plast = temp;
    }

    if(r != null)
    {
        r->pnext = temp;
    }
    else //此处容易忘记
    {
        *p = temp;
    }
}

/**
 * 删除链表中第i个节点
 */
void deletenode(struct strlnode **p, int i)
{
    if((*p == null) || (i < 0) || (i >= getnodenum(p)))
    {
        return;
    }

    struct strlnode *q = *p;
    int j = 0;
    while(j < i)
    {
        q = q->pnext;
        j++;
    }

    /*注意此时q不可能为null，因为i的取值被限制了*/
    if(q->plast == null) //删除第一个结点
    {
        *p = q->pnext;
        if (q->pnext != null)
        {
            q->pnext->plast = null;
        }
        free(q);
    }
    else //删除其它结点
    {
        q->plast->pnext = q->pnext;
        if (q->pnext != null)
        {
            q->pnext->plast = q->plast;
        }
        free(q);
    }

}

/**
 * 获取链表中节点个数
 */
int getnodenum(struct strlnode **p)
{
    int nodenum = 0;
    /* 代码在这里实现 */
    struct strlnode *q = *p;
    while(q != null)
    {
        q = q->pnext;
        nodenum++;
    }
    return nodenum;
}

/**
 * 使用链表实现大整数相加
 */
void bignumberplus(struct strlnode **plus, struct strlnode **p, struct strlnode **q)
{
    int pLength = getnodenum(p);
    int qLength = getnodenum(q);
    int plusLength = (pLength > qLength ? pLength : qLength) + 1;

    int *pArray = (int *)malloc(sizeof(int)*pLength);
    int *qArray = (int *)malloc(sizeof(int)*qLength);
    int *plusArray = (int *)malloc(sizeof(int)*plusLength);

    writetosqlist(pArray, *p);
    writetosqlist(qArray, *q);
    memset(plusArray,0,sizeof(int)*plusLength);

    int carry = 0; //进位

    int pIndex = pLength-1;
    int qIndex = qLength-1;
    int plusIndex = plusLength-1;

    while((pIndex >= 0) && (qIndex >= 0))
    {
        int temp = pArray[pIndex] + qArray[qIndex] + carry;
        if (temp >= 10)
        {
            carry = 1;
            plusArray[plusIndex] = temp - 10;
        }
        else
        {
            carry = 0;
            plusArray[plusIndex] = temp;
        }
        pIndex--;
        qIndex--;
        plusIndex--;
    }
    while(pIndex >= 0)
    {
        int temp = pArray[pIndex] + carry;
        if (temp >= 10)
        {
            carry = 1;
            plusArray[plusIndex] = temp - 10;
        }
        else
        {
            carry = 0;
            plusArray[plusIndex] = temp;
        }
        pIndex--;
        plusIndex--;
    }
    while(qIndex >= 0)
    {
        int temp = qArray[qIndex] + carry;
        if (temp >= 10)
        {
            carry = 1;
            plusArray[plusIndex] = temp - 10;
        }
        else
        {
            carry = 0;
            plusArray[plusIndex] = temp;
        }
        qIndex--;
        plusIndex--;
    }
    if (carry == 1) //此处容易忘记
    {
        plusArray[plusIndex] = 1;
    }
    if (plusArray[0] == 0)
    {
        readtolnode(plus,plusArray+1,plusLength-1);
    }
    else
    {
        readtolnode(plus,plusArray,plusLength);
    }
}

/**
 * 将数组写入链表中，链表中的数据的先后顺序和数组中的顺序要保持一致
 */
void readtolnode(struct strlnode **p, int *a, int size)
{
    int j = 0;
    int data = 0;
    struct strlnode *s = *p;

    s->data = *(a + (size-1));

    for(j = 2; j < (size+1); j++)
    {
        data = *(a + (size-j));
        insertnode(p, 0, data);
    }

    return;
}

/**
 * 将链表写入数组中，数组中的数据的先后顺序和链表中的顺序要保持一致
 */
void writetosqlist(int *a, struct strlnode *p)
{
    int j = 0;
    struct strlnode *s = p;

    while(s != null)
    {
        *(a + j) = s->data;
        s = s->pnext;
        j++;
    }

    return;
}

int main() {
    /* －－－－－－－－－－链表创建类用例－－－－－－－－－－－－－ */
    {
        struct strlnode *p;

        create(&p, 1);

        std::cout << (p != null) << std::endl;
        std::cout << (p->data == 1) << std::endl;
        std::cout << (p->plast == null) << std::endl;
        std::cout << (p->pnext == null) << std::endl;
    }
/* －－－－－－－－－－链表创建类用例－－－－－－－－－－－－－ */


/* －－－－－－－－－－在链表第i个位置插入数据等于x的节点类用例－－－－－－－－－－－－－ */
    {
        struct strlnode *p;

        create(&p, 1);
        insertnode(&p, 1, 2);
        insertnode(&p, 2, 3);
        insertnode(&p, 3, 4);

        insertnode(&p, 2, 5);

        std::cout << (p->data == 1) << std::endl;
        p = p->pnext;
        std::cout << (p->data == 2) << std::endl;
        p = p->pnext;
        std::cout << (p->data == 5) << std::endl;
        p = p->pnext;
        std::cout << (p->data == 3) << std::endl;
        p = p->pnext;
        std::cout << (p->data == 4) << std::endl;
        std::cout << (p->pnext == null) << std::endl;

        p = p->plast;
        std::cout << (p->data == 3) << std::endl;
        p = p->plast;
        std::cout << (p->data == 5) << std::endl;
        p = p->plast;
        std::cout << (p->data == 2) << std::endl;
        p = p->plast;
        std::cout << (p->data == 1) << std::endl;
        std::cout << (p->plast == null) << std::endl;

    }
/* －－－－－－－－－－在链表第i个位置插入数据等于x的节点类用例－－－－－－－－－－－－－ */


/* －－－－－－－－－－删除链表中第i个节点类用例－－－－－－－－－－－－－ */
    {
        struct strlnode *p;

        create(&p, 1);
        insertnode(&p, 1, 2);
        insertnode(&p, 2, 3);
        insertnode(&p, 3, 4);

        deletenode(&p, 2);

        std::cout << (p->data == 1) << std::endl;
        p = p->pnext;
        std::cout << (p->data == 2) << std::endl;
        p = p->pnext;
        std::cout << (p->data == 4) << std::endl;
        std::cout << (p->pnext == null) << std::endl;

        p = p->plast;
        std::cout << (p->data == 2) << std::endl;
        p = p->plast;
        std::cout << (p->data == 1) << std::endl;
        std::cout << (p->plast == null) << std::endl;
    }
/* －－－－－－－－－－删除链表中第i个节点类用例－－－－－－－－－－－－－ */

/* －－－－－－－－－－获取链表中节点个数类用例－－－－－－－－－－－－－ */
    {
        struct strlnode *p;
        int num = 0;

        create(&p, 1);
        insertnode(&p, 1, 2);
        insertnode(&p, 2, 3);
        insertnode(&p, 3, 4);

        num = getnodenum(&p);

        std::cout << (num == 4) << std::endl;
    }
/* －－－－－－－－－－获取链表中节点个数类用例－－－－－－－－－－－－－ */


/* －－－－－－－－－－大整数相加类用例－－－－－－－－－－－－－ */
    {
        struct strlnode *plus;
        struct strlnode *p;
        struct strlnode *q;
        int a[] = {4,8,6,3,0,2,7,9,3,1,0,4,2,1,3,5,2,6};
        int b[] = {9,2,0,8,6,7,8,3,1,0,3,6,9,2,0,1,6,8};
        int j = 0;

        create(&plus, 0);
        create(&p, 0);
        create(&q, 0);

        readtolnode(&p, a, 18);
        readtolnode(&q, b, 18);

        bignumberplus(&plus, &p, &q);

        int result[19];
        writetosqlist(result, plus);
        int c[] = {1,4,0,7,1,7,0,6,2,4,1,4,1,1,3,3,6,9,4};

        for(j = 0; j < 19; j++)
        {
            std::cout << (result[j] == c[j]) << std::endl;
        }
    }

    {
        struct strlnode *plus;
        struct strlnode *p;
        struct strlnode *q;
        int a[] = {4,8,6,3,0,2,7,9,3,1,0,4,2,1,3,5,2,6};
        int b[] = {7,6,0,9,3,4,0,1,9,2,0,8,6,7,8,3,1,0,3,6,9,2,0,1,6,8};
        int j = 0;

        create(&plus, 0);
        create(&p, 0);
        create(&q, 0);

        readtolnode(&p, a, 18);
        readtolnode(&q, b, 26);

        bignumberplus(&plus, &p, &q);

        int result[26];
        writetosqlist(result, plus);
        int c[] = {7,6,0,9,3,4,0,2,4,0,7,1,7,0,6,2,4,1,4,1,1,3,3,6,9,4};

        for(j = 0; j < 26; j++)
        {
            std::cout << (result[j] == c[j]) << std::endl;
        }
    }

    {
        struct strlnode *plus;
        struct strlnode *p;
        struct strlnode *q;
        int a[] = {7,6,0,9,3,4,0,1,9,2,0,8,6,7,8,3,1,0,3,6,9,2,0,1,6,8};
        int b[] = {4,8,6,3,0,2,7,9,3,1,0,4,2,1,3,5,2,6};
        int j = 0;

        create(&plus, 0);
        create(&p, 0);
        create(&q, 0);

        readtolnode(&p, a, 26);
        readtolnode(&q, b, 18);

        bignumberplus(&plus, &p, &q);

        int result[26];
        writetosqlist(result, plus);
        int c[] = {7,6,0,9,3,4,0,2,4,0,7,1,7,0,6,2,4,1,4,1,1,3,3,6,9,4};

        for(j = 0; j < 26; j++)
        {
            std::cout << (result[j] == c[j]) << std::endl;
        }
    }
/* －－－－－－－－－－大整数相加类用例－－－－－－－－－－－－－ */
}




