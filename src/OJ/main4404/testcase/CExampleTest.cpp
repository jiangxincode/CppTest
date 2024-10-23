#include <cppunit/config/SourcePrefix.h>
#include "CExampleTest.h"
#include <cstdlib>
#include <cstring>
#include "../source/CommonDef.h"
#include "../source/OJ.h"

using namespace std;


// ע������׵�CppUnit
CPPUNIT_TEST_SUITE_REGISTRATION( CExampleTest );

// ��������ʵ��ʾ��

// SetUp: ��ÿ������ǰִ��һ��

// ��������ʵ��ʾ��

// SetUp: ��ÿ������ǰִ��һ��
void CExampleTest::setUp()
{

}

// tearDown: ��ÿ��������ִ��һ��
void CExampleTest::tearDown()
{

}

//������������(�������ӣ�
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



//�������������������У�
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



//����ɾ����������ɾ����
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



//�������һ���������������
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

