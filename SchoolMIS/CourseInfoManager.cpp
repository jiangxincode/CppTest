// CourseInfoManager.cpp : 实现文件
//

#include "stdafx.h"
#include "ODBC.h"
#include "CourseInfoManager.h"
/***********************by jiangxin***********************/
#include "MainFrm.h"
extern CDatabase m_database;
extern CString m_ID;
extern int m_type;
/***********************by jiangxin***********************/


// CCourseInfoManager

IMPLEMENT_DYNCREATE(CCourseInfoManager, CFormView)

CCourseInfoManager::CCourseInfoManager()
	: CFormView(CCourseInfoManager::IDD)
	, m_courseID(_T(""))
	, m_course_name(_T(""))
	, m_course_time(_T(""))
	, m_teacher(_T(""))
	, m_cent(_T(""))
	, m_require(_T(""))
	, m_instruction(_T(""))
	, m_start(COleDateTime::GetCurrentTime())
	, m_end(COleDateTime::GetCurrentTime())
{

}

CCourseInfoManager::~CCourseInfoManager()
{
}

void CCourseInfoManager::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_COURSE_ID, m_courseID);
	DDX_Text(pDX, IDC_EDIT_COURSE_NAME, m_course_name);
	DDX_Text(pDX, IDC_EDIT_TIME, m_course_time);
	DDX_Text(pDX, IDC_EDIT_TEACHER, m_teacher);
	DDX_Text(pDX, IDC_EDIT_CENT, m_cent);
	DDX_Text(pDX, IDC_EDIT_REQUIRE, m_require);
	DDX_Text(pDX, IDC_EDIT_INSTRUCTION, m_instruction);
	DDX_Control(pDX, IDC_LIST_COURSE, m_course);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_start);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_end);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_C_start);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_C_end);
}

BEGIN_MESSAGE_MAP(CCourseInfoManager, CFormView)
	ON_NOTIFY(NM_CLICK, IDC_LIST_COURSE, &CCourseInfoManager::OnNMClickListCourse)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CCourseInfoManager::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DEL, &CCourseInfoManager::OnBnClickedButtonDel)
	ON_BN_CLICKED(IDC_BUTTON_FRESH, &CCourseInfoManager::OnBnClickedButtonFresh)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, &CCourseInfoManager::OnBnClickedButtonChange)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CCourseInfoManager 诊断

#ifdef _DEBUG
void CCourseInfoManager::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CCourseInfoManager::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCourseInfoManager 消息处理程序


void CCourseInfoManager::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	// 自动调整窗口
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit(FALSE);
	// 设置标题
	GetParentFrame()->SetWindowText(L"课程信息子系统");
	CenterWindow();
	// 设置字体
	LOGFONT LogFont;
	GetFont()->GetLogFont(&LogFont);
	LogFont.lfHeight+=LogFont.lfHeight/2;
	LogFont.lfWidth+=LogFont.lfWidth/2;
	Font.CreateFontIndirect(&LogFont);
	GetDlgItem(IDC_STATIC_COURSE)->SetFont(&Font);
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


void CCourseInfoManager::initial(void)
{
	CDBVariant varValue;
	CString str,buf;
	int i=0;
	m_course.DeleteAllItems();
	CRecordset m_recordset(&m_database);
	CString strSQL;
	strSQL.Format(L"select * from COURSE");
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
	
	// 使i指向课程列表的第一列
	i=0;
	// 从课程列表中选择对应信息填充到相应单元
	settext(0);
	UpdateData(FALSE);
}


void CCourseInfoManager::settext(int index)
{
	// 读取列表控件中各个字段值填充到对应的编辑框中
	m_courseID=m_course.GetItemText(index,0);
	m_course_name=m_course.GetItemText(index,1);
	m_course_time=m_course.GetItemText(index,2);
//	m_start.ParseDateTime(m_course.GetItemText(index,3));
//	m_end.ParseDateTime(m_course.GetItemText(index,4));
	m_cent=m_course.GetItemText(index,5);
	m_teacher=m_course.GetItemText(index,6);
	m_require=m_course.GetItemText(index,7);
	m_instruction=m_course.GetItemText(index,8);

	UpdateData(FALSE);
}


void CCourseInfoManager::OnNMClickListCourse(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	// 获得选中的课程标识信息
	int i=m_course.GetSelectionMark();
	// 调用显示函数进行详细显示
	settext(i);
	*pResult = 0;
}


