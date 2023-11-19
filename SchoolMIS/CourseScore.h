#pragma once
#include "afxcmn.h"



// CCourseScore ������ͼ

class CCourseScore : public CFormView
{
	DECLARE_DYNCREATE(CCourseScore)

protected:
	CCourseScore();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CCourseScore();

public:
	enum { IDD = IDD_COURSESCORE };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
/***********************by jiangxin***********************/
private:
	//���öԻ�����������
	CFont Font;
/***********************by jiangxin***********************/

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	CString m_stuID;
	CString m_courseID;
	CString m_course_name;
	CString m_score;
	CListCtrl m_course;
	void initial(void);
	afx_msg void OnNMClickListCourseScore(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDestroy();
};


