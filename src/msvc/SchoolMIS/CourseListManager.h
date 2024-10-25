#pragma once
#include "afxcmn.h"
#include "afxwin.h"



// CCourseListManager ������ͼ

class CCourseListManager : public CFormView
{
	DECLARE_DYNCREATE(CCourseListManager)

protected:
	CCourseListManager();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CCourseListManager();

public:
	enum { IDD = IDD_COURSELISTMANAGER };
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
	CString m_class;
	CString m_teacher;
	CString m_weekday;
	CString m_dayhour;
	CString m_building;
	CString m_room;
	CListCtrl m_course_list;
/***********************by jiangxin***********************/
private:
	//���öԻ�����������
	CFont Font;
/***********************by jiangxin***********************/
public:
	virtual void OnInitialUpdate();
	void initial(void);
	void settext(int index);
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonDel();
	afx_msg void OnBnClickedButtonChange();
	afx_msg void OnBnClickedButtonFresh();
	afx_msg void OnNMClickListCourseList(NMHDR *pNMHDR, LRESULT *pResult);
	CComboBox m_C_weekday;
	afx_msg void OnDestroy();
};


