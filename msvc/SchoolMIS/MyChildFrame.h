#pragma once


// CMyChildFrame ���

class CMyChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CMyChildFrame)
public:
	CMyChildFrame();           // ��̬������ʹ�õĹ����Ĺ��캯��
	virtual ~CMyChildFrame();
/*
protected:
	CMyChildFrame();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CMyChildFrame();
*/
protected:
	DECLARE_MESSAGE_MAP()
};


