#include <cppunit/config/SourcePrefix.h>
#include "CExampleTest.h"
#include <stdlib.h>

#define MAXSIZE 50

struct strqueue
{
	int queue[MAXSIZE];
	int head; /* ��ͷ */
	int tail; /* ��β */
	int num;  /* ��Ԫ�ظ��� */
};

extern bool initqueue(struct strqueue *s);
extern bool enqueue(struct strqueue *s, int x);
extern bool dequeue(struct strqueue *s, int *x);
extern int gethead(struct strqueue *s);
extern int gettail(struct strqueue *s);
extern int getqueuelenth(struct strqueue *s);
extern bool search(struct strqueue *s, int x);

// ע������׵�CppUnit
CPPUNIT_TEST_SUITE_REGISTRATION( CExampleTest );

// SetUp: ��ÿ������ǰִ��һ��
void CExampleTest::setUp()
{
	return;
}

// tearDown: ��ÿ��������ִ��һ��
void CExampleTest::tearDown()
{
	return;
}


/* ����������������������ʼ���������������������������������� */
void CExampleTest::TestCase01_1()
{
	struct strqueue s;
	bool result = 0;
	int i = 0;

	result = initqueue(&s);

	CPPUNIT_ASSERT(result == 1);
	for(i = 0; i < MAXSIZE; i++)
	{
		CPPUNIT_ASSERT(s.queue[i] == 0);
	}
	CPPUNIT_ASSERT(s.head == -1);
	CPPUNIT_ASSERT(s.tail == -1);
	CPPUNIT_ASSERT(s.num == 0);
}
/* ����������������������ʼ���������������������������������� */

/* ���������������������������������������������������������� */
void CExampleTest::TestCase02_1()
{
	struct strqueue s;
	bool result = 0;

	result = initqueue(&s);
	result = enqueue(&s, 1);

	CPPUNIT_ASSERT(result == 1);
	CPPUNIT_ASSERT(s.queue[0] == 1);
	CPPUNIT_ASSERT(s.head == 0);
	CPPUNIT_ASSERT(s.tail == 0);
	CPPUNIT_ASSERT(s.num == 1);
}

void CExampleTest::TestCase02_2()
{
	struct strqueue s;
	bool result = 0;

	result = initqueue(&s);
	result = enqueue(&s, 1);
	result = enqueue(&s, 2);

	CPPUNIT_ASSERT(result == 1);
	CPPUNIT_ASSERT(s.queue[0] == 1);
	CPPUNIT_ASSERT(s.queue[1] == 2);
	CPPUNIT_ASSERT(s.head == 0);
	CPPUNIT_ASSERT(s.tail == 1);
	CPPUNIT_ASSERT(s.num == 2);
}

void CExampleTest::TestCase02_3()
{
	struct strqueue s;
	bool result = 0;

	result = initqueue(&s);

	s.queue[15] = 1;
	s.queue[16] = 2;
	s.queue[17] = 3;
	s.queue[18] = 4;
	s.head = 15;
	s.tail = 18;
	s.num = 4;

	result = enqueue(&s, 5);

	CPPUNIT_ASSERT(result == 1);
	CPPUNIT_ASSERT(s.queue[15] == 1);
	CPPUNIT_ASSERT(s.queue[16] == 2);
	CPPUNIT_ASSERT(s.queue[17] == 3);
	CPPUNIT_ASSERT(s.queue[18] == 4);
	CPPUNIT_ASSERT(s.queue[19] == 5);
	CPPUNIT_ASSERT(s.head == 15);
	CPPUNIT_ASSERT(s.tail == 19);
	CPPUNIT_ASSERT(s.num == 5);
}

