// ShowingNumber.cpp: implementation of the ShowingNumber class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Elevator.h"
#include "ShowingNumber.h"
#include "ElevatorDlg.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ShowingNumber::ShowingNumber()
{

}

ShowingNumber::~ShowingNumber()
{

}

int ShowingNumber::change(char a)
{
	switch(a) 
	{
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':return a-'0';
		break;
	case '<':return 10;//shang
		break;
	case '>':return 11;//xia
		
		break;
	default: return 0;
	}

}

void ShowingNumber::showicon(CString temp)
{
	m_time=temp;
	int mynum=m_time.GetLength();
	int k;
	
	for(k=0;k<num-mynum;k++)//���ǰ���ͼ����ʾ
	{
		CImageList m_imgList;
		m_imgList.Create(IDB_BITMAP1,12, 1, RGB(255,255,255));//����λͼ�� ÿ��λͼ12����
		HICON myico= m_imgList.ExtractIcon(10);	//ȡ��ͼ��
		m_pictur[k]->SetIcon(myico);//������ʾ��ͼ��		
	}
	for(int i=k;i<num;i++)//�������ͼ����ʾ
	{
		CImageList m_imgList;
		m_imgList.Create(IDB_BITMAP1,12, 1, RGB(255,255,255));
		HICON myico= m_imgList.ExtractIcon(change(m_time[i-k]));	
		m_pictur[i]->SetIcon(myico);	
	}	

}

void ShowingNumber::set(CDialog *parent, int tnum, int tx, int ty, int tspace)
{
	CElevatorDlg *mypar=(CElevatorDlg*)parent;
	for(int i=0;i<num;i++)// ɾ����ǰ�����
		delete *(m_pictur+i);
	// ���ø���Ա����
	num=tnum; x=tx;y=ty;space=tspace;
	for(int j=0;j<num;j++)//���·���
		m_pictur[j]=new(CStatic);
	for(int k=0;k<num;k++)
	{
		//ȷ����ʾλ��
		CRect aa1(x+k*(space+12),y,40+x+k*(space+12),40+y);
		m_pictur[k]->Create(NULL,SS_ICON,aa1,mypar,1);// ������̬ͼ��ؼ�
		m_pictur[k]->ShowWindow(true);
	}

}
