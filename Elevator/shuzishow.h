// shuzishow.h: interface for the shuzishow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHUZISHOW_H__EA130FA8_F186_4BA3_BB27_37F1FD1C03F7__INCLUDED_)
#define AFX_SHUZISHOW_H__EA130FA8_F186_4BA3_BB27_37F1FD1C03F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class shuzishow  
{
public:
	void set(CDialog *parent,int tnum,int tx,int ty,int tspace);
	void showicon(CString temp);
	int change(char a);
	shuzishow();
	CString m_time;
	CStatic *m_pictur[50];// ��̬ͼ ָ������

	virtual ~shuzishow();
	int num;// ��̬ͼ����
	int x;// ��ʼX����
	int y;// ��ʼY����
	int space;// ������֮�� ���

};

#endif // !defined(AFX_SHUZISHOW_H__EA130FA8_F186_4BA3_BB27_37F1FD1C03F7__INCLUDED_)
