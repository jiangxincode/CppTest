
// MainFrm.cpp : CMainFrame ���ʵ��
//
#include "stdafx.h"
#include "ODBC.h"

#include "MainFrm.h"

/***********************by jiangxin***********************/
#include "LoginDlg.h"
#include "UserChange.h"
#include "StudentInfo.h"
#include "TeacherInfo.h"
#include "InfoManager.h"
#include "ChoiceCourse.h"
#include "DelCourse.h"
#include "CourseList.h"
#include "CourseScore.h"
#include "TeacherScore.h"
#include "CourseInfoManager.h"
#include "CourseListManager.h"
/***********************by jiangxin***********************/

/***********************by jiangxin***********************/
//�ⲿ������������
// CDatebase�ͱ����������������ݿ�
extern CDatabase m_database;
// ��½����ϵͳ�е�ΨһIDֵ
extern CString m_ID;
//��½�û�������
extern int m_type;
/***********************by jiangxin***********************/

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWndEx)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_WINDOW_MANAGER, &CMainFrame::OnWindowManager)
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
	ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_UPDATE_COMMAND_UI(ID_USER_CHANGE, &CMainFrame::OnUpdateUserChange)
	ON_UPDATE_COMMAND_UI(ID_STUDENT_INFO, &CMainFrame::OnUpdateStudentInfo)
	ON_UPDATE_COMMAND_UI(ID_TEACHER_INFO, &CMainFrame::OnUpdateTeacherInfo)
	ON_UPDATE_COMMAND_UI(ID_INFO_MANAGER, &CMainFrame::OnUpdateInfoManager)
	ON_UPDATE_COMMAND_UI(ID_SYSTEM_CONNECT, &CMainFrame::OnUpdateSystemConnect)
	ON_UPDATE_COMMAND_UI(ID_SYSTEM_DISCONNECT, &CMainFrame::OnUpdateSystemDisconnect)
	ON_UPDATE_COMMAND_UI(ID_CHOICE_COURSE, &CMainFrame::OnUpdateChoiceCourse)
	ON_UPDATE_COMMAND_UI(ID_DEL_COURSE, &CMainFrame::OnUpdateDelCourse)
	ON_UPDATE_COMMAND_UI(ID_COURSE_LIST, &CMainFrame::OnUpdateCourseList)
	ON_UPDATE_COMMAND_UI(ID_COURSEINFO_MANAGER, &CMainFrame::OnUpdateCourseinfoManager)
	ON_UPDATE_COMMAND_UI(ID_COURSELIST_MANAGER, &CMainFrame::OnUpdateCourselistManager)
	ON_UPDATE_COMMAND_UI(ID_COURSE_SCORE, &CMainFrame::OnUpdateCourseScore)
	ON_UPDATE_COMMAND_UI(ID_TEACHER_SCORE, &CMainFrame::OnUpdateTeacherScore)
	ON_COMMAND(ID_SYSTEM_CONNECT, &CMainFrame::OnSystemConnect)
	ON_COMMAND(ID_SYSTEM_DISCONNECT, &CMainFrame::OnSystemDisconnect)
	ON_COMMAND(ID_USER_CHANGE, &CMainFrame::OnUserChange)
	ON_COMMAND(ID_STUDENT_INFO, &CMainFrame::OnStudentInfo)
	ON_COMMAND(ID_TEACHER_INFO, &CMainFrame::OnTeacherInfo)
	ON_COMMAND(ID_INFO_MANAGER, &CMainFrame::OnInfoManager)
	ON_COMMAND(ID_CHOICE_COURSE, &CMainFrame::OnChoiceCourse)
	ON_COMMAND(ID_DEL_COURSE, &CMainFrame::OnDelCourse)
	ON_COMMAND(ID_COURSE_LIST, &CMainFrame::OnCourseList)
	ON_COMMAND(ID_COURSE_SCORE, &CMainFrame::OnCourseScore)
	ON_COMMAND(ID_TEACHER_SCORE, &CMainFrame::OnTeacherScore)
	ON_COMMAND(ID_COURSEINFO_MANAGER, &CMainFrame::OnCourseinfoManager)
	ON_COMMAND(ID_COURSELIST_MANAGER, &CMainFrame::OnCourselistManager)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
	/***********************by jiangxin***********************/
	//��Ĭ��ֵΪδ��¼
	m_bLogin = FALSE;
	//���ø��˵���ť�Բ�����
	m_bItemUserChange = FALSE;
	m_bItemStudentInfo = FALSE;
	m_bItemTeacherInfo = FALSE;
	m_bItemInfoManager = FALSE;
	m_bItemChoiceCourse = FALSE;
	m_bItemDelCourse = FALSE;
	m_bItemCourseList = FALSE;
	m_bItemCourseScore = FALSE;
	m_bItemTeacherScore = FALSE;
	m_bItemCourseInfoManager = FALSE;
	m_bItemCourseListManager = FALSE;

	//��ʼ����ָ��Ϊ��
	m_pUserChange = NULL;
	m_pStudentInfo = NULL;
	m_pTeacherInfo = NULL;
	m_pInfoManager = NULL;
	m_pChoiceCourse = NULL;
	m_pDelCourse = NULL;
	m_pCourseList = NULL;
	m_pCourseScore = NULL;
	m_pTeacherScore = NULL;
	m_pCourseInfoManager = NULL;
	m_pCourseListManager = NULL;
