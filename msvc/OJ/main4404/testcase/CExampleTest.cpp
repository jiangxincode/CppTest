#include <cppunit/config/SourcePrefix.h>
#include "CExampleTest.h"
#include <stdlib.h>
#include <string.h>
#include "../source/CommonDef.h"
#include "../source/OJ.h"

using namespace std;


// 注册测试套到CppUnit
CPPUNIT_TEST_SUITE_REGISTRATION( CExampleTest );

// 测试用例实现示例

// SetUp: 在每个用例前执行一次

// 测试用例实现示例

// SetUp: 在每个用例前执行一次
void CExampleTest::setUp()
{

}

// tearDown: 在每个用例后执行一次
void CExampleTest::tearDown()
{

}

//测试增加任务(正常增加）
void CExampleTest::TestCase01()
{
	initialize();
	OperateTask(ATask, 1, AddTask);
	OperateTask(BTask, 2, AddTask);
	OperateTask(CTask, 3, AddTask);

	TaskStatus status;
	GetTaskStatus(1, status);
	CPPUNIT_ASSERT(Waiting == status);
	GetTaskStatus(2, status);
	CPPUNIT_ASSERT(Waiting == status);
	GetTaskStatus(3, status);
	CPPUNIT_ASSERT(Waiting == status);

	finitialize();
}



//测试运行任务（正常运行）
void CExampleTest::TestCase02()
{
	initialize();
	OperateTask(ATask, 1, AddTask);
	OperateTask(BTask, 2, AddTask);
	OperateTask(CTask, 3, AddTask);
	OperateTask(ATask, 1, RunTask);
	OperateTask(BTask, 2, RunTask);
	OperateTask(CTask, 3, RunTask);

	TaskStatus status;
	GetTaskStatus(1, status);
	CPPUNIT_ASSERT(Finished == status);
	GetTaskStatus(2, status);
	CPPUNIT_ASSERT(Finished == status);
	GetTaskStatus(3, status);
	CPPUNIT_ASSERT(Finished == status);

	finitialize();
}



//测试删除任务（正常删除）
void CExampleTest::TestCase03()
{
	initialize();
	OperateTask(ATask, 1, AddTask);
	OperateTask(BTask, 2, AddTask);
	OperateTask(CTask, 3, AddTask);
	OperateTask(ATask, 1, RunTask);
	OperateTask(BTask, 2, RunTask);
	OperateTask(CTask, 3, RunTask);
	OperateTask(ATask, 1, DelTask);
	OperateTask(BTask, 2, DelTask);
	OperateTask(CTask, 3, DelTask);

	TaskStatus status;
	GetTaskStatus(1, status);
	CPPUNIT_ASSERT(NotExist == status);
	GetTaskStatus(2, status);
	CPPUNIT_ASSERT(NotExist == status);
	GetTaskStatus(3, status);
	CPPUNIT_ASSERT(NotExist == status);

	finitialize();
}



//测试清除一类任务（正常清除）
void CExampleTest::TestCase04()
{
	initialize();
	OperateTask(ATask, 1, AddTask);
	OperateTask(BTask, 2, AddTask);
	OperateTask(CTask, 3, AddTask);
	OperateTask(ATask, 4, AddTask);
	OperateTask(BTask, 5, AddTask);
	OperateTask(CTask, 6, AddTask);
	OperateTask(ATask, 7, AddTask);
	OperateTask(BTask, 8, AddTask);
	OperateTask(CTask, 9, AddTask);
	OperateTask(ATask, 1, RunTask);
	OperateTask(ATask, 4, RunTask);
	OperateTask(ATask, 7, RunTask);
	bool ret = OperateTask(ATask, 9, ClearTask);
	CPPUNIT_ASSERT(ret == true);

	TaskStatus status;
	GetTaskStatus(1, status);
	CPPUNIT_ASSERT(NotExist == status);
	GetTaskStatus(4, status);
	CPPUNIT_ASSERT(NotExist == status);
	GetTaskStatus(7, status);
	CPPUNIT_ASSERT(NotExist == status);
	
	finitialize();
}

