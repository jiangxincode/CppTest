#pragma once


// CLoginDlg 对话框

class CLoginDlg : public CDialog
{
	DECLARE_DYNAMIC(CLoginDlg)

public:
	CLoginDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLoginDlg();

// 对话框数据
	enum { IDD = IDD_LOGINDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
