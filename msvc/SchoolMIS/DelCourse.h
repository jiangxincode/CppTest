#pragma once
#include "afxcmn.h"



// CDelCourse ������ͼ

class CDelCourse : public CFormView
{
	DECLARE_DYNCREATE(CDelCourse)

protected:
	CDelCourse();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CDelCourse();

public:
	enum { IDD = IDD_DELCOURSE };
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
	CString m_courseID;
	CString m_course_name;
	CString m_course_time;
	CString m_teacher;
	CString m_start;
	CString m_end;
	CString m_cent;
	CString m_require;
	CString m_instruction;
	CListCtrl m_course;
/***********************by jiangxin***********************/
private:
	//���öԻ�����������
	CFont Font;
/***********************by jiangxin***********************/
public:
	virtual void OnInitialUpdate();
	void initial(void);
	void settext(int index);
	afx_msg void OnNMClickListCourse(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonChoice();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonCancle();
};