void CExampleTest::TestCase02_4()
{
	struct strqueue s;
	bool result = 0;

	result = initqueue(&s);

	s.queue[46] = 1;
	s.queue[47] = 2;
	s.queue[48] = 3;
	s.queue[49] = 4;
	s.head = 46;
	s.tail = 49;
	s.num = 4;

	result = enqueue(&s, 5);

	CPPUNIT_ASSERT(result == 1);
	CPPUNIT_ASSERT(s.queue[46] == 1);
	CPPUNIT_ASSERT(s.queue[47] == 2);
	CPPUNIT_ASSERT(s.queue[48] == 3);
	CPPUNIT_ASSERT(s.queue[49] == 4);
	CPPUNIT_ASSERT(s.queue[0] == 5);
	CPPUNIT_ASSERT(s.head == 46);
	CPPUNIT_ASSERT(s.tail == 0);
	CPPUNIT_ASSERT(s.num == 5);
}

void CExampleTest::TestCase02_5()
{
	struct strqueue s;
	bool result = 0;
	int i = 0;

	result = initqueue(&s);

	for(i = 0; i < MAXSIZE; i++)
	{
		s.queue[i] = i+1;
	}
	s.head = 0;
	s.tail = 49;
	s.num = 50;

	result = enqueue(&s, 51);

	CPPUNIT_ASSERT(result == 0);
	for(i = 0; i < MAXSIZE; i++)
	{
		CPPUNIT_ASSERT(s.queue[i] == (i+1));
	}
	CPPUNIT_ASSERT(s.head == 0);
	CPPUNIT_ASSERT(s.tail == 49);
	CPPUNIT_ASSERT(s.num == 50);
}
/* ���������������������������������������������������������� */

/* ���������������������������������������������������������� */
void CExampleTest::TestCase03_1()
{
	struct strqueue s;
	int x = 0;
	bool result = 0;

	result = initqueue(&s);
	result = dequeue(&s, &x);

	CPPUNIT_ASSERT(result == 0);
	CPPUNIT_ASSERT(s.head == -1);
	CPPUNIT_ASSERT(s.tail == -1);
	CPPUNIT_ASSERT(s.num == 0);
}

void CExampleTest::TestCase03_2()
{
	struct strqueue s;
	int x = 0;
	bool result = 0;

	result = initqueue(&s);
	result = enqueue(&s, 1);
	result = dequeue(&s, &x);

	CPPUNIT_ASSERT(result == 1);
	CPPUNIT_ASSERT(x == 1);
	CPPUNIT_ASSERT(s.queue[0] == 0);
	CPPUNIT_ASSERT(s.head == -1);
	CPPUNIT_ASSERT(s.tail == -1);
	CPPUNIT_ASSERT(s.num == 0);
}

void CExampleTest::TestCase03_3()
{
	struct strqueue s;
	int x = 0;
	bool result = 0;

	result = initqueue(&s);

	s.queue[15] = 1;
	s.queue[16] = 2;
	s.queue[17] = 3;
	s.queue[18] = 4;
	s.head = 15;
	s.tail = 18;
	s.num = 4;

	result = dequeue(&s, &x);

	CPPUNIT_ASSERT(result == 1);
	CPPUNIT_ASSERT(x == 1);
	CPPUNIT_ASSERT(s.queue[15] == 0);
	CPPUNIT_ASSERT(s.queue[16] == 2);
	CPPUNIT_ASSERT(s.queue[17] == 3);
	CPPUNIT_ASSERT(s.queue[18] == 4);
	CPPUNIT_ASSERT(s.head == 16);
	CPPUNIT_ASSERT(s.tail == 18);
	CPPUNIT_ASSERT(s.num == 3);
}

void CExampleTest::TestCase03_4()
{
	struct strqueue s;
	int x = 0;
	bool result = 0;

	result = initqueue(&s);

	s.queue[49] = 1;
	s.queue[0] = 2;
	s.queue[1] = 3;
	s.queue[2] = 4;
	s.head = 49;
	s.tail = 2;
	s.num = 4;

	result = dequeue(&s, &x);

	CPPUNIT_ASSERT(result == 1);
	CPPUNIT_ASSERT(x == 1);
	CPPUNIT_ASSERT(s.queue[49] == 0);
	CPPUNIT_ASSERT(s.queue[0] == 2);
	CPPUNIT_ASSERT(s.queue[1] == 3);
	CPPUNIT_ASSERT(s.queue[2] == 4);
	CPPUNIT_ASSERT(s.head == 0);
	CPPUNIT_ASSERT(s.tail == 2);
	CPPUNIT_ASSERT(s.num == 3);
}
/* ���������������������������������������������������������� */

