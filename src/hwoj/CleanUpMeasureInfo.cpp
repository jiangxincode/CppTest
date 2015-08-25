/*
 * CleanUpMeasureInfo.cpp
 *
 *  Created on: 2015年8月25日
 *      Author: Administrator
 * 线性插值
 * 信号测量的结果包括测量编号和测量值。存在信号测量结果丢弃及测量结果重复的情况。

 1.测量编号不连续的情况，认为是测量结果丢弃。对应测量结果丢弃的情况，需要进行插值操作以更准确的评估信号。

 采用简化的一阶插值方法,由丢失的测量结果两头的测量值算出两者中间的丢失值。

 假设第M个测量结果的测量值为A，第N个测量结果的测量值为B。则需要进行(N-M-1)个测量结果的插值处理。进行一阶线性插值估计的第N+i个测量结果的测量值为A+( (B-A)/(N-M) )*i  (注：N的编号比M大。)

 例如：只有测量编号为4的测量结果和测量编号为7的测量结果，测量值分别为4和10

 则需要补充测量编号为5和6的测量结果。

 其中测量编号为5的测量值=4 + ((10-4)/(7-4))*1 = 6

 其中测量编号为6的测量值=4 + ((10-4)/(7-4))*2 = 8



 2.测量编号相同，则认为测量结果重复，需要对丢弃后来出现的测量结果。

 请根据以上规则进行测量结果的整理。

 详细描述：

 接口说明

 原型：

 intCleanUpMeasureInfo(MEASURE_INFO_STRUCT* pOriMeasureInfo,intnOriMINum,intnMaxMIRst, MEASURE_INFO_STRUCT* pMeasureInfoRst);

 输入参数：

 MEASURE_INFO_STRUCT* pOriMeasureInfo:         原始测量结果内容，以结构数组方式存放。测量编号已经按升序排列。MEASURE_INFO_STRUCT定义包含编号和测量值，见OJ.h

 int nOriMINum:                                原始测量结果个数。

 int nMaxMIRst:                                整理的测量结果最大个数。

 输入参数：

 MEASURE_INFO_STRUCT* pMeasureInfoRst：         整理的测量结果

 返回值：

 Int

 整理的测量结果个数
 首先，第一行输入两个整数m和n，m是后面要输入的(测量编号，测量结果)对的个数，n不知道干嘛用的，木有用到的说。。。这题目设计得==

 然后就是插值了，就是要求出不连续测量编号之间的测量结果。比如已知测量编号和测量结果为(M, A)，(N, B)，且M、N不连续，即M!=N-1，则要对M和N之间的测量编号进行插值，插值公式其实就是直线方程y-A=((B-A)/(N-M))*(x-M)，插值结果要取整。
 */

#include <iostream>
#include <cstdlib>

using namespace std;

typedef struct Node
{
	int a;
	int b;
	struct Node *next;
} Node, *LinkList;

