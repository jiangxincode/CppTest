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
����: ����Ƿ�������������˾ӵ����ͬ�ĵ绰����,��ͳ�����

�������: inFileName  - �������Ե绰����������б��Դ�ļ���      [��ʽ�����Ŀ˵��PPT]
        outFileName - ���ͳ���ظ�����Ľ����Ŀ���ļ���                  [��ʽ�����Ŀ˵��PPT]

�������: ��
����: 0 - �ɹ�
        1 - �������ִ������ļ�������
*/
// 2 2 2 3 3 3 4 4 4 5 5 5 6 6 6 7 7 7 7 8 8 8 9 9 9 9
// A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
int transTable[26] = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 9};

/***************************************************
���绰����ת��Ϊ���ָ�ʽ
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

	if(feof(fpSrc)) //���벻���Ϲ������ٰ����绰���������
    {
		fclose(fpSrc);
        fclose(fpDst);
        return 1;
    }

	memset(srcLine,0,50);
	fgets(srcLine,50,fpSrc);
    sscanf(srcLine,"%d",&nCount);

	while(!feof(fpSrc)) //����д���ļ�
	{
		memset(srcLine,0,50);
		fgets(srcLine,50,fpSrc);
		num = trans(srcLine);
		if(num <= 0) //�����쳣�ַ��ĺ������
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

	if(flag == false) //���û���ظ��������Ӧ����Ϣ
    {
		fprintf(fpDst,"%s\n","No duplicates.");
    }
	fclose(fpDst);
	return 0;
}
