// ShowingNumber.h: interface for the ShowingNumber class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHOWINGNUMBER_H__EA130FA8_F186_4BA3_BB27_37F1FD1C03F7__INCLUDED_)
#define AFX_SHOWINGNUMBER_H__EA130FA8_F186_4BA3_BB27_37F1FD1C03F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ShowingNumber  
{
public:
	void set(CDialog *parent,int tnum,int tx,int ty,int tspace);
	void showicon(CString temp);
	int change(char a);
	ShowingNumber();
	CString m_time;
	CStatic *m_pictur[50];// ��̬ͼ ָ������

	virtual ~ShowingNumber();
	int num;// ��̬ͼ����
	int x;// ��ʼX����
	int y;// ��ʼY����
	int space;// ������֮�� ���

};

#endif // !defined(AFX_SHOWINGNUMBER_H__EA130FA8_F186_4BA3_BB27_37F1FD1C03F7__INCLUDED_)
