#ifndef _CEXAMPLE_TEST_H
#define _CEXAMPLE_TEST_H

#include <cppunit/extensions/HelperMacros.h>
class CExampleTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( CExampleTest );
	//CPPUNIT_TEST( TestCase01 );
	//CPPUNIT_TEST( TestCase02 );
	//CPPUNIT_TEST( TestCase03 );
	//CPPUNIT_TEST( TestCase04 );
	//CPPUNIT_TEST( TestCase05 );
	//CPPUNIT_TEST( TestCase06 );
	//CPPUNIT_TEST( TestCase07 );
	//CPPUNIT_TEST( TestCase08 );
	//CPPUNIT_TEST( TestCase09 );
	//CPPUNIT_TEST( TestCase10 );
	//CPPUNIT_TEST( TestCase11 );
	//CPPUNIT_TEST( TestCase12 );
	//CPPUNIT_TEST( TestCase13 );
	//CPPUNIT_TEST( TestCase14 );
	//CPPUNIT_TEST( TestCase15 );
	//CPPUNIT_TEST( TestCase16 );
	CPPUNIT_TEST( TestCaseME );
    // ��������Ӳ�����������, �������������������
    // CPPUNIT_TEST( TestCasexx );
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
	void TestCase00();
    // ��������Ӳ�����������, ����������ĳ�Ա����
    // void TestCasexx();
 //   void TestCase01();
	//void TestCase02();
	//void TestCase03();
	//void TestCase04();
	//void TestCase05();
	//void TestCase06();
	//void TestCase07();
	//void TestCase08();
	//void TestCase09();
	//void TestCase10();
	//void TestCase11();
	//void TestCase12();
	//void TestCase13();
	//void TestCase14();
	//void TestCase15();
	//void TestCase16();
	void TestCaseME();
private:
	bool fileCompare(const char *srcFileName,const char *dstFileName);
};

#endif /*_CEXAMPLE_TEST_H*/