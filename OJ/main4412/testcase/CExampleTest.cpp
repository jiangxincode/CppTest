#include <cppunit/config/SourcePrefix.h>
#include "CExampleTest.h"
#include <stdlib.h>

#include "..\source\CellularDistrict.h"


// ע������׵�CppUnit
CPPUNIT_TEST_SUITE_REGISTRATION( CExampleTest );

// ��������ʵ��ʾ��

// SetUp: ��ÿ������ǰִ��һ��
void CExampleTest::setUp()
{

}

// tearDown: ��ÿ��������ִ��һ��
void CExampleTest::tearDown()
{

}

void CExampleTest::TestCase01()
{
	//1
	{
		tLine aMap [] = {{1,2},{1,3},{2,3}};  int aDrawline[256];
		CPPUNIT_ASSERT(OneLineDrawMap(sizeof(aMap)/sizeof(tLine), aMap, aDrawline) == 0);

		int aDrawline_ok[] = {1,2,3,1};
		CPPUNIT_ASSERT(memcmp(aDrawline, aDrawline_ok, sizeof(aDrawline_ok)) == 0);
	}
}
void CExampleTest::TestCase02()
{
	//2
	{
		tLine aMap[] ={{1,2},{1,4},{2,3},{3,4},{1,3}}; int aDrawline[256];
		CPPUNIT_ASSERT(OneLineDrawMap(sizeof(aMap)/sizeof(tLine),aMap, aDrawline) == 0);

		int aDrawline_ok[6] = {1,2,3,1,4,3};
		CPPUNIT_ASSERT(memcmp(aDrawline, aDrawline_ok, sizeof(aDrawline_ok)) == 0);
	}
}
void CExampleTest::TestCase03()
{
	//3
	{
		tLine aMap[] ={{1,2},{1,4},{2,3},{3,4},{1,3}}; int aDrawline[256];
		CPPUNIT_ASSERT(OneLineDrawMap(sizeof(aMap)/sizeof(tLine), aMap, aDrawline) == 0);

		int aDrawline_ok[] = {1,2,3,1,4,3};
		CPPUNIT_ASSERT(memcmp(aDrawline, aDrawline_ok, sizeof(aDrawline_ok)) == 0);
	}
}