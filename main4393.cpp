//unsolved 一个测试用例未通过

#include <stdlib.h>
#include <string.h>
#include "oj.h"

#include <iostream>

using namespace std;

/*
功能:

输入:

输出:

返回:成功0,其它-1

*/

int ProcessString( char * strInput,char chSrc,char chDes ,char * strOutput)
{
    unsigned i = 0;
    while(*(strInput+i) != '\0')
    {
        if(*(strInput+i) == chSrc)
        {
            *(strOutput+i) = chDes;
        }
        else
        {
            *(strOutput+i) = *(strInput+i);
        }
        i++;
    }
    strOutput[i] = '\0';
	return 0;
}

int main4393()
{
    char strInput[] = "d545";

	//char strSrc[] = "d545c";
	char strOutput[10] = "";
	ProcessString(strInput,'a','c',strOutput);
	cout << strOutput << endl;
    return 0;
}