/***********************by jiangxin***********************/
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_VS_2008);
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;
/***********************by jiangxin***********************/
	//�����ʾ����
	ShowWindow(SW_SHOWMAXIMIZED);
/***********************by jiangxin***********************/
	BOOL bNameValid;
	// ���ڳ־�ֵ�����Ӿ�����������ʽ
	OnApplicationLook(theApp.m_nAppLook);

	CMDITabInfo mdiTabParams;
	mdiTabParams.m_style = CMFCTabCtrl::STYLE_3D_ONENOTE; // ����������ʽ...
	mdiTabParams.m_bActiveTabCloseButton = TRUE;      // ����Ϊ FALSE �Ὣ�رհ�ť������ѡ�������Ҳ�
	mdiTabParams.m_bTabIcons = FALSE;    // ����Ϊ TRUE ���� MDI ѡ��������ĵ�ͼ��
	mdiTabParams.m_bAutoColor = TRUE;    // ����Ϊ FALSE ������ MDI ѡ����Զ���ɫ
	mdiTabParams.m_bDocumentMenu = TRUE; // ��ѡ�������ұ�Ե�����ĵ��˵�
	EnableMDITabbedGroups(TRUE, mdiTabParams);

	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("δ�ܴ����˵���\n");
		return -1;      // δ�ܴ���
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	// ��ֹ�˵����ڼ���ʱ��ý���
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_MAINFRAME : IDR_MAINFRAME))
	{
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}

	CString strToolBarName;
	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	ASSERT(bNameValid);
	m_wndToolBar.SetWindowText(strToolBarName);

	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);
	m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

	// �����û�����Ĺ���������:
	InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: �������ϣ���������Ͳ˵�����ͣ������ɾ��������
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);
	DockPane(&m_wndToolBar);


	// ���� Visual Studio 2005 ��ʽͣ��������Ϊ
	CDockingManager::SetDockingMode(DT_SMART);
	// ���� Visual Studio 2005 ��ʽͣ�������Զ�������Ϊ
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// ������ǿ�Ĵ��ڹ���Ի���
	EnableWindowsDialog(ID_WINDOW_MANAGER, ID_WINDOW_MANAGER, TRUE);

	// ���ù�������ͣ�����ڲ˵��滻
	EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

	// ���ÿ���(��ס Alt �϶�)�������Զ���
	CMFCToolBar::EnableQuickCustomization();

	if (CMFCToolBar::GetUserImages() == NULL)
	{
		// �����û�����Ĺ�����ͼ��
		if (m_UserImages.Load(_T(".\\UserImages.bmp")))
		{
			CMFCToolBar::SetUserImages(&m_UserImages);
		}
	}

	// ���ò˵����Ի�(���ʹ�õ�����)
	// TODO: �������Լ��Ļ������ȷ��ÿ�������˵�������һ���������
	CList<UINT, UINT> lstBasicCommands;

	lstBasicCommands.AddTail(ID_FILE_NEW);
	lstBasicCommands.AddTail(ID_APP_EXIT);
	lstBasicCommands.AddTail(ID_EDIT_CUT);
	lstBasicCommands.AddTail(ID_EDIT_PASTE);
	lstBasicCommands.AddTail(ID_EDIT_UNDO);
	lstBasicCommands.AddTail(ID_APP_ABOUT);
	lstBasicCommands.AddTail(ID_VIEW_STATUS_BAR);
	lstBasicCommands.AddTail(ID_VIEW_TOOLBAR);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2003);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_VS_2005);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLUE);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_SILVER);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLACK);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_AQUA);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_WINDOWS_7);

	CMFCToolBar::SetBasicCommands(lstBasicCommands);

	// ���ĵ�����Ӧ�ó��������ڴ��ڱ������ϵ�˳����н�������
	// ���Ľ��������Ŀ����ԣ���Ϊ��ʾ���ĵ�����������ͼ��
	ModifyStyle(0, FWS_PREFIXTITLE);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return TRUE;
}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ��Ϣ�������

