
// Static Text.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CStaticTextApp:
// �йش����ʵ�֣������ Static Text.cpp
//

class CStaticTextApp : public CWinApp
{
public:
	CStaticTextApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CStaticTextApp theApp;