#pragma once
#include "afxwin.h"
#include "atlcomtime.h"
#include "afxdtctl.h"



// CTeacherInfo 窗体视图

class CTeacherInfo : public CFormView
{
	DECLARE_DYNCREATE(CTeacherInfo)

protected:
	CTeacherInfo();           // 动态创建所使用的受保护的构造函数
	virtual ~CTeacherInfo();

public:
	enum { IDD = IDD_TEACHERINFO };
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
	CString m_name;
	CString m_number;
	CString m_department;
	CString m_major;
	int m_sex;
	CComboBox m_c_sex;
	int m_title;
	CComboBox m_c_title;
	//COleDateTime m_birthday;
	int m_party;
	CComboBox m_c_party;
	CString m_race;
	CString m_phone;
	CString m_hometown;
	CString m_address;
	CString m_other;
/***********************by jiangxin***********************/
	// 记录控件是否发生了改变
	BOOL b_title;
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
/***********************by jiangxin***********************/
private:
	//设置对话框标题的字体
	CFont Font;
/***********************by jiangxin***********************/
	virtual void OnInitialUpdate();
public:
	void initial(void);
	CDateTimeCtrl m_birthday;
	afx_msg void OnCbnSelchangeComboId();
	afx_msg void OnCbnSelchangeComboSex();
	afx_msg void OnEnChangeEditDepartment();
	afx_msg void OnEnChangeEditMajor();
	afx_msg void OnCbnSelchangeComboTitle();
	afx_msg void OnDtnDatetimechangeDatetimepickerBirthday(NMHDR *pNMHDR, LRESULT *pResult);
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


