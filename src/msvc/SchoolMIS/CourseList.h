#pragma once
#include "afxwin.h"



// CCourseList ������ͼ

class CCourseList : public CFormView
{
	DECLARE_DYNCREATE(CCourseList)

protected:
	CCourseList();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CCourseList();

public:
	enum { IDD = IDD_COURSELIST };
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
	CString m_key;
	CString m_cost;
	CString m_courseID;
	CString m_course_name;
	CString m_class;
	CString m_teacher;
	CString m_dayhour;
	CString m_building;
	CString m_room;
	virtual void OnInitialUpdate();
/***********************by jiangxin***********************/
private:
	//���öԻ�����������
	CFont Font;
/***********************by jiangxin***********************/
public:
	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnDestroy();
	int m_weekday;
};


