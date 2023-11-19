#pragma once
#include "afxwin.h"
#include "afxdtctl.h"



// CStudentInfo ������ͼ

class CStudentInfo : public CFormView
{
	DECLARE_DYNCREATE(CStudentInfo)

protected:
	CStudentInfo();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CStudentInfo();

public:
	enum { IDD = IDD_STUDENTINFO };
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
	CString m_name;
	CString m_number;
	int m_sex;
	CComboBox m_c_sex;
	CString m_department;
	CString m_major;
	CDateTimeCtrl m_starttime;
	CDateTimeCtrl m_birthday;
	int m_party;
	CComboBox m_c_party;
	CString m_race;
	CString m_phone;
	CString m_hometown;
	CString m_address;
	CString m_other;
/***********************by jiangxin***********************/
	// ��¼�ؼ��Ƿ����˸ı�
	BOOL b_starttime;
	BOOL b_birthday;
	BOOL b_major;
	BOOL b_other;
	BOOL b_race;
	BOOL b_hometown;
	BOOL b_department;
	BOOL b_address;
	BOOL b_phone;
	BOOL b_party;
	BOOL b_sex;
/***********************by jiangxin***********************/
	virtual void OnInitialUpdate();
/***********************by jiangxin***********************/
private:
	//���öԻ�����������
	CFont LoginFont;
/***********************by jiangxin***********************/
public:
	void initial(void);
	afx_msg void OnEnChangeEditDepartment();
	afx_msg void OnEnChangeEditMajor();
	afx_msg void OnCbnSelchangeComboSex();
	afx_msg void OnDtnCloseupDatetimepickerStart(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDtnCloseupDatetimepickerBirthday(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeComboParty();
	afx_msg void OnEnChangeEditRace();
	afx_msg void OnEnChangeEditphone();
	afx_msg void OnEnChangeEditHometown();
	afx_msg void OnEnChangeEditAddress();
	afx_msg void OnEnChangeEditOther();
	afx_msg void OnBnClickedButtonChange();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonCancle();
};