void CMainFrame::OnWindowManager()
{
	ShowWindowsDialog();
}

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* ɨ��˵�*/);
	pDlgCust->EnableUserDefinedToolbars();
	pDlgCust->Create();
}

LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres = CMDIFrameWndEx::OnToolbarCreateNew(wp,lp);
	if (lres == 0)
	{
		return 0;
	}

	CMFCToolBar* pUserToolbar = (CMFCToolBar*)lres;
	ASSERT_VALID(pUserToolbar);

	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	return lres;
}

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}

BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	// ���ཫִ�������Ĺ���

	if (!CMDIFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}


	// Ϊ�����û������������Զ��尴ť
	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	for (int i = 0; i < iMaxUserToolbars; i ++)
	{
		CMFCToolBar* pUserToolbar = GetUserToolBarByIndex(i);
		if (pUserToolbar != NULL)
		{
			pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
		}
	}

	return TRUE;
}


/***********************by jiangxin***********************/
void CMainFrame::OnUpdateUserChange(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(m_bItemUserChange);
}
/***********************by jiangxin***********************/

/***********************by jiangxin***********************/
void CMainFrame::OnUpdateStudentInfo(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(m_bItemStudentInfo);
}
/***********************by jiangxin***********************/

/***********************by jiangxin***********************/
void CMainFrame::OnUpdateTeacherInfo(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(m_bItemTeacherInfo);
}
/***********************by jiangxin***********************/

/***********************by jiangxin***********************/
void CMainFrame::OnUpdateInfoManager(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(m_bItemInfoManager);
}
/***********************by jiangxin***********************/

/***********************by jiangxin***********************/
void CMainFrame::OnUpdateSystemConnect(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(!m_bLogin);
}
/***********************by jiangxin***********************/

/***********************by jiangxin***********************/
void CMainFrame::OnUpdateSystemDisconnect(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(m_bLogin);
}
/***********************by jiangxin***********************/

/***********************by jiangxin***********************/
void CMainFrame::OnUpdateChoiceCourse(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(m_bItemChoiceCourse);
}
/***********************by jiangxin***********************/

/***********************by jiangxin***********************/
void CMainFrame::OnUpdateDelCourse(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(m_bItemDelCourse);
}
/***********************by jiangxin***********************/

/***********************by jiangxin***********************/
void CMainFrame::OnUpdateCourseList(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(m_bItemCourseList);
}
/***********************by jiangxin***********************/

/***********************by jiangxin***********************/
void CMainFrame::OnUpdateCourseinfoManager(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(m_bItemCourseInfoManager);
}
/***********************by jiangxin***********************/

/***********************by jiangxin***********************/
void CMainFrame::OnUpdateCourselistManager(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(m_bItemCourseListManager);
}
/***********************by jiangxin***********************/

/***********************by jiangxin***********************/
void CMainFrame::OnUpdateCourseScore(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(m_bItemCourseScore);
}
/***********************by jiangxin***********************/

