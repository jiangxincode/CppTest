//memory leak check

#define _CRTDBG_MAP_ALLOC

#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>

using namespace std;

_CrtMemState s1, s2, s3;


void GetMemory(char *p, int num)
{
	p = (char*)malloc(sizeof(char) * num);
}

/**
 * 检测内存泄露的方法，必须在VS中编译运行
 */
int main()
{
	_CrtMemCheckpoint( &s1 );
	char *str = NULL;

	GetMemory(str, 100);
	_CrtMemCheckpoint( &s2 );

	if ( _CrtMemDifference( &s3, &s1, &s2) )
		_CrtMemDumpStatistics( &s3 );

	cout<<"Memory leak test!"<<endl;
	_CrtDumpMemoryLeaks();

	return 0;
}