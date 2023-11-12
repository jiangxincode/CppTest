#include <stdio.h>
#include <conio.h>
//#include "Libjiangxin.h"
#include "..\\Libjiangxin\\Libjiangxin.h"
//#pragma comment(lib, "libjiangxin.lib") //指定与静态库一起连接
#pragma comment(lib, "..\\Debug\\libjiangxin.lib") //指定与静态库一起连接
int main(int argc, char* argv[])
{
	printf( "2 + 3 = %d", add( 2, 3 ) );
	getch();
}