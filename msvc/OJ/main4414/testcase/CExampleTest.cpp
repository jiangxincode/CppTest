#include <cppunit/config/SourcePrefix.h>
#include "CExampleTest.h"
#include <stdlib.h>
#include <string.h>
#include "../source/PhoneBookProcess.h"

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
/*�ļ��Ƚϣ���ͬ�򷵻�true,�������Ҫ�����޸�ʹ�ã�����Ϊ�ύ����*/
bool CExampleTest::fileCompare(const char *srcFileName,const char *dstFileName)
{
	FILE *fpSrc = NULL;
	FILE *fpDst = NULL;
	char srcLine[32]={0};
	char dstLine[32]={0};
	bool ret = true;
	fpSrc = fopen(srcFileName,"r");
	if (NULL == fpSrc)
	{
		return false;
	}
	fpDst = fopen(dstFileName,"r");
	if (NULL == fpDst)
	{
		fclose(fpSrc);
		return false;
	}

	while(!feof(fpSrc) &&!feof(fpDst))
	{
		memset(srcLine,0,32);
		memset(dstLine,0,32);
		fgets(srcLine,32,fpSrc);
		fgets(dstLine,32,fpDst);
		if (0 != strcmp(srcLine,dstLine))
		{
			ret = false;
			break;
		}
	}
	if (!feof(fpSrc) || !feof(fpDst))
	{
		ret = false;
	}
	fclose(fpSrc);
	fclose(fpDst);
	return ret;
}

void CExampleTest::TestCaseME()
{
	CPPUNIT_ASSERT(0 == PhoneBookProcess("ME.dat","ME.mex"));
	CPPUNIT_ASSERT(true == fileCompare("ME.mex","ME.out"));
}


// �������湹�����Ĳ����ļ�
// void CExampleTest::TestCase02()
// {
// 
// }
