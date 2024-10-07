// TeacherScore.cpp : 实现文件
//

#include "stdafx.h"
#include "SchoolMIS.h"
#include "TeacherScore.h"
/***********************by jiangxin***********************/
#include "MainFrm.h"
extern CDatabase m_database;
extern CString m_ID;
extern int m_type;
/***********************by jiangxin***********************/


// CTeacherScore

IMPLEMENT_DYNCREATE(CTeacherScore, CFormView)

CTeacherScore::CTeacherScore()
	: CFormView(CTeacherScore::IDD)
	, m_stuID(_T(""))
	, m_courseID(_T(""))
	, m_score(_T(""))
	, m_course_name(_T(""))
{

}

CTeacherScore::~CTeacherScore()
{
}

void CTeacherScore::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_stuID);
	DDX_Text(pDX, IDC_EDIT2, m_courseID);
	DDX_Text(pDX, IDC_EDIT3, m_score);
	DDX_Text(pDX, IDC_EDIT4, m_course_name);
	DDX_Control(pDX, IDC_LIST_STUDENT, m_student);
	DDX_Control(pDX, IDC_LIST_COURSE, m_course);
}

BEGIN_MESSAGE_MAP(CTeacherScore, CFormView)
	ON_NOTIFY(NM_CLICK, IDC_LIST_COURSE, &CTeacherScore::OnNMClickListCourse)
	ON_NOTIFY(NM_CLICK, IDC_LIST_STUDENT, &CTeacherScore::OnNMClickListStudent)
	ON_BN_CLICKED(IDC_BUTTON_SURE, &CTeacherScore::OnBnClickedButtonSure)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CTeacherScore::OnBnClickedButtonCancel)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CTeacherScore 诊断

#ifdef _DEBUG
void CTeacherScore::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CTeacherScore::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTeacherScore 消息处理程序


void CTeacherScore::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	// 自动调整窗口
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit(FALSE);
	// 设置标题
	GetParentFrame()->SetWindowText(L"成绩管理");
	CenterWindow();
	// 设置字体
	LOGFONT LogFont;
	GetFont()->GetLogFont(&LogFont);
	LogFont.lfHeight+=LogFont.lfHeight/2;
	LogFont.lfWidth+=LogFont.lfWidth/2;
	Font.CreateFontIndirect(&LogFont);
	GetDlgItem(IDC_STATIC_TEACHER_SCORE)->SetFont(&Font);
	// 初始化课程列表控件
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
	m_course.SetColumnWidth(0,width/9);
	m_course.SetColumnWidth(1,width/9);
	m_course.SetColumnWidth(2,width/9);
	m_course.SetColumnWidth(3,width/9);
	m_course.SetColumnWidth(4,width/9);
	m_course.SetColumnWidth(5,width/9);
	m_course.SetColumnWidth(6,width/9);
	m_course.SetColumnWidth(7,width/9);
	m_course.SetColumnWidth(8,width/9);
	m_course.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	// 初始化学生列表控件
	m_course.InsertColumn(0,L"学号");
	m_course.InsertColumn(1,L"课程名称");
	m_course.InsertColumn(2,L"课程编号");
	m_course.InsertColumn(3,L"分数");

	m_course.GetWindowRect(&rect);
	width=rect.right-rect.left;
	m_course.SetColumnWidth(0,width/4);
	m_course.SetColumnWidth(1,width/4);
	m_course.SetColumnWidth(2,width/4);
	m_course.SetColumnWidth(3,width/4);
	m_course.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	initial();
}


void CTeacherScore::initial(void)
{
	m_course.DeleteAllItems();
	CDBVariant varValue;
	CString strSQL;
	CString str;
	CString buf;
	int i=0;
	CRecordset m_recordset(&m_database);
	strSQL.Format(L"select TEA_NAME from TEACHER_INFO where TEA_ID='%s'",m_ID);
	m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL);
	m_recordset.GetFieldValue(L"TEA_NAME",str);
	m_recordset.Close();

	strSQL.Format(L"select * from COURSE where COURSE_TACHER='%s'",str);
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

	// 使i指向课程列表中的第一列
	i=0;
	// 从课程列表中选择对应信息填充到相应单元
	course_settext(0);

}


void CTeacherScore::course_settext(int index)
{
	m_courseID=m_course.GetItemText(index,0);
	m_course_name=m_course.GetItemText(index,1);

	m_student.DeleteAllItems();
	CDBVariant varValue;
	CString strSQL;
	CString str;
	CString buf;
	int i=0;
	CRecordset m_recordset(&m_database);
	strSQL.Format(L"select * from COURSE_SCORE where SCORE_ID='%s'",m_courseID);
	m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL);
	if(m_recordset.GetRecordCount()!=0)
		m_recordset.MoveFirst();
	int j=0;
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

		// 对整形数据进行处理
		m_recordset.GetFieldValue(3,varValue);
		buf.Format(L"%d",varValue.m_iVal);
		m_course.SetItemText(i,3,buf);

		j++;
		m_recordset.MoveNext();
	}
	m_recordset.Close();
	i=0;
	m_stuID=m_student.GetItemText(1,0);
	m_score=m_student.GetItemText(1,3);
	UpdateData(FALSE);
}


void CTeacherScore::OnNMClickListCourse(NMHDR *pNMHDR, LRESULT *pResult)
{

	// TODO: 在此添加控件通知处理程序代码
	int i=m_course.GetSelectionMark();
	// 调用显示函数进行显示
	course_settext(i);
	*pResult = 0;
}


void CTeacherScore::OnNMClickListStudent(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	int i=m_student.GetSelectionMark();
	m_stuID=m_student.GetItemText(1,0);
	m_score=m_student.GetItemText(1,3);
	UpdateData(FALSE);
	*pResult = 0;
}


void CTeacherScore::OnBnClickedButtonSure()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CRecordset m_recordset;
	if(m_score.GetLength()==0)
	{
		MessageBox(L"成绩不能为空！",L"请重新输入！");
	}
	else
	{
		int score=_ttoi(m_score);
		if(score>100||score<0)
			MessageBox(L"无效成绩！",L"请重新输入！");
		else
		{
			CString strSQL;
			strSQL.Format(L"update COURSE_SCORE set SCORE='%d' where STU_ID='%s' and COURSE_ID='%s'",score,m_stuID,m_courseID);
			m_database.ExecuteSQL(strSQL);
			MessageBox(L"成绩已成功输入！");
		}
	}
	initial();
}


void CTeacherScore::OnBnClickedButtonCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	// 删除此窗口
	((CMainFrame *)AfxGetMainWnd())->m_pTeacherScore->DestroyWindow();
}


void CTeacherScore::OnDestroy()
{
	CFormView::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	// 使菜单中‘成绩信息管理’项再次可用
	((CMainFrame *)AfxGetMainWnd())->m_bItemTeacherScore=TRUE;
	// 清空‘成绩信息管理’窗口指针
	((CMainFrame *)AfxGetMainWnd())->m_pTeacherScore=NULL;
}