/* ����������������������ȡ����ͷ��ֵ�������������������������������� */
void CExampleTest::TestCase04_1()
{
	struct strqueue s;
	int x = 0;
	bool result = 0;

	result = initqueue(&s);

	s.queue[15] = 1;
	s.queue[16] = 2;
	s.queue[17] = 3;
	s.queue[18] = 4;
	s.head = 15;
	s.tail = 18;
	s.num = 4;

	x = gethead(&s);

	CPPUNIT_ASSERT(x == 1);
}

void CExampleTest::TestCase04_2()
{
	struct strqueue s;
	int x = 0;
	bool result = 0;

	result = initqueue(&s);

	x = gethead(&s);

	CPPUNIT_ASSERT(x == -1);
}
/* ����������������������ȡ����ͷ��ֵ�������������������������������� */

/* ����������������������ȡ����β��ֵ�������������������������������� */
void CExampleTest::TestCase05_1()
{
	struct strqueue s;
	int x = 0;
	bool result = 0;

	result = initqueue(&s);

	s.queue[15] = 1;
	s.queue[16] = 2;
	s.queue[17] = 3;
	s.queue[18] = 4;
	s.head = 15;
	s.tail = 18;
	s.num = 4;

	x = gettail(&s);

	CPPUNIT_ASSERT(x == 4);
}

void CExampleTest::TestCase05_2()
{
	struct strqueue s;
	int x = 0;
	bool result = 0;

	result = initqueue(&s);

	x = gettail(&s);

	CPPUNIT_ASSERT(x == -1);
}
/* ����������������������ȡ����β��ֵ�������������������������������� */

/* ����������������������ֵ������������������������������������ */
void CExampleTest::TestCase06_1()
{
	struct strqueue s;
	int x = 0;
	bool result = 0;

	result = initqueue(&s);

	s.queue[15] = 1;
	s.queue[16] = 2;
	s.queue[17] = 3;
	s.queue[18] = 4;
	s.head = 15;
	s.tail = 18;
	s.num = 4;

	result = search(&s, 2);

	CPPUNIT_ASSERT(result == 1);
}

void CExampleTest::TestCase06_2()
{
	struct strqueue s;
	int x = 0;
	bool result = 0;

	result = initqueue(&s);

	s.queue[15] = 1;
	s.queue[16] = 2;
	s.queue[17] = 3;
	s.queue[18] = 4;
	s.head = 15;
	s.tail = 18;
	s.num = 4;

	result = search(&s, 5);

	CPPUNIT_ASSERT(result == 0);
}

void CExampleTest::TestCase06_3()
{
	struct strqueue s;
	int x = 0;
	bool result = 0;

	result = initqueue(&s);

	s.queue[48] = 1;
	s.queue[49] = 2;
	s.queue[0] = 3;
	s.queue[1] = 4;
	s.head = 48;
	s.tail = 1;
	s.num = 4;

	result = search(&s, 2);

	CPPUNIT_ASSERT(result == 1);
}

void CExampleTest::TestCase06_4()
{
	struct strqueue s;
	int x = 0;
	bool result = 0;

	result = initqueue(&s);

	s.queue[48] = 1;
	s.queue[49] = 2;
	s.queue[0] = 3;
	s.queue[1] = 4;
	s.head = 48;
	s.tail = 1;
	s.num = 4;

	result = search(&s, 3);

	CPPUNIT_ASSERT(result == 1);
}

void CExampleTest::TestCase06_5()
{
	struct strqueue s;
	int x = 0;
	bool result = 0;

	result = initqueue(&s);

	s.queue[48] = 1;
	s.queue[49] = 2;
	s.queue[0] = 3;
	s.queue[1] = 4;
	s.head = 48;
	s.tail = 1;
	s.num = 4;

	result = search(&s, 5);

	CPPUNIT_ASSERT(result == 0);
}
/* ����������������������ֵ������������������������������������ */