#pragma once



// CUserChange ������ͼ

class CUserChange : public CFormView
{
	DECLARE_DYNCREATE(CUserChange)

protected:
	CUserChange();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_old;
	CString m_new;
	CString m_new_sure;
/***********************by jiangxin***********************/
private:
	//���öԻ�����������
	CFont Font;
/***********************by jiangxin***********************/
public:
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedChange();
	afx_msg void OnDestroy();
};


