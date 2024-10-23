#define _CRT_SECURE_NO_WARNINGS

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <map>
#include <algorithm>
#include <utility>
#include <iostream>
#include "PhoneBookProcess.h"
using namespace std;




/*
功能: 检查是否有两个或多个公司拥有相同的电话号码,并统计输出

输入参数: inFileName  - 包含个性电话号码个数与列表的源文件名      [格式请见题目说明PPT]
        outFileName - 输出统计重复号码的结果的目标文件名                  [格式请见题目说明PPT]

输出参数: 无
返回: 0 - 成功
        1 - 其它各种错误，如文件不存在
*/
// 2 2 2 3 3 3 4 4 4 5 5 5 6 6 6 7 7 7 7 8 8 8 9 9 9 9
// A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
int transTable[26] = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 9};

/***************************************************
将电话号码转换为数字格式
******************************************************/
int trans(char *in)
{
	bool flag=false;
	char cTmp=0;
	int res=0;
	while(*in)
	{
		cTmp=*in;
		if(cTmp>='A' && cTmp<='Z')
		{
			res=res*10+transTable[cTmp-'A'];
		}
		else if(cTmp>='a' && cTmp<='z')
		{
			res=res*10+transTable[cTmp-'a'];
		}
		else if(cTmp=='-')
		{
			++in;
			continue;
		}
		else if(cTmp>='0' && cTmp<='9')
		{
			res=res*10+cTmp-'0';
		}
		else if(10==cTmp)
		{
			break;
		}
		else
		   return -1;
		++in;
	}
	return res;
}


int PhoneBookProcess(const char *inFileName,const char *outFileName)
{
	FILE *fpSrc = NULL;
	FILE *fpDst = NULL;
	char srcLine[50] = {0};
	char dstLine[50] = {0};

	char *pc = NULL; //warning
	int nCount = 0;
	bool flag = false;
	char strOut[50] = {0}; //warning
	int num=0;
	map<int,int> phoneBook;


	if((inFileName == NULL) || (outFileName == NULL))
    {
		return 1;
    }
	fpSrc = fopen(inFileName,"r");
	if (fpSrc == NULL)
	{
		return 1;
	}
	fpDst = fopen(outFileName,"w");
	if (fpDst == NULL)
	{
		fclose(fpSrc);
		return 1;
	}

	if(feof(fpSrc)) //输入不符合规则，至少包括电话号码的数量
    {
		fclose(fpSrc);
        fclose(fpDst);
        return 1;
    }

	memset(srcLine,0,50);
	fgets(srcLine,50,fpSrc);
    sscanf(srcLine,"%d",&nCount);

	while(!feof(fpSrc)) //处理并写入文件
	{
		memset(srcLine,0,50);
		fgets(srcLine,50,fpSrc);
		num = trans(srcLine);
		if(num <= 0) //具有异常字符的号码忽略
        {
			continue;
        }
		phoneBook[num]++;
	}
	fclose(fpSrc);

	for(map<int,int>::iterator iter=phoneBook.begin();iter!=phoneBook.end();++iter)
	{
		if(iter->second > 1)
		{
			fprintf(fpDst,"%d %d\n",iter->first,iter->second);
			flag = true;
		}
	}

	if(flag == false) //如果没有重复，输出相应的信息
    {
		fprintf(fpDst,"%s\n","No duplicates.");
    }
	fclose(fpDst);
	return 0;
}
