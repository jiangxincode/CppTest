
// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once

/***********************by jiangxin***********************/
// ��Ӻ�ſ��ԺϷ�������CMYChildFrame *�͵ı���
#include "MyChildFrame.h"
/***********************by jiangxin***********************/

class CMainFrame : public CMDIFrameWndEx
{
	DECLARE_DYNAMIC(CMainFrame)

public:CMainFrame();

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnWindowManager();
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

/***********************by jiangxin***********************/
//����Ӵ���ָ���������¼�˵��Ƿ���õ�BOOL����
public:
	//ָ���޸�������ϵͳ
	CMyChildFrame *m_pUserChange;
	//ָ��ѧ��ѧ��������ϵͳ
	CMyChildFrame *m_pStudentInfo;
	//ָ���ʦ��Ϣ������ϵͳ
	CMyChildFrame *m_pTeacherInfo;
	//ָ����Ϣ������ϵͳ
	CMyChildFrame *m_pInfoManager;
	//ָ��ѡ����ϵͳ
	CMyChildFrame *m_pChoiceCourse;
	//ָ��ɾ����ѡ�γ���ϵͳ
	CMyChildFrame *m_pDelCourse;
	//ָ��α������ϵͳ
	CMyChildFrame *m_pCourseList;
	//ָ��ѧ���γ̳ɼ���ϵͳ
	CMyChildFrame *m_pCourseScore;
	//ָ���ʦ�γ̳ɼ���ϵͳ
	CMyChildFrame *m_pTeacherScore;
	//ָ��γ���Ϣ��ϵͳ
	CMyChildFrame *m_pCourseInfoManager;
	//ָ��α���Ϣ��ϵͳ
	CMyChildFrame *m_pCourseListManager;

	//��¼��½״̬
	BOOL m_bLogin;
	//��¼�޸�����˵��Ƿ����
	BOOL m_bItemUserChange;
	//��¼ѧ������˵��Ƿ����
	BOOL m_bItemStudentInfo;
	//��¼��ʦ��Ϣ�˵��Ƿ����
	BOOL m_bItemTeacherInfo;
	//��¼��Ϣ����˵��Ƿ����
	BOOL m_bItemInfoManager;
	//��¼ѡ�β˵��Ƿ����
	BOOL m_bItemChoiceCourse;
	//��¼ɾ����ѡ�γ̲˵��Ƿ����
	BOOL m_bItemDelCourse;
	//��¼��ѡ�οα�˵��Ƿ����
	BOOL m_bItemCourseList;
	//��¼ѧ���γ̳ɼ��˵��Ƿ����
	BOOL m_bItemCourseScore;
	//��¼��ʦ�γ̳ɼ��˵��Ƿ����
	BOOL m_bItemTeacherScore;
	//��¼�γ���Ϣ�˵��Ƿ����
	BOOL m_bItemCourseInfoManager;
	//��¼�α���Ϣ�˵��Ƿ����
	BOOL m_bItemCourseListManager;
/***********************by jiangxin***********************/
	afx_msg void OnUpdateUserChange(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStudentInfo(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTeacherInfo(CCmdUI *pCmdUI);
	afx_msg void OnUpdateInfoManager(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSystemConnect(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSystemDisconnect(CCmdUI *pCmdUI);
	afx_msg void OnUpdateChoiceCourse(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDelCourse(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCourseList(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCourseinfoManager(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCourselistManager(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCourseScore(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTeacherScore(CCmdUI *pCmdUI);
	afx_msg void OnSystemConnect();
	afx_msg void OnSystemDisconnect();
	afx_msg void OnUserChange();
	afx_msg void OnStudentInfo();
	afx_msg void OnTeacherInfo();
	afx_msg void OnInfoManager();
	afx_msg void OnChoiceCourse();
	afx_msg void OnDelCourse();
	afx_msg void OnCourseList();
	afx_msg void OnCourseScore();
	afx_msg void OnTeacherScore();
	afx_msg void OnCourseinfoManager();
	afx_msg void OnCourselistManager();
};