void CCourseInfoManager::OnBnClickedButtonAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	// 获取时间信息

	m_C_start.GetTime(m_start);
	m_C_end.GetTime(m_end);
	int cent=_ttoi(m_cent);
	// 检查信息完整性
	if(m_courseID.GetLength()==0)
		MessageBox(L"课程号不能为空！");
	else if(m_course_name.GetLength()==0)
		MessageBox(L"课程名不能为空！");
	else if(m_course_time.GetLength()==0)
		MessageBox(L"上课时间不能为空！");
	else if(m_cent.GetLength()==0)
		MessageBox(L"学分不能为空！");
	else if(m_teacher.GetLength()==0)
		MessageBox(L"教师不能为空！");
	else if(m_require.GetLength()==0)
		MessageBox(L"课程要求不能为空！");
	else if(m_instruction.GetLength()==0)
		MessageBox(L"课程介绍不能为空！");
	else
	{
		// 向数据库中添加课程信息
		CRecordset m_recordset(&m_database);
		CString strSQL;
		strSQL.Format(L"select * from COURSE where COURSE_ID='%s'",m_courseID);
		m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL);
		if(m_recordset.GetRecordCount()==0)
		{
			strSQL.Format(L"insert into COURSE (COURSE_ID,COURSE_NAME,COURSE_TIME,START_DATE,END_DATE,CENT,COURSE_TEACHER,REQUIRE,INSTRUCTION) values(\'%s\',\'%s\',\'%s\',\'%d-%d-%d\',\'%d-%d-%d\',\'%d\',\'%s\',\'%s\',\'%s\')",m_courseID,m_course_name,m_course_time,m_start.GetYear(),m_start.GetMonth(),m_start.GetDay(),m_end.GetYear(),m_end.GetMonth(),m_end.GetDay(),cent,m_teacher,m_require,m_instruction);
			m_database.ExecuteSQL(strSQL);
			MessageBox(L"已经成功添加课程信息！");
		}
		else
		{
			MessageBox(L"此课程信息已存在，请核对！");
		}
		initial();
	}
}


void CCourseInfoManager::OnBnClickedButtonDel()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CRecordset m_recordset(&m_database);
	CString strSQL;
	strSQL.Format(L"select * from COURSE where COURSE_ID='%s'",m_courseID);
	m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL);
	// 数据库中无此记录
	if(m_recordset.GetRecordCount()==0)
	{
		MessageBox(L"无此信息，请核对！");
	}
	else
	{
		strSQL.Format(L"delete from COURSE where COURSE_ID='%s'",m_courseID);
		m_database.ExecuteSQL(strSQL);
		MessageBox(L"已成功删除该课程信息！");
		CCourseInfoManager::OnBnClickedButtonFresh();
	}
	initial();
}


void CCourseInfoManager::OnBnClickedButtonFresh()
{
	// TODO: 在此添加控件通知处理程序代码
	//设置各控件为空值
	m_courseID="";
	m_course_name="";
	m_course_time="";
	m_C_start.SetTime(COleDateTime(2000,1,1,0,0,0));
	m_C_end.SetTime(COleDateTime(2000,1,1,0,0,0));
	m_cent="";
	m_teacher="";
	m_require="";
	m_instruction="";
	UpdateData(FALSE);
}


void CCourseInfoManager::OnBnClickedButtonChange()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	// 获取时间信息
	m_C_start.GetTime(m_start);
	m_C_end.GetTime(m_end);
	int cent=_ttoi(m_cent);
	// 检查信息完整性
	if(m_courseID.GetLength()==0)
		MessageBox(L"课程号不能为空！");
	else if(m_course_name.GetLength()==0)
		MessageBox(L"课程名不能为空！");
	else if(m_course_time.GetLength()==0)
		MessageBox(L"上课时间不能为空！");
	else if(m_cent.GetLength()==0)
		MessageBox(L"学分不能为空！");
	else if(m_teacher.GetLength()==0)
		MessageBox(L"教师不能为空！");
	else if(m_require.GetLength()==0)
		MessageBox(L"课程要求不能为空！");
	else if(m_instruction.GetLength()==0)
		MessageBox(L"课程介绍不能为空！");
	else
	{
		CRecordset m_recordset(&m_database);
		CString strSQL;
		strSQL.Format(L"select * from COURSE where COURSE_ID='%s'",m_courseID);
		m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL);
		if(m_recordset.GetRecordCount()!=0)
		{
			strSQL.Format(L"update COURSE set COURSE_ID='%s',COURSE_NAME='%s',COURSE_TIME='%s',START_DATE='%d-%d-%d',END_DATE='%d-%d-%d',CENT='%d',COURSE_TEACHER='%s',REQUIRE='%s',INSTRUCTION='%s' where COURSE_ID='%s'"
				,m_courseID,m_course_name,m_course_time,m_start.GetYear(),m_start.GetMonth(),m_start.GetDay(),m_end.GetYear(),m_end.GetMonth(),m_end.GetDay(),cent,m_teacher,m_require,m_instruction,m_courseID);
			m_database.ExecuteSQL(strSQL);
			MessageBox(L"已经成功更新课程信息！");
		}
		else
		{
			MessageBox(L"无此信息，请核对！");
		}
		initial();
	}
}


void CCourseInfoManager::OnDestroy()
{
	CFormView::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	// 使菜单中‘基本信息管理’项再次可用
	((CMainFrame *)AfxGetMainWnd())->m_bItemCourseInfoManager=TRUE;
	// 清空‘基本信息管理’窗口指针
	((CMainFrame *)AfxGetMainWnd())->m_pCourseInfoManager=NULL;
}
