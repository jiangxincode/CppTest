#pragma once
#include "afxcmn.h"



// CTeacherScore ������ͼ

class CTeacherScore : public CFormView
{
	DECLARE_DYNCREATE(CTeacherScore)

protected:
	CTeacherScore();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CTeacherScore();

public:
	enum { IDD = IDD_TEACHERSCORE };
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
	CString m_stuID;
	CString m_courseID;
	CString m_score;
	CString m_course_name;
	CListCtrl m_student;
	CListCtrl m_course;
/***********************by jiangxin***********************/
private:
	//���öԻ�����������
	CFont Font;
/***********************by jiangxin***********************/
public:
	virtual void OnInitialUpdate();
	void initial(void);
	void course_settext(int index);
	afx_msg void OnNMClickListCourse(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListStudent(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonSure();
	afx_msg void OnBnClickedButtonCancel();
	afx_msg void OnDestroy();
};


