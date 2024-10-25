#pragma once
#include "afxcmn.h"



// CInfoManager 窗体视图

class CInfoManager : public CFormView
{
	DECLARE_DYNCREATE(CInfoManager)

protected:
	CInfoManager();           // 动态创建所使用的受保护的构造函数
	virtual ~CInfoManager();

public:
	enum { IDD = IDD_INFOMANAGER };
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
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	CString m_student_name;
	CString m_student_number;
	CListCtrl m_student;
	CString m_teacher_name;
	CString m_teacher_number;
	CListCtrl m_teacher;
	virtual void OnInitialUpdate();
	void initial(void);
	void settext_student(int index);
	void settext_teacher(int index);
	afx_msg void OnNMClickStudent(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickTeacher(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedStudentAdd();
	afx_msg void OnBnClickedStudentDel();
	afx_msg void OnBnClickedStudentFresh();
	afx_msg void OnBnClickedTeacherAdd();
	afx_msg void OnBnClickedTeacherDel();
	afx_msg void OnBnClickedTeacherFresh();
	afx_msg void OnDestroy();
};


