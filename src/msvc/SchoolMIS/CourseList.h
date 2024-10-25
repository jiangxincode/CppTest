#pragma once
#include "afxwin.h"



// CCourseList 窗体视图

class CCourseList : public CFormView
{
	DECLARE_DYNCREATE(CCourseList)

protected:
	CCourseList();           // 动态创建所使用的受保护的构造函数
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
	//设置对话框标题的字体
	CFont Font;
/***********************by jiangxin***********************/
public:
	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnDestroy();
	int m_weekday;
};


