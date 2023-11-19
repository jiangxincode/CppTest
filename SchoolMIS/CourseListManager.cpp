// CourseListManager.cpp : 实现文件
//

#include "stdafx.h"
#include "ODBC.h"
#include "CourseListManager.h"
/***********************by jiangxin***********************/
#include "MainFrm.h"
extern CDatabase m_database;
extern CString m_ID;
extern int m_type;
/***********************by jiangxin***********************/


// CCourseListManager

IMPLEMENT_DYNCREATE(CCourseListManager, CFormView)

CCourseListManager::CCourseListManager()
	: CFormView(CCourseListManager::IDD)
	, m_courseID(_T(""))
	, m_course_name(_T(""))
	, m_class(_T(""))
	, m_teacher(_T(""))
	, m_weekday(_T(""))
	, m_dayhour(_T(""))
	, m_building(_T(""))
	, m_room(_T(""))
{

}

CCourseListManager::~CCourseListManager()
{
}

void CCourseListManager::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_courseID);
	DDX_Text(pDX, IDC_EDIT4, m_course_name);
	DDX_Text(pDX, IDC_EDIT2, m_class);
	DDX_Text(pDX, IDC_EDIT5, m_teacher);
	DDX_Text(pDX, IDC_COMBO2, m_weekday);
	DDX_Text(pDX, IDC_EDIT7, m_dayhour);
	DDX_Text(pDX, IDC_EDIT10, m_building);
	DDX_Text(pDX, IDC_EDIT11, m_room);
	DDX_Control(pDX, IDC_LIST_COURSE_LIST, m_course_list);
	DDX_Control(pDX, IDC_COMBO2, m_C_weekday);
}

BEGIN_MESSAGE_MAP(CCourseListManager, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CCourseListManager::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DEL, &CCourseListManager::OnBnClickedButtonDel)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, &CCourseListManager::OnBnClickedButtonChange)
	ON_BN_CLICKED(IDC_BUTTON_FRESH, &CCourseListManager::OnBnClickedButtonFresh)
	ON_NOTIFY(NM_CLICK, IDC_LIST_COURSE_LIST, &CCourseListManager::OnNMClickListCourseList)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CCourseListManager 诊断

#ifdef _DEBUG
void CCourseListManager::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CCourseListManager::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCourseListManager 消息处理程序


void CCourseListManager::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	// 自动调整窗口
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit(FALSE);
	// 设置标题
	GetParentFrame()->SetWindowText(L"课表信息子系统");
	CenterWindow();
	// 设置字体
	LOGFONT LogFont;
	GetFont()->GetLogFont(&LogFont);
	LogFont.lfHeight+=LogFont.lfHeight/2;
	LogFont.lfWidth+=LogFont.lfWidth/2;
	Font.CreateFontIndirect(&LogFont);
	GetDlgItem(IDC_STATIC_COURSE_LIST)->SetFont(&Font);
	// 设置列表控件
	m_course_list.InsertColumn(0,L"课程编号");
	m_course_list.InsertColumn(1,L"课程名称");
	m_course_list.InsertColumn(2,L"班级号");
	m_course_list.InsertColumn(3,L"教师");
	m_course_list.InsertColumn(4,L"上课时间");
	m_course_list.InsertColumn(5,L"上课时段");
	m_course_list.InsertColumn(6,L"教学楼号");
	m_course_list.InsertColumn(7,L"教师号");

	RECT rect;
	m_course_list.GetWindowRect(&rect);
	int width=rect.right-rect.left;
	m_course_list.SetColumnWidth(0,width/7);
	m_course_list.SetColumnWidth(1,width/7);
	m_course_list.SetColumnWidth(2,width/7);
	m_course_list.SetColumnWidth(3,width/7);
	m_course_list.SetColumnWidth(4,width/7);
	m_course_list.SetColumnWidth(5,width/7);
	m_course_list.SetColumnWidth(6,width/7);
	m_course_list.SetColumnWidth(7,width/7);
	m_course_list.SetColumnWidth(8,width/7);

	m_course_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	initial();
}


