#pragma once


// CLoginDlg �Ի���

class CLoginDlg : public CDialog
{
	DECLARE_DYNAMIC(CLoginDlg)

public:
	CLoginDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLoginDlg();

// �Ի�������
	enum { IDD = IDD_LOGINDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_userID;
	CString m_userpassword;
	CString m_usertype;
	afx_msg void OnStnClickedStaticLogintext();
	afx_msg void OnBnClickedOk();
/***********************by jiangxin***********************/
public:
	int count;
/***********************by jiangxin***********************/
};
