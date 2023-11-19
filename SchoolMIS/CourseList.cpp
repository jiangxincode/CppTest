// CourseList.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ODBC.h"
#include "CourseList.h"
/***********************by jiangxin***********************/
#include "MainFrm.h"
extern CDatabase m_database;
extern CString m_ID;
extern int m_type;
/***********************by jiangxin***********************/

// CCourseList

IMPLEMENT_DYNCREATE(CCourseList, CFormView)

CCourseList::CCourseList()
	: CFormView(CCourseList::IDD)
	, m_key(_T(""))
	, m_cost(_T(""))
	, m_courseID(_T(""))
	, m_course_name(_T(""))
	, m_class(_T(""))
	, m_teacher(_T(""))
	, m_dayhour(_T(""))
	, m_building(_T(""))
	, m_room(_T(""))
	, m_weekday(0)
{

}

CCourseList::~CCourseList()
{
}

void CCourseList::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO_KEYWORD, m_key);
	DDX_Text(pDX, IDC_EDIT_COST, m_cost);
	DDX_Text(pDX, IDC_EDIT_COURSE_ID, m_courseID);
	DDX_Text(pDX, IDC_EDIT3, m_course_name);
	DDX_Text(pDX, IDC_EDIT_CLASS_ID, m_class);
	DDX_Text(pDX, IDC_EDIT4, m_teacher);
	DDX_Text(pDX, IDC_EDIT_DAYHOUR, m_dayhour);
	DDX_Text(pDX, IDC_EDIT_BUILDING, m_building);
	DDX_Text(pDX, IDC_EDIT_ROOM, m_room);
	DDX_CBIndex(pDX, IDC_COMBO_WEEKDAY, m_weekday);
}

BEGIN_MESSAGE_MAP(CCourseList, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CCourseList::OnBnClickedButtonSearch)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CCourseList ���

#ifdef _DEBUG
void CCourseList::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CCourseList::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCourseList ��Ϣ�������


void CCourseList::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	// �Զ���������
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit(FALSE);
	// ���ñ���
	GetParentFrame()->SetWindowText(L"ɾ����ѡ�γ���ϵͳ");
	CenterWindow();
	// ��������
	LOGFONT LogFont;
	GetFont()->GetLogFont(&LogFont);
	LogFont.lfHeight+=LogFont.lfHeight/2;
	LogFont.lfWidth+=LogFont.lfWidth/2;
	Font.CreateFontIndirect(&LogFont);
	GetDlgItem(IDC_STATIC_COURSE_LIST)->SetFont(&Font);
}


void CCourseList::OnBnClickedButtonSearch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strSQL;
	CDBVariant varValue;
	UpdateData(TRUE);
	if(m_key.Compare(L"�γ̺�")==0)
		// �Կγ̺Ž��в���
		strSQL.Format(L"select * from COURSE_LIST where COURSE_ID='%s'",m_cost);
	else
		// �Կγ������в���
		strSQL.Format(L"select * from COURSE_LIST where COURSE_NAME='%s'",m_cost);
	CRecordset m_recordset(&m_database);
	m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL);
	if(m_recordset.GetRecordCount()==0)
	{
		MessageBox(L"�Բ���û��������Ҫ�Ľ������˶Ժ��������룡",L"�޴˽��");
	}
	else
	{
		int temp=0;
		m_recordset.GetFieldValue(temp,m_courseID);
		m_recordset.GetFieldValue(1,m_course_name);
		m_recordset.GetFieldValue(2,m_class);
		m_recordset.GetFieldValue(3,m_teacher);
		
		//���������ݽ��д���
		m_recordset.GetFieldValue(4,varValue);
		m_weekday=varValue.m_iVal-1;

		// ���ַ������д���
		m_recordset.GetFieldValue(5,m_dayhour);
		m_recordset.GetFieldValue(6,m_building);
		m_recordset.GetFieldValue(7,m_room);

		m_recordset.Close();
		UpdateData(FALSE);
	}
}


void CCourseList::OnDestroy()
{
	CFormView::OnDestroy();
	// TODO: �ڴ˴������Ϣ����������
	// ʹ�˵��С�������Ϣ�������ٴο���
	((CMainFrame *)AfxGetMainWnd())->m_bItemCourseList=TRUE;
	// ��ա�������Ϣ��������ָ��
	((CMainFrame *)AfxGetMainWnd())->m_pCourseList=NULL;
}