void CCourseListManager::initial(void)
{
	CDBVariant varValue;
	CString str,buf;
	int i=0;
	m_course_list.DeleteAllItems();
	CRecordset m_recordset(&m_database);
	CString strSQL;
	strSQL.Format(L"select * from COURSE_LIST");
	m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL);
	if(m_recordset.GetRecordCount()!=0)
		m_recordset.MoveFirst();
	while(!m_recordset.IsEOF())
	{
		int temp=0;
		// 对字符串进行处理
		m_recordset.GetFieldValue(temp,str);
		m_course_list.InsertItem(i,str);

		m_recordset.GetFieldValue(1,str);
		m_course_list.SetItemText(i,1,str);
		
		m_recordset.GetFieldValue(2,str);
		m_course_list.SetItemText(i,2,str);

		m_recordset.GetFieldValue(3,str);
		m_course_list.SetItemText(i,3,str);

		// 对组合选项进行处理
		m_recordset.GetFieldValue(4,varValue);
		switch (varValue.m_iVal)
		{
		case 0:
			m_course_list.SetItemText(i,4,L"星期一");
			break;
		case 1:
			m_course_list.SetItemText(i,4,L"星期二");
			break;
		case 2:
			m_course_list.SetItemText(i,4,L"星期三");
			break;
		case 3:
			m_course_list.SetItemText(i,4,L"星期四");
			break;
		case 4:
			m_course_list.SetItemText(i,4,L"星期五");
			break;
		case 5:
			m_course_list.SetItemText(i,4,L"星期六");
			break;
		case 6:
			m_course_list.SetItemText(i,4,L"星期日");
			break;
		default:
			break;
		}

		// 对字符串进行处理
		m_recordset.GetFieldValue(5,str);
		m_course_list.SetItemText(i,5,str);

		m_recordset.GetFieldValue(6,str);
		m_course_list.SetItemText(i,6,str);

		m_recordset.GetFieldValue(7,str);
		m_course_list.SetItemText(i,7,str);

		i++;
		m_recordset.MoveNext();
		
	}
	m_recordset.Close();
	// 使i指向课程列表的第一列
	i=0;
	// 从课程列表中选择对应信息填充到相应单元
	settext(0);
	UpdateData(FALSE);
}


void CCourseListManager::settext(int index)
{
	// 读取列表控件中各个字段值填充到对应的编辑框中
	m_courseID=m_course_list.GetItemText(index,0);
	m_course_name=m_course_list.GetItemText(index,1);
	m_class=m_course_list.GetItemText(index,2);
	m_teacher=m_course_list.GetItemText(index,3);
	m_weekday=m_course_list.GetItemText(index,4);
	m_dayhour=m_course_list.GetItemText(index,5);
	m_building=m_course_list.GetItemText(index,6);
	m_room=m_course_list.GetItemText(index,7);

	UpdateData(FALSE);
}


void CCourseListManager::OnBnClickedButtonAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int m_i_weekday=m_C_weekday.GetCurSel();
	// 检查信息完整性
	if(m_courseID.GetLength()==0)
		MessageBox(L"课程号不能为空！");
	else if(m_course_name.GetLength()==0)
		MessageBox(L"课程名不能为空！");
	else if(m_class.GetLength()==0)
		MessageBox(L"班级不能为空！");
	else if(m_dayhour.GetLength()==0)
		MessageBox(L"上课时间不能为空！");
	else if(m_teacher.GetLength()==0)
		MessageBox(L"教师不能为空！");
	else if(m_building.GetLength()==0)
		MessageBox(L"教学楼号不能为空！");
	else if(m_room.GetLength()==0)
		MessageBox(L"教室编号不能为空！");
	else
	{
		// 向数据库中添加课程信息
		CRecordset m_recordset(&m_database);
		CString strSQL;
		strSQL.Format(L"select * from COURSE_LIST where COURSE_ID='%s'",m_courseID);
		m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL);
		if(m_recordset.GetRecordCount()==0)
		{
			strSQL.Format(L"insert into COURSE_LIST (COURSE_ID,COURSE_NAME,COURSE_TEACHER,WEEKDAY,DAYHOUR,BUILDING,ROOM) values(\'%s\',\'%s\',\'%s\',\'%d\',\'%s\',\'%s\',\'%s\')",m_courseID,m_course_name,m_teacher,m_weekday,m_dayhour,m_building,m_room);
			m_database.ExecuteSQL(strSQL);
			MessageBox(L"已经成功添加课表信息！");
		}
		else
		{
			MessageBox(L"此课表信息已存在，请核对！");
		}
		initial();
	}
}