/***********************by jiangxin***********************/
void CMainFrame::OnUpdateTeacherScore(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(m_bItemTeacherScore);
}
/***********************by jiangxin***********************/

/***********************by jiangxin***********************/
void CMainFrame::OnSystemConnect()
{
	// TODO: �ڴ���������������
	CLoginDlg dlg;
	if(dlg.DoModal()==IDOK)
	{
		//ѧ��
		if(m_type==1)
		{
			m_bLogin = TRUE;
			m_bItemUserChange = TRUE;
			m_bItemStudentInfo = TRUE;
			m_bItemChoiceCourse = TRUE;
			m_bItemDelCourse = TRUE;
			m_bItemCourseList = TRUE;
			m_bItemCourseScore = TRUE;
		}
		//��ʦ
		if(m_type==2)
		{
			m_bLogin = TRUE;
			m_bItemUserChange = TRUE;
			m_bItemTeacherInfo = TRUE;
			m_bItemChoiceCourse = TRUE;
			m_bItemDelCourse = TRUE;
			m_bItemCourseList = TRUE;
			m_bItemTeacherScore = TRUE;
		}
		//����Ա
		if(m_type==3)
		{
			m_bLogin = TRUE;
			m_bItemUserChange = TRUE;
			m_bItemInfoManager = TRUE;
			m_bItemCourseInfoManager = TRUE;
			m_bItemCourseListManager = TRUE;
		}
	}

}
/***********************by jiangxin***********************/

/***********************by jiangxin***********************/
void CMainFrame::OnSystemDisconnect()
{
	// TODO: �ڴ���������������
	// �ر������������еĴ���
	if(m_pUserChange)
		m_pUserChange->DestroyWindow();
	if(m_pTeacherInfo)
		m_pTeacherInfo->DestroyWindow();
	if(m_pStudentInfo)
		m_pStudentInfo->DestroyWindow();
	if(m_pInfoManager)
		m_pInfoManager->DestroyWindow();
	if(m_pChoiceCourse)
		m_pChoiceCourse->DestroyWindow();
	if(m_pDelCourse)
		m_pDelCourse->DestroyWindow();
	if(m_pCourseList)
		m_pCourseList->DestroyWindow();
	if(m_pCourseScore)
		m_pCourseScore->DestroyWindow();
	if(m_pTeacherScore)
		m_pTeacherScore->DestroyWindow();
	if(m_pCourseInfoManager)
		m_pCourseInfoManager->DestroyWindow();
	if(m_pTeacherScore)
		m_pCourseListManager->DestroyWindow();

	//�������ø����˵���
	m_bLogin = FALSE;
	m_bItemUserChange = FALSE;
	m_bItemStudentInfo = FALSE;
	m_bItemTeacherInfo = FALSE;
	m_bItemInfoManager = FALSE;
	m_bItemChoiceCourse = FALSE;
	m_bItemDelCourse = FALSE;
	m_bItemCourseScore = FALSE;
	m_bItemCourseList = FALSE;
	m_bItemTeacherScore = FALSE;
	m_bItemCourseInfoManager = FALSE;
	m_bItemCourseListManager = FALSE;
	m_type=0;

}
/***********************by jiangxin***********************/

/* ����Ϊ��������ģ��Ĵ�����롣������ĳһ����ģ��ʱ���ͻᵯ����Ӧ����ͼ�Ի���
Ȼ����øò˵��������������һ������ͼ */

/***********************by jiangxin***********************/
void CMainFrame::OnUserChange()
{
	// TODO: �ڴ���������������
	// �������޸����롱�ӿ�ܺ���ͼ
	m_pUserChange=new CMyChildFrame;
	CCreateContext context;
	context.m_pNewViewClass=RUNTIME_CLASS(CUserChange);
	if(!m_pUserChange->LoadFrame(IDR_MAINFRAME,WS_OVERLAPPEDWINDOW|FWS_PREFIXTITLE,this,&context)) return;
	m_pUserChange->InitialUpdateFrame(NULL,TRUE);
	// ��ֹ�ٴδ򿪡��޸����롱�ӿ�ܺ���ͼ
	m_bItemUserChange=FALSE;
}
/***********************by jiangxin***********************/

