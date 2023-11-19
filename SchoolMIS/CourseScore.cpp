// CourseScore.cpp : 实现文件
//

#include "stdafx.h"
#include "ODBC.h"
#include "CourseScore.h"
/***********************by jiangxin***********************/
#include "MainFrm.h"
extern CDatabase m_database;
extern CString m_ID;
extern int m_type;
/***********************by jiangxin***********************/


// CCourseScore

IMPLEMENT_DYNCREATE(CCourseScore, CFormView)

CCourseScore::CCourseScore()
	: CFormView(CCourseScore::IDD)
	, m_stuID(_T(""))
	, m_courseID(_T(""))
	, m_course_name(_T(""))
	, m_score(_T(""))
{

}

CCourseScore::~CCourseScore()
{
}

void CCourseScore::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_stuID);
	DDX_Text(pDX, IDC_EDIT2, m_courseID);
	DDX_Text(pDX, IDC_EDIT3, m_course_name);
	DDX_Text(pDX, IDC_EDIT4, m_score);
	DDX_Control(pDX, IDC_LIST_COURSE_SCORE, m_course);
}

BEGIN_MESSAGE_MAP(CCourseScore, CFormView)
	ON_NOTIFY(NM_CLICK, IDC_LIST_COURSE_SCORE, &CCourseScore::OnNMClickListCourseScore)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CCourseScore 诊断

#ifdef _DEBUG
void CCourseScore::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CCourseScore::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCourseScore 消息处理程序


void CCourseScore::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	// 自动调整窗口
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit(FALSE);
	// 设置标题
	GetParentFrame()->SetWindowText(L"学生成绩管理子系统");
	CenterWindow();
	// 设置字体
	LOGFONT LogFont;
	GetFont()->GetLogFont(&LogFont);
	LogFont.lfHeight+=LogFont.lfHeight/2;
	LogFont.lfWidth+=LogFont.lfWidth/2;
	Font.CreateFontIndirect(&LogFont);
	GetDlgItem(IDC_STATIC_COURSE_SCORE)->SetFont(&Font);
	// 初始化列表控件
	m_course.InsertColumn(0,L"课程编号");
	m_course.InsertColumn(1,L"课程名称");
	m_course.InsertColumn(2,L"上课时间");
	m_course.InsertColumn(3,L"开课日期");
	m_course.InsertColumn(4,L"结课日期");
	m_course.InsertColumn(5,L"课程学分");
	m_course.InsertColumn(6,L"授课教师");
	m_course.InsertColumn(7,L"选课要求");
	m_course.InsertColumn(8,L"课程简介");

	RECT rect;
	m_course.GetWindowRect(&rect);
	int width=rect.right-rect.left;
	m_course.SetColumnWidth(0,width/7);
	m_course.SetColumnWidth(1,width/7);
	m_course.SetColumnWidth(2,width/7);
	m_course.SetColumnWidth(3,width/7);
	m_course.SetColumnWidth(4,width/7);
	m_course.SetColumnWidth(5,width/7);
	m_course.SetColumnWidth(6,width/7);
	m_course.SetColumnWidth(7,width/7);
	m_course.SetColumnWidth(8,width/7);

	m_course.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	initial();
}


void CCourseScore::initial(void)
{
	CDBVariant varValue;
	CString str,buf;
	int i=0;
	m_course.DeleteAllItems();
	CRecordset m_recordset(&m_database);
	CString strSQL;
	strSQL.Format(L"select * from COURSE where COURSE_ID in (select COURSE_ID from COURSE_SCORE where STU_ID='%s')",m_ID);
	m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL);
	if(m_recordset.GetRecordCount()!=0)
		m_recordset.MoveFirst();
	while(!m_recordset.IsEOF())
	{
		int temp=0;
		// 对字符串进行处理
		m_recordset.GetFieldValue(temp,str);
		m_course.InsertItem(i,str);

		m_recordset.GetFieldValue(1,str);
		m_course.SetItemText(i,1,str);
		
		m_recordset.GetFieldValue(2,str);
		m_course.SetItemText(i,2,str);

		// 对日期类型进行处理
		m_recordset.GetFieldValue(3,varValue);

		buf.Format(L"%d-%d-%d",varValue.m_pdate->year,varValue.m_pdate->month,varValue.m_pdate->day);
		m_course.SetItemText(i,3,buf);

		m_recordset.GetFieldValue(4,varValue);

		buf.Format(L"%d-%d-%d",varValue.m_pdate->year,varValue.m_pdate->month,varValue.m_pdate->day);
		m_course.SetItemText(i,4,buf);

		// 对整形数据进行处理
		m_recordset.GetFieldValue(5,varValue);
		buf.Format(L"%d",varValue.m_iVal);
		m_course.SetItemText(i,5,buf);

		// 对字符串进行处理
		m_recordset.GetFieldValue(6,str);
		m_course.SetItemText(i,6,str);

		m_recordset.GetFieldValue(7,str);
		m_course.SetItemText(i,7,str);

		m_recordset.GetFieldValue(8,str);
		m_course.SetItemText(i,8,str);

		m_recordset.MoveNext();
		i++;
	}
	m_recordset.Close();
	UpdateData(FALSE);
}


void CCourseScore::OnNMClickListCourseScore(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	// 获得选中的课程信息标志
	int i=m_course.GetSelectionMark();
	m_courseID=m_course.GetItemText(i,0);
	CDBVariant varValue;
	CString buf;
	CRecordset m_recordset(&m_database);
	CString strSQl;
	// 查询所选课程成绩
	strSQl.Format(L"select * from COURSE_SCORE where STU_ID='%s' and COURSE_ID='%s'",m_ID,m_courseID);
	m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQl);
	int temp=0;
	m_recordset.GetFieldValue(temp,m_stuID);
	m_recordset.GetFieldValue(1,m_courseID);
	m_recordset.GetFieldValue(2,m_course_name);

	m_recordset.GetFieldValue(3,varValue);
	buf.Format(L"%d",varValue.m_iVal);
	m_score=buf;
	UpdateData(FALSE);
	*pResult = 0;
}


void CCourseScore::OnDestroy()
{
	CFormView::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	// 使菜单中‘基本信息管理’项再次可用
	((CMainFrame *)AfxGetMainWnd())->m_bItemCourseScore=TRUE;
	// 清空‘基本信息管理’窗口指针
	((CMainFrame *)AfxGetMainWnd())->m_pCourseScore=NULL;
}
