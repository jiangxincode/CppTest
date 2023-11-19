// LoginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ODBC.h"
#include "LoginDlg.h"
#include "afxdialogex.h"

/***********************by jiangxin***********************/
#include "USERS.h"

extern CDatabase m_database;
extern CString m_ID;
extern int m_type;
/***********************by jiangxin***********************/



// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialog)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDlg::IDD, pParent)
	, m_userID(_T(""))
	, m_userpassword(_T(""))
	, m_usertype(_T(""))
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_USER_NAME, m_userID);
	DDX_Text(pDX, IDC_EDIT_USER_PASSWORD, m_userpassword);
	DDX_CBString(pDX, IDC_COMBO_TYPE, m_usertype);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
	ON_STN_CLICKED(IDC_STATIC_LOGINTEXT, &CLoginDlg::OnStnClickedStaticLogintext)
	ON_BN_CLICKED(IDOK, &CLoginDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序


void CLoginDlg::OnStnClickedStaticLogintext()
{
	// TODO: 在此添加控件通知处理程序代码
}

/***********************by jiangxin***********************/
void CLoginDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	// 先设置为未登录状态
	BOOL bLogin=FALSE;
	CUSERS *m_recordset=new CUSERS(&m_database);
	CString strSQL;
	// 标志用户类型
	int type=0;
	// 读入用户输入的信息
	UpdateData(TRUE);
	// 确定用户的类型
	if(m_usertype.Compare(L"学生")==0)
		type=1;
	else if(m_usertype.Compare(L"教师")==0)
		type=2;
	else if(m_usertype.Compare(L"管理员")==0)
		type=3;
	// 查询是否有匹配的用户
	strSQL.Format(L"select * from USERS where USER_ID='%s' AND USER_PASSWORD='%s' AND USER_TYPE='%d'",m_userID,m_userpassword,type);
	m_recordset->Open(CRecordset::dynaset,strSQL);
	// 若查询结果为空
	if(m_recordset->GetRecordCount()==0)
	{
		if(count<3)
		{
			MessageBox(L"用户名或密码不正确！");
			count++;
		}
		else
		{
			MessageBox(L"错误次数达三次以上！",L"本窗口即将关闭！");
			EndDialog(IDCANCEL);
		}
	}
	// 成功登陆
	else
	{
		// 记录用户ID和用户类型
		m_ID=m_recordset->m_USER_ID;
		m_type=type;
		bLogin=TRUE;
	}
	if(bLogin)
	{
		// 若登陆成功，返回主框架IDOK
		EndDialog(IDOK);
	}
	else
		m_database.Close();
	CDialog::OnOK();
}
/***********************by jiangxin***********************/