/***********************by jiangxin***********************/
void CMainFrame::OnStudentInfo()
{
	// TODO: �ڴ���������������
	// ������ѧ��������Ϣ���ӿ�ܺ���ͼ
	m_pStudentInfo=new CMyChildFrame;
	CCreateContext context;
	context.m_pNewViewClass=RUNTIME_CLASS(CStudentInfo);
	if(!m_pStudentInfo->LoadFrame(IDR_MAINFRAME,WS_OVERLAPPEDWINDOW|FWS_PREFIXTITLE,this,&context)) return;
	m_pStudentInfo->InitialUpdateFrame(NULL,TRUE);
	// ��ֹ�ٴδ򿪡�ѧ��������Ϣ���ӿ�ܺ���ͼ
	m_bItemStudentInfo=FALSE;
}
/***********************by jiangxin***********************/

/***********************by jiangxin***********************/
void CMainFrame::OnTeacherInfo()
{
	// TODO: �ڴ���������������
	// ��������ʦ������Ϣ���ӿ�ܺ���ͼ
	m_pTeacherInfo=new CMyChildFrame;
	CCreateContext context;
	context.m_pNewViewClass=RUNTIME_CLASS(CTeacherInfo);
	if(!m_pTeacherInfo->LoadFrame(IDR_MAINFRAME,WS_OVERLAPPEDWINDOW|FWS_PREFIXTITLE,this,&context)) return;
	m_pTeacherInfo->InitialUpdateFrame(NULL,TRUE);
	// ��ֹ�ٴδ򿪡���ʦ������Ϣ���ӿ�ܺ���ͼ
	m_bItemTeacherInfo=FALSE;
}
/***********************by jiangxin***********************/

/***********************by jiangxin***********************/
void CMainFrame::OnInfoManager()
{
	// TODO: �ڴ���������������
	// ���������������Ϣ���ӿ�ܺ���ͼ
	m_pInfoManager=new CMyChildFrame;
	CCreateContext context;
	context.m_pNewViewClass=RUNTIME_CLASS(CInfoManager);
	if(!m_pInfoManager->LoadFrame(IDR_MAINFRAME,WS_OVERLAPPEDWINDOW|FWS_PREFIXTITLE,this,&context)) return;
	m_pInfoManager->InitialUpdateFrame(NULL,TRUE);
	// ��ֹ�ٴδ򿪡����������Ϣ���ӿ�ܺ���ͼ
	m_bItemInfoManager=FALSE;
}
/***********************by jiangxin***********************/

/***********************by jiangxin***********************/
void CMainFrame::OnChoiceCourse()
{
	// TODO: �ڴ���������������
	// ������ѡ�Ρ��ӿ�ܺ���ͼ
	m_pChoiceCourse=new CMyChildFrame;
	CCreateContext context;
	context.m_pNewViewClass=RUNTIME_CLASS(CChoiceCourse);
	if(!m_pChoiceCourse->LoadFrame(IDR_MAINFRAME,WS_OVERLAPPEDWINDOW|FWS_PREFIXTITLE,this,&context)) return;
	m_pChoiceCourse->InitialUpdateFrame(NULL,TRUE);
	// ��ֹ�ٴδ򿪡�ѡ�Ρ��ӿ�ܺ���ͼ
	m_bItemChoiceCourse=FALSE;
}
/***********************by jiangxin***********************/

/***********************by jiangxin***********************/
void CMainFrame::OnDelCourse()
{
	// TODO: �ڴ���������������
	// ������ɾ���γ̡��ӿ�ܺ���ͼ
	m_pDelCourse=new CMyChildFrame;
	CCreateContext context;
	context.m_pNewViewClass=RUNTIME_CLASS(CDelCourse);
	if(!m_pDelCourse->LoadFrame(IDR_MAINFRAME,WS_OVERLAPPEDWINDOW|FWS_PREFIXTITLE,this,&context)) return;
	m_pDelCourse->InitialUpdateFrame(NULL,TRUE);
	// ��ֹ�ٴδ򿪡�ɾ���γ̡��ӿ�ܺ���ͼ
	m_bItemDelCourse=FALSE;
}
/***********************by jiangxin***********************/

