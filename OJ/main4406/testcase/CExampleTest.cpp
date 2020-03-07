#include <cppunit/config/SourcePrefix.h>
#include "CExampleTest.h"
#include <stdlib.h>

extern int SwiCreate(unsigned int swiId, unsigned int prio, void (* proc)(void));
extern int SwiActivate(unsigned int swiId);
extern void Clear();

static unsigned int * schedTrace;
static unsigned int   schedTraceCnt;
static unsigned int   schedTraceSize;

void SchedTraceInit(unsigned int * p, unsigned int size)
{
	schedTrace = p;
	schedTraceCnt = 0;
	schedTraceSize = size;
}

void SchedTraceRecord(unsigned int pid)
{
	if (schedTraceCnt < schedTraceSize)
		schedTrace[schedTraceCnt++] = pid;
}

// 注册测试套到CppUnit
CPPUNIT_TEST_SUITE_REGISTRATION( CExampleTest );

// 测试用例实现示例

// SetUp: 在每个用例前执行一次
void CExampleTest::setUp()
{

}

// tearDown: 在每个用例后执行一次
void CExampleTest::tearDown()
{

}

static void TestCase01_proc1()
{
	SchedTraceRecord(1);
	SwiActivate(2);
	SchedTraceRecord(1);
}

static void TestCase01_proc2()
{
	SchedTraceRecord(2);
	SwiActivate(3);
	SchedTraceRecord(2);
}
static void TestCase01_proc3()
{
	SchedTraceRecord(3);
}

void CExampleTest::TestCase01()
{
	int ret;
	unsigned int trace[10];
	unsigned int expect[] = {1, 2, 2, 3, 1};

	SchedTraceInit(trace, 10);
	Clear();

	ret = SwiCreate(1, 5, TestCase01_proc1);
    CPPUNIT_ASSERT(0 == ret);

	ret = SwiCreate(2, 3, TestCase01_proc2);
    CPPUNIT_ASSERT(0 == ret);

	ret = SwiCreate(3, 4, TestCase01_proc3);
    CPPUNIT_ASSERT(0 == ret);

	ret = SwiActivate(1);
	CPPUNIT_ASSERT(0 == ret);

	CPPUNIT_ASSERT(5 == schedTraceCnt);
	CPPUNIT_ASSERT(0 == memcmp(expect, trace, sizeof(expect)));
}

// 在这里添加测试用例实现
// void CExampleTest::TestCasexx()
// {
//
// }