void CCourseListManager::OnBnClickedButtonDel()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CRecordset m_recordset(&m_database);
	CString strSQL;
	strSQL.Format(L"select * from COURSE_LIST where COURSE_ID='%s'",m_courseID);
	m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL);
	// 数据库中无此记录
	if(m_recordset.GetRecordCount()==0)
	{
		MessageBox(L"无此信息，请核对！");
	}
	else
	{
		strSQL.Format(L"delete from COURSE_LIST where COURSE_ID='%s'",m_courseID);
		m_database.ExecuteSQL(strSQL);
		MessageBox(L"已成功删除该课表信息！");
		CCourseListManager::OnBnClickedButtonFresh();
	}
	initial();
}


void CCourseListManager::OnBnClickedButtonChange()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int m_i_weekday=m_C_weekday.GetCurSel();
	// 检查信息完整性
	if(m_courseID.GetLength()==0)
		MessageBox(L"课程号不能为空！");
	else if(m_course_name.GetLength()==0)
		MessageBox(L"课程名不能为空！");
	else if(m_class.GetLength()==0)
		MessageBox(L"班级不能为空！");
	else if(m_dayhour.GetLength()==0)
		MessageBox(L"上课时间不能为空！");
	else if(m_teacher.GetLength()==0)
		MessageBox(L"教师不能为空！");
	else if(m_building.GetLength()==0)
		MessageBox(L"教学楼号不能为空！");
	else if(m_room.GetLength()==0)
		MessageBox(L"教室编号不能为空！");
	else
	{
		CRecordset m_recordset(&m_database);
		CString strSQL;
		strSQL.Format(L"select * from COURSE_LIST where COURSE_ID='%s'",m_courseID);
		m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL);
		if(m_recordset.GetRecordCount()!=0)
		{
			strSQL.Format(L"update COURSE_LIST set COURSE_ID='%s',COURSE_NAME='%s',CLASS_ID='%s',COURSE_TEACHER='%s',WEEKDAY='%d',DAYHOUR='%s',BUILDING='%s',ROOM='%s' where COURSE_ID='%s'"
				,m_courseID,m_course_name,m_class,m_teacher,m_weekday,m_dayhour,m_building,m_room,m_courseID);
			m_database.ExecuteSQL(strSQL);
			MessageBox(L"已经修改添加课表信息！");
		}
		else
		{
			MessageBox(L"无此信息，请核对！");
		}
		initial();
	}

}


void CCourseListManager::OnBnClickedButtonFresh()
{
	// TODO: 在此添加控件通知处理程序代码
	//设置各控件为空值
	m_courseID="";
	m_course_name="";
	m_teacher="";
	m_weekday="";
	m_dayhour="";
	m_teacher="";
	m_building="";
	m_room="";
	UpdateData(FALSE);
}


void CCourseListManager::OnNMClickListCourseList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	// 获得选中的课程标识信息
	int i=m_course_list.GetSelectionMark();
	// 调用显示函数进行详细显示
	settext(i);
	*pResult = 0;
}


void CCourseListManager::OnDestroy()
{
	CFormView::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	// 使菜单中‘课表信息管理’项再次可用
	((CMainFrame *)AfxGetMainWnd())->m_bItemCourseListManager=TRUE;
	// 清空‘课表信息管理’窗口指针
	((CMainFrame *)AfxGetMainWnd())->m_pCourseListManager=NULL;
}