/***********************by jiangxin***********************/
void CMainFrame::OnCourseList()
{
	// TODO: �ڴ���������������
	// �������α��ӿ�ܺ���ͼ
	m_pCourseList=new CMyChildFrame;
	CCreateContext context;
	context.m_pNewViewClass=RUNTIME_CLASS(CCourseList);
	if(!m_pCourseList->LoadFrame(IDR_MAINFRAME,WS_OVERLAPPEDWINDOW|FWS_PREFIXTITLE,this,&context)) return;
	m_pCourseList->InitialUpdateFrame(NULL,TRUE);
	// ��ֹ�ٴδ򿪡��α��ӿ�ܺ���ͼ
	m_bItemCourseList=FALSE;
}
/***********************by jiangxin***********************/

/***********************by jiangxin***********************/
void CMainFrame::OnCourseScore()
{
	// TODO: �ڴ���������������
	// �������γ̳ɼ����ӿ�ܺ���ͼ
	m_pCourseScore=new CMyChildFrame;
	CCreateContext context;
	context.m_pNewViewClass=RUNTIME_CLASS(CCourseScore);
	if(!m_pCourseScore->LoadFrame(IDR_MAINFRAME,WS_OVERLAPPEDWINDOW|FWS_PREFIXTITLE,this,&context)) return;
	m_pCourseScore->InitialUpdateFrame(NULL,TRUE);
	// ��ֹ�ٴδ򿪡��γ̳ɼ����ӿ�ܺ���ͼ
	m_bItemCourseScore=FALSE;
}
/***********************by jiangxin***********************/

/***********************by jiangxin***********************/
void CMainFrame::OnTeacherScore()
{
	// TODO: �ڴ���������������
	// ��������ʦ�γ̳ɼ����ӿ�ܺ���ͼ
	m_pTeacherScore=new CMyChildFrame;
	CCreateContext context;
	context.m_pNewViewClass=RUNTIME_CLASS(CTeacherScore);
	if(!m_pTeacherScore->LoadFrame(IDR_MAINFRAME,WS_OVERLAPPEDWINDOW|FWS_PREFIXTITLE,this,&context)) return;
	m_pTeacherScore->InitialUpdateFrame(NULL,TRUE);
	// ��ֹ�ٴδ򿪡���ʦ�γ̳ɼ����ӿ�ܺ���ͼ
	m_bItemTeacherScore=FALSE;
}
/***********************by jiangxin***********************/

/***********************by jiangxin***********************/
void CMainFrame::OnCourseinfoManager()
{
	// TODO: �ڴ���������������
	// �������γ���Ϣ�����ӿ�ܺ���ͼ
	m_pCourseInfoManager=new CMyChildFrame;
	CCreateContext context;
	context.m_pNewViewClass=RUNTIME_CLASS(CCourseInfoManager);
	if(!m_pCourseInfoManager->LoadFrame(IDR_MAINFRAME,WS_OVERLAPPEDWINDOW|FWS_PREFIXTITLE,this,&context)) return;
	m_pCourseInfoManager->InitialUpdateFrame(NULL,TRUE);
	// ��ֹ�ٴδ򿪡��γ���Ϣ�����ӿ�ܺ���ͼ
	m_bItemCourseInfoManager=FALSE;
}
/***********************by jiangxin***********************/

/***********************by jiangxin***********************/
void CMainFrame::OnCourselistManager()
{
	// TODO: �ڴ���������������
	// �������α���Ϣ�����ӿ�ܺ���ͼ
	m_pCourseListManager=new CMyChildFrame;
	CCreateContext context;
	context.m_pNewViewClass=RUNTIME_CLASS(CCourseListManager);
	if(!m_pCourseListManager->LoadFrame(IDR_MAINFRAME,WS_OVERLAPPEDWINDOW|FWS_PREFIXTITLE,this,&context)) return;
	m_pCourseListManager->InitialUpdateFrame(NULL,TRUE);
	// ��ֹ�ٴδ򿪡��α���Ϣ�����ӿ�ܺ���ͼ
	m_bItemCourseListManager=FALSE;
}
/***********************by jiangxin***********************/