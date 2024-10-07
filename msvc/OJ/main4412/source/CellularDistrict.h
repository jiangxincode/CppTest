#pragma once


//结构体tLine表示一条双向的线段
typedef struct
{
	int pot1;
	int pot2;
}tLine;


//一笔画出给定图形
int OneLineDrawMap (int n, tLine *arrLines, int* aDrawline) ;