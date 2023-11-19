// LoginDlg.cpp : ʵ���ļ�
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



// CLoginDlg �Ի���

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


// CLoginDlg ��Ϣ�������


void CLoginDlg::OnStnClickedStaticLogintext()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

/***********************by jiangxin***********************/
void CLoginDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ������Ϊδ��¼״̬
	BOOL bLogin=FALSE;
	CUSERS *m_recordset=new CUSERS(&m_database);
	CString strSQL;
	// ��־�û�����
	int type=0;
	// �����û��������Ϣ
	UpdateData(TRUE);
	// ȷ���û�������
	if(m_usertype.Compare(L"ѧ��")==0)
		type=1;
	else if(m_usertype.Compare(L"��ʦ")==0)
		type=2;
	else if(m_usertype.Compare(L"����Ա")==0)
		type=3;
	// ��ѯ�Ƿ���ƥ����û�
	strSQL.Format(L"select * from USERS where USER_ID='%s' AND USER_PASSWORD='%s' AND USER_TYPE='%d'",m_userID,m_userpassword,type);
	m_recordset->Open(CRecordset::dynaset,strSQL);
	// ����ѯ���Ϊ��
	if(m_recordset->GetRecordCount()==0)
	{
		if(count<3)
		{
			MessageBox(L"�û��������벻��ȷ��");
			count++;
		}
		else
		{
			MessageBox(L"����������������ϣ�",L"�����ڼ����رգ�");
			EndDialog(IDCANCEL);
		}
	}
	// �ɹ���½
	else
	{
		// ��¼�û�ID���û�����
		m_ID=m_recordset->m_USER_ID;
		m_type=type;
		bLogin=TRUE;
	}
	if(bLogin)
	{
		// ����½�ɹ������������IDOK
		EndDialog(IDOK);
	}
	else
		m_database.Close();
	CDialog::OnOK();
}
/***********************by jiangxin***********************/