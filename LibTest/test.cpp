#include <stdio.h>
#include <conio.h>
//#include "Libjiangxin.h"
#include "..\\Libjiangxin\\Libjiangxin.h"
//#pragma comment(lib, "libjiangxin.lib") //ָ���뾲̬��һ������
#pragma comment(lib, "..\\Debug\\libjiangxin.lib") //ָ���뾲̬��һ������
int main(int argc, char* argv[])
{
	printf( "2 + 3 = %d", add( 2, 3 ) );
	getch();
}