
// ODBC.h : ODBC Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CODBCApp:
// �йش����ʵ�֣������ ODBC.cpp
//

class CODBCApp : public CWinAppEx
{
public:
	CODBCApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
protected:
	HMENU  m_hMDIMenu;
	HACCEL m_hMDIAccel;

public:
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	afx_msg void OnFileNew();
	DECLARE_MESSAGE_MAP()
};

extern CODBCApp theApp;