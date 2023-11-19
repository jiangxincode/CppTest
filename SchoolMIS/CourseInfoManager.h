#pragma once
#include "afxdtctl.h"
#include "afxcmn.h"
#include "atlcomtime.h"



// CCourseInfoManager ������ͼ

class CCourseInfoManager : public CFormView
{
	DECLARE_DYNCREATE(CCourseInfoManager)

protected:
	CCourseInfoManager();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CCourseInfoManager();

public:
	enum { IDD = IDD_COURSEINFOMANAGER };
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
	COleDateTime m_start;
	COleDateTime m_end;
	CDateTimeCtrl m_C_start;
	CDateTimeCtrl m_C_end;
	CString m_cent;
	CString m_require;
	CString m_instruction;
	CListCtrl m_course;
	virtual void OnInitialUpdate();
/***********************by jiangxin***********************/
private:
	//���öԻ�����������
	CFont Font;
/***********************by jiangxin***********************/
public:
	void initial(void);
	void settext(int index);

	afx_msg void OnNMClickListCourse(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonDel();
	afx_msg void OnBnClickedButtonFresh();
	afx_msg void OnBnClickedButtonChange();
	afx_msg void OnDestroy();
};


