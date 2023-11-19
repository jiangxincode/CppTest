// UserChange.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ODBC.h"
#include "UserChange.h"


// CUserChange
/***********************by jiangxin***********************/
#include "USERS.h"
#include "MainFrm.h"
extern CDatabase m_database;
extern CString m_ID;
extern int m_type;
/***********************by jiangxin***********************/


IMPLEMENT_DYNCREATE(CUserChange, CFormView)

CUserChange::CUserChange()
	: CFormView(CUserChange::IDD)
	, m_old(_T(""))
	, m_new(_T(""))
	, m_new_sure(_T(""))
{

}

CUserChange::~CUserChange()
{
}

void CUserChange::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_OLD, m_old);
	DDX_Text(pDX, IDC_EDIT_NEW, m_new);
	DDX_Text(pDX, IDC_EDIT_NEW_SURE, m_new_sure);
}

BEGIN_MESSAGE_MAP(CUserChange, CFormView)
	ON_BN_CLICKED(IDC_CHANGE, &CUserChange::OnBnClickedChange)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CUserChange ���

#ifdef _DEBUG
void CUserChange::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CUserChange::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CUserChange ��Ϣ�������

/***********************by jiangxin***********************/
void CUserChange::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	// �Զ���������
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit(FALSE);
	// ���ñ���
	GetParentFrame()->SetWindowText(L"�޸�������ϵͳ");
	CenterWindow();
	// ��������
	LOGFONT LogFont;
	GetFont()->GetLogFont(&LogFont);
	LogFont.lfHeight+=LogFont.lfHeight/2;
	LogFont.lfWidth+=LogFont.lfWidth/2;
	Font.CreateFontIndirect(&LogFont);
	GetDlgItem(IDC_STATIC_USER_CHANGE)->SetFont(&Font);
}
/***********************by jiangxin***********************/

/***********************by jiangxin***********************/
void CUserChange::OnBnClickedChange()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ȡ�ÿؼ��е�����
	UpdateData(TRUE);
	CUSERS m_recordset(&m_database);
	CString strSQL;
	strSQL.Format(L"select * from USERS where USER_ID='%s' AND USER_PASSWORD='%s'",m_ID,m_old);
	m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL);
	if(m_recordset.GetRecordCount()==0)
	{
		MessageBox(L"�����벻��ȷ�����������룡");
		m_old="";
		UpdateData(FALSE);
	}
	else
		if(m_new==m_new_sure)
		{
			strSQL.Format(L"update USERS set USER_PASSWORD='%s' where USER_ID='%s'",m_new,m_ID);
			m_database.ExecuteSQL(strSQL);
			MessageBox(L"�����޸ĳɹ���");
			((CMainFrame *)AfxGetMainWnd())->m_pUserChange->DestroyWindow();
		}
		else
		{
			MessageBox(L"��������������벻��ȣ����������룡");
			m_new="";
			m_new_sure="";
			UpdateData(FALSE);
		}
}
/***********************by jiangxin***********************/

/***********************by jiangxin***********************/
void CUserChange::OnDestroy()
{
	CFormView::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	// ʹ�˵��С��޸����롯���ٴο���
	((CMainFrame *)AfxGetMainWnd())->m_bItemUserChange=TRUE;
	// ��ա��޸����롯����ָ��
	((CMainFrame *)AfxGetMainWnd())->m_pUserChange=NULL;
}
/***********************by jiangxin***********************/