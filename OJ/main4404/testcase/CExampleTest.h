#ifndef _CEXAMPLE_TEST_H
#define _CEXAMPLE_TEST_H

#include <cppunit/extensions/HelperMacros.h>

class CExampleTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( CExampleTest );
	CPPUNIT_TEST( TestCase01 );
	CPPUNIT_TEST( TestCase02 );
	CPPUNIT_TEST( TestCase03 );
	CPPUNIT_TEST( TestCase04 );




    // ���������Ӳ�����������, �������������������
    // CPPUNIT_TEST( TestCasexx );
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
    // ���������Ӳ�����������, ����������ĳ�Ա����
    // void TestCasexx();
    void TestCase01();
	void TestCase02();
	void TestCase03();
	void TestCase04();


};

#endif /*_CEXAMPLE_TEST_H*/