LinkList Build(LinkList L, int m) //建立单向链表
{
	LinkList p, q;
	p = L;
	while (m--)
	{
		q = (LinkList) malloc(sizeof(Node));
		cin >> q->a >> q->b;
		q->next = NULL;
		p->next = q;
		p = q;
	}
	return L;
}
LinkList ListNewV1(int m) //新建链表，指定节点个数
{
	Node *head = (Node*) malloc(sizeof(Node));
	head->next = NULL;
	cin >> head->a >> head->b;
	LinkList t = head;
	if (head)
	{
		for (int i = 1; i <= m - 1; i++)
		{
			Node *nextnode = (Node *) malloc(sizeof(Node));
			nextnode->next = NULL; //新建节点
			cin >> nextnode->a >> nextnode->b; //
			head->next = nextnode;
			head = nextnode;
		}
	}
	else
	{
		cout << "head new comes error!" << endl;
	}
	return t;
}
LinkList DelSamEleV1(LinkList L) //删除相同标号的
{
	LinkList temp = L;
	while (temp->next != NULL)
	{

		if (temp->next->a == temp->a)
		{
			temp->next = temp->next->next;
			//free(temp->next);
		}
		else
		{
			temp = temp->next;
		}
	}
	return L;
}
LinkList DeleteSameElem(LinkList L) //相邻的重复元素，删除后者保留前者
{
	LinkList p, q; //,s;
	p = L;
	q = L->next;
	while (q->next)
	{

		if (q->a == q->next->a)
		{
			/*
			 p->next=q->next;
			 s=q;
			 q=q->next;
			 free(s);
			 */
			p = q->next;
			q->next = p->next;
			free(p);

		}
		else
		{
			//p=p->next;
			q = q->next;
		}
	}
	return L;
}
void ListInsertV1(LinkList L, int m) //进行插值
{
	LinkList temp = L, p;
	while (temp->next != NULL)
	{
		int chazhinum = (temp->next->a) - (temp->a);
		if (chazhinum > 1) //出现不连续，需要插值的数量为chazhinum-1
		{ //A+( (B-A)/(N-M) )*i
			int A = temp->b;
			int B = temp->next->b;
			int M = temp->a;
			int N = temp->next->a;
			for (int i = 1; i <= chazhinum - 1; i++)
			{
				p = (LinkList) malloc(sizeof(Node));
				p->a = temp->a + 1; //
				p->b = A + ((B - A) / (N - M)) * i;
				p->next = temp->next; //进行节点的插入
				temp->next = p;
				temp = p;
			}
		}
		temp = temp->next;
	}
}
void LineInsert(LinkList L, int m)
{
	LinkList p = L->next, q;
	while (p->next != NULL) //注意不是while(p!=NULL) 因为后面涉及到p->next->next
	//for(int i=1;i<m;i++)
	{ /*
	 if(p->a==p->next->a)
	 {
	 q=p->next;
	 p->next=p->next->next;
	 free(q);
	 }
	 else */

		if (((p->next->a) - (p->a)) > 1)
		{
			int d = (p->next->a) - (p->a) - 1;
			int A = p->b;
			int B = p->next->b;
			int M = p->a;
			int N = p->next->a;
			for (int i = 1; i <= d; i++)
			{
				q = (LinkList) malloc(sizeof(Node));
				q->a = p->a + 1; //不是 q->a=M+1;
				q->b = A + (B - A) / (N - M) * i;
				q->next = p->next;
				p->next = q;
				p = q;
			}

		}
		p = p->next;
	}
}
void DisplayListV1(LinkList L)
{
	LinkList temp = L;
	while (temp)
	{
		cout << temp->a << " " << temp->b << endl;
		temp = temp->next;
	}
}
void DisplayList(LinkList L)
{
	LinkList p = L->next;
	while (p != NULL) //不是while(p->next!=NULL)
	{
		cout << p->a << " " << p->b << endl;
		p = p->next;
	}
}
int main__()
{
	int m, n;
	cin >> m >> n;
	LinkList L, t;
	L = ListNewV1(m);

	DelSamEleV1(L);
	ListInsertV1(L, m);
	DisplayListV1(L);

	//Build(L,m);
	//DeleteSameElem(L);
	//   //pur_LinkList(L);
	//LineInsert(L,m);
	//DisplayList(L);

	return 0;
}

//解法二
#include <iostream>
using namespace std;
typedef struct node
{

	int a; //编号
	int b; //测量值
	struct node *next;
} node, *linklist;

/*m为输入的数据组数，每组数据为node结构，从第一组输入数据开始连续两两插值，总共需要循环插值操作m-1次，每次循环次数为相邻两组数据编号差-1*/

int maincleanupmeasureinfo()
{

	int i, j, m, n, d, A, B, N, M;
	linklist L, s, p, q;
	L = (linklist) malloc(sizeof(node)); //头结点。动态存储数据 方便删除 插入操作
	p = L;
	cin >> m >> n; //将头节点用于存储m和n的值
	for (i = 0; i < m; i++) //赋值
	{
		s = (linklist) malloc(sizeof(node));
		cin >> s->a >> s->b;
		p->next = s;
		p = s;
	}
	p->next = NULL;
	p = L->next; //第一个数据

	for (i = 1; i < m; i++) //依次对两两之间进行插值
	{
		if (p->a == p->next->a) //编号相同 则丢弃后出现的测量结果
		{
			q = p->next; //缓存待丢弃的位置
			p->next = p->next->next;
			free(q); //释放丢弃的节点
			p = p->next;
		}
		else //编号不同 则进行插值操作 插值数为编号差减一
		{
			d = (p->next->a) - (p->a) - 1;
			A = p->b;
			B = p->next->b;
			M = p->a;
			N = p->next->a;
			for (j = 1; j <= d; j++)
			{
				s = (linklist) malloc(sizeof(node));
				s->a = p->a + 1;
				s->b = A + (B - A) / (N - M) * j;
				s->next = p->next;
				p->next = s;
				p = s;
			}
			p = p->next;
		}
	}
	p = L->next;
	while (p) //打印
	{
		cout << p->a << " " << p->b << endl;
		p = p->next;
	}
	return 1;
}

