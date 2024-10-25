
// MainFrm.h : CMainFrame 类的接口
//

#pragma once

/***********************by jiangxin***********************/
// 添加后才可以合法地声明CMYChildFrame *型的变量
#include "MyChildFrame.h"
/***********************by jiangxin***********************/

class CMainFrame : public CMDIFrameWndEx
{
	DECLARE_DYNAMIC(CMainFrame)

public:CMainFrame();

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnWindowManager();
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

/***********************by jiangxin***********************/
//添加子窗口指针变量及记录菜单是否可用的BOOL变量
public:
	//指向修改密码子系统
	CMyChildFrame *m_pUserChange;
	//指向学生学籍管理子系统
	CMyChildFrame *m_pStudentInfo;
	//指向教师信息管理子系统
	CMyChildFrame *m_pTeacherInfo;
	//指向信息管理子系统
	CMyChildFrame *m_pInfoManager;
	//指向选课子系统
	CMyChildFrame *m_pChoiceCourse;
	//指向删除已选课程子系统
	CMyChildFrame *m_pDelCourse;
	//指向课表管理子系统
	CMyChildFrame *m_pCourseList;
	//指向学生课程成绩子系统
	CMyChildFrame *m_pCourseScore;
	//指向教师课程成绩子系统
	CMyChildFrame *m_pTeacherScore;
	//指向课程信息子系统
	CMyChildFrame *m_pCourseInfoManager;
	//指向课表信息子系统
	CMyChildFrame *m_pCourseListManager;

	//记录登陆状态
	BOOL m_bLogin;
	//记录修改密码菜单是否可用
	BOOL m_bItemUserChange;
	//记录学生管理菜单是否可用
	BOOL m_bItemStudentInfo;
	//记录教师信息菜单是否可用
	BOOL m_bItemTeacherInfo;
	//记录信息管理菜单是否可用
	BOOL m_bItemInfoManager;
	//记录选课菜单是否可用
	BOOL m_bItemChoiceCourse;
	//记录删除已选课程菜单是否可用
	BOOL m_bItemDelCourse;
	//记录已选课课表菜单是否可用
	BOOL m_bItemCourseList;
	//记录学生课程成绩菜单是否可用
	BOOL m_bItemCourseScore;
	//记录教师课程成绩菜单是否可用
	BOOL m_bItemTeacherScore;
	//记录课程信息菜单是否可用
	BOOL m_bItemCourseInfoManager;
	//记录课表信息菜单是否可用
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