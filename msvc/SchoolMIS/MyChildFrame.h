#pragma once


// CMyChildFrame 框架

class CMyChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CMyChildFrame)
public:
	CMyChildFrame();           // 动态创建所使用的公开的构造函数
	virtual ~CMyChildFrame();
/*
protected:
	CMyChildFrame();           // 动态创建所使用的受保护的构造函数
	virtual ~CMyChildFrame();
*/
protected:
	DECLARE_MESSAGE_MAP()
};


