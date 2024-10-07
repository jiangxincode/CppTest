#pragma once



// CUserChange 窗体视图

class CUserChange : public CFormView
{
	DECLARE_DYNCREATE(CUserChange)

protected:
	CUserChange();           // 动态创建所使用的受保护的构造函数
	virtual ~CUserChange();

public:
	enum { IDD = IDD_USERCHANGE };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_old;
	CString m_new;
	CString m_new_sure;
/***********************by jiangxin***********************/
private:
	//设置对话框标题的字体
	CFont Font;
/***********************by jiangxin***********************/
public:
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedChange();
	afx_msg void OnDestroy();
};


