// UserChange.cpp : 实现文件
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


// CUserChange 诊断

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


// CUserChange 消息处理程序

/***********************by jiangxin***********************/
void CUserChange::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	// 自动调整窗口
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit(FALSE);
	// 设置标题
	GetParentFrame()->SetWindowText(L"修改密码子系统");
	CenterWindow();
	// 设置字体
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
	// TODO: 在此添加控件通知处理程序代码
	// 取得控件中的内容
	UpdateData(TRUE);
	CUSERS m_recordset(&m_database);
	CString strSQL;
	strSQL.Format(L"select * from USERS where USER_ID='%s' AND USER_PASSWORD='%s'",m_ID,m_old);
	m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL);
	if(m_recordset.GetRecordCount()==0)
	{
		MessageBox(L"旧密码不正确，请重新输入！");
		m_old="";
		UpdateData(FALSE);
	}
	else
		if(m_new==m_new_sure)
		{
			strSQL.Format(L"update USERS set USER_PASSWORD='%s' where USER_ID='%s'",m_new,m_ID);
			m_database.ExecuteSQL(strSQL);
			MessageBox(L"密码修改成功！");
			((CMainFrame *)AfxGetMainWnd())->m_pUserChange->DestroyWindow();
		}
		else
		{
			MessageBox(L"两次输入的新密码不相等，请重新输入！");
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

	// TODO: 在此处添加消息处理程序代码
	// 使菜单中‘修改密码’项再次可用
	((CMainFrame *)AfxGetMainWnd())->m_bItemUserChange=TRUE;
	// 清空‘修改密码’窗口指针
	((CMainFrame *)AfxGetMainWnd())->m_pUserChange=NULL;
}
/***********************by jiangxin***********************/