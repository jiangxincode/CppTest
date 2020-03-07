#include <cppunit/config/SourcePrefix.h>
#include "CExampleTest.h"
#include <stdlib.h>
#include <string.h>
#include "../source/PhoneBookProcess.h"

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
/*文件比较，相同则返回true,请根据需要自行修改使用，不作为提交内容*/
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


// 请在下面构造更多的测试文件
// void CExampleTest::TestCase02()
// {
// 
// }
