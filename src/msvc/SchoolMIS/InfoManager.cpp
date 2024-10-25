// InfoManager.cpp : 实现文件
//

#include "stdafx.h"
#include "SchoolMIS.h"
#include "InfoManager.h"

/***********************by jiangxin***********************/
#include "MainFrm.h"
extern CDatabase m_database;
extern CString m_ID;
extern int m_type;
/***********************by jiangxin***********************/


// CInfoManager

IMPLEMENT_DYNCREATE(CInfoManager, CFormView)

CInfoManager::CInfoManager()
	: CFormView(CInfoManager::IDD)
	, m_student_name(_T(""))
	, m_student_number(_T(""))
	, m_teacher_name(_T(""))
	, m_teacher_number(_T(""))
{

}

CInfoManager::~CInfoManager()
{
}

void CInfoManager::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STUDENT_NAME, m_student_name);
	DDX_Text(pDX, IDC_STUDENT_NUMBER, m_student_number);
	DDX_Control(pDX, IDC_STUDENT, m_student);
	DDX_Text(pDX, IDC_TEACHER_NAME, m_teacher_name);
	DDX_Text(pDX, IDC_TEACHER_NUMBER, m_teacher_number);
	DDX_Control(pDX, IDC_TEACHER, m_teacher);
}

BEGIN_MESSAGE_MAP(CInfoManager, CFormView)
	
	ON_NOTIFY(NM_CLICK, IDC_STUDENT, &CInfoManager::OnNMClickStudent)
	ON_NOTIFY(NM_CLICK, IDC_TEACHER, &CInfoManager::OnNMClickTeacher)
	ON_BN_CLICKED(IDC_STUDENT_ADD, &CInfoManager::OnBnClickedStudentAdd)
	ON_BN_CLICKED(IDC_STUDENT_DEL, &CInfoManager::OnBnClickedStudentDel)
	ON_BN_CLICKED(IDC_STUDENT_FRESH, &CInfoManager::OnBnClickedStudentFresh)
	ON_BN_CLICKED(IDC_TEACHER_ADD, &CInfoManager::OnBnClickedTeacherAdd)
	ON_BN_CLICKED(IDC_TEACHER_DEL, &CInfoManager::OnBnClickedTeacherDel)
	ON_BN_CLICKED(IDC_TEACHER_FRESH, &CInfoManager::OnBnClickedTeacherFresh)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CInfoManager 诊断

#ifdef _DEBUG
void CInfoManager::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CInfoManager::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CInfoManager 消息处理程序


void CInfoManager::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	// 调整界面
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit(FALSE);
	// 设置标题
	GetParentFrame()->SetWindowText(L"基本信息管理");
	// 设置学生列表控件
	m_student.InsertColumn(0,L"学号");
	m_student.InsertColumn(1,L"姓名");

	RECT rect;
	m_student.GetWindowRect(&rect);
	int width=rect.right-rect.left;
	m_student.SetColumnWidth(0,width/2);
	m_student.SetColumnWidth(1,width/2);

	m_student.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	// 设置教师列表控件
	m_teacher.InsertColumn(0,L"教师编号");
	m_teacher.InsertColumn(1,L"姓名");

	m_teacher.GetWindowRect(&rect);
	width = rect.right-rect.left;
	m_teacher.SetColumnWidth(0,width/2);
	m_teacher.SetColumnWidth(1,width/2);

	m_teacher.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	initial();
}


void CInfoManager::initial(void)
{
	CString temp;
	int i;
	CRecordset m_recordset(&m_database);
	CString strSQL;

	// 取得学生信息
	i=0;
	m_student.DeleteAllItems();
	strSQL.Format(L"select * from STUDENT_INFO");
	m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL);
	if(m_recordset.GetRecordCount()!=0)
		m_recordset.MoveFirst();
	while(!m_recordset.IsEOF())
	{
		int t=0;
		// 对字符串进行处理
		m_recordset.GetFieldValue(t,temp);
		m_student.InsertItem(i,temp);

		m_recordset.GetFieldValue(1,temp);
		m_student.SetItemText(i,1,temp);

		m_recordset.MoveNext();
		i++;
	}
	m_recordset.Close();
	// 取得教师信息
	i=0;
	m_teacher.DeleteAllItems();
	strSQL.Format(L"select * from TEACHER_INFO");
	m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL);
	if(m_recordset.GetRecordCount()!=0)
		m_recordset.MoveFirst();
	while(!m_recordset.IsEOF())
	{
		int t=0;
		// 对字符串进行处理
		m_recordset.GetFieldValue(t,temp);
		m_teacher.InsertItem(i,temp);

		m_recordset.GetFieldValue(1,temp);
		m_teacher.SetItemText(i,1,temp);

		m_recordset.MoveNext();
		i++;
	}
	m_recordset.Close();

	// 使i指向课程列表中的第一列
	i=0;
	// 从列表中选择对应信息填充到相应单元
	settext_student(0);
	settext_teacher(0);
}


void CInfoManager::settext_student(int index)
{
	// 显示学生信息
	m_student_number=m_student.GetItemText(index,0);
	m_student_name=m_student.GetItemText(index,1);
	UpdateData(FALSE);
}


void CInfoManager::settext_teacher(int index)
{
	// 显示教师信息
	m_teacher_number=m_teacher.GetItemText(index,0);
	m_teacher_name=m_teacher.GetItemText(index,1);
	UpdateData(FALSE);
}


void CInfoManager::OnNMClickStudent(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	// 获取选中的学生信息标志
	int i=m_student.GetSelectionMark();
	// 调用显示函数进行详细显示
	settext_student(i);
	*pResult = 0;
}


void CInfoManager::OnNMClickTeacher(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	// 获取选中的教师信息标志
	int i=m_teacher.GetSelectionMark();
	// 调用显示函数进行详细显示
	settext_teacher(i);
	*pResult = 0;
}


void CInfoManager::OnBnClickedStudentAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	// 获取编辑框中的信息
	UpdateData(TRUE);
	// 检查信息是否完整
	if(m_student_name.GetLength()==0)
		MessageBox(L"学生姓名不能为空！");
	else if(m_student_number.GetLength()==0)
		MessageBox(L"学生学号不能为空1");
	else
	{
		CRecordset m_recordset(&m_database);
		CString strSQL;
		strSQL.Format(L"select * from STUDENT_INFO where STU_ID='%s'",m_student_number);
		m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL);
		if(m_recordset.GetRecordCount()==0)
		{
			CTime time=CTime::GetCurrentTime();
			strSQL.Format(L"insert into STUDENT_INFO(STU_ID,STU_NAME,ENROLLMENT_TIME,DEPARTMENT,MAJOR,SEX,BIRTHDAY,HOMETOWN,ADDRESS,PHONE,RACE,PARTY,DIRECTION) values(%s,\'%s\',\'%d-%d-%d\',\' \',\' \','0',\'%d-%d-%d\',\' \',\' \',\' \',\' \','0',\' \')"
				,m_student_number,m_student_name,time.GetYear(),time.GetMonth(),time.GetDay(),time.GetYear(),time.GetMonth(),time.GetDay());
			m_database.ExecuteSQL(strSQL);
			/* 此处改为由数据库完成
			strSQL.Format(L"insert into USERS(USER_ID,USER_PASSWORD,USER_TYPE) values('%s','%s','1')"
				,m_student_number,m_student_number);
			m_database.ExecuteSQL(strSQL);
			*/
			MessageBox(L"已成功添加学生信息！");
		}
		else
		{
			MessageBox(L"此学生信息已存在，请核对！");
		}
		initial();
	}
}


void CInfoManager::OnBnClickedStudentDel()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CRecordset m_recordset(&m_database);
	CString strSQL;
	strSQL.Format(L"select * from STUDENT_INFO where STU_ID='%s'",m_student_number);
	m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL);
	if(m_recordset.GetRecordCount()==0)
	{
		MessageBox(L"无此信息，请核对！");
	}
	else
	{
		strSQL.Format(L"delete from STUDENT_INFO where STU_ID='%s'",m_student_number);
		m_database.ExecuteSQL(strSQL);
		/* 此处改为由数据库完成
		strSQL.Format(L"delete from USERS where USER_ID='%s'",m_student_number);
		m_database.ExecuteSQL(strSQL);
		*/
		MessageBox(L"已成功删除学生信息！");
	}
	initial();
}


void CInfoManager::OnBnClickedStudentFresh()
{
	// TODO: 在此添加控件通知处理程序代码
	// 设置编辑框为空
	m_student_name=L"";
	m_student_number=L"";
	UpdateData(FALSE);
}


void CInfoManager::OnBnClickedTeacherAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	// 获取编辑框中的信息
	UpdateData(TRUE);
	// 检查信息是否完整
	if(m_teacher_name.GetLength()==0)
		MessageBox(L"教师姓名不能为空！");
	else if(m_teacher_number.GetLength()==0)
		MessageBox(L"教师编号不能为空1");
	else
	{
		CRecordset m_recordset(&m_database);
		CString strSQL;
		strSQL.Format(L"select * from TEACHER_INFO where TEA_ID='%s'",m_teacher_number);
		m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL);
		if(m_recordset.GetRecordCount()==0)
		{
			CTime time=CTime::GetCurrentTime();
			strSQL.Format(L"insert into TEACHER_INFO(TEA_ID,TEA_NAME,TITLE,DEPARTMENT,MAJOR,SEX,BIRTHDAY,HOMETOWN,ADDRESS,PHONE,RACE,PARTY,DIRECTION) values(%s,\'%s\',\' \',\' \',\' \','0',\'%d-%d-%d\',\' \',\' \',\' \',\' \','0',\' \')"
				,m_teacher_number,m_teacher_name,time.GetYear(),time.GetMonth(),time.GetDay());
			m_database.ExecuteSQL(strSQL);
			/* 此处改为由数据库完成
			strSQL.Format(L"insert into USERS(USER_ID,USER_PASSWORD,USER_TYPE) values('%s','%s',2)",m_teacher_number,m_teacher_number);
			m_database.ExecuteSQL(strSQL);
			*/
			MessageBox(L"已成功添加教师信息！");
		}
		else
		{
			MessageBox(L"此教师信息已存在，请核对！");
		}
		initial();
	}
}


void CInfoManager::OnBnClickedTeacherDel()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CRecordset m_recordset(&m_database);
	CString strSQL;
	strSQL.Format(L"select * from TEACHER_INFO where TEA_ID='%s'",m_teacher_number);
	m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL);
	if(m_recordset.GetRecordCount()==0)
	{
		MessageBox(L"无此信息，请核对！");
	}
	else
	{
		strSQL.Format(L"delete from TEACHER_INFO where TEA_ID='%s'",m_teacher_number);
		m_database.ExecuteSQL(strSQL);
		/* 此处改为由数据库完成
		strSQL.Format(L"delete from USERS where USER_ID='%s'",m_teacher_number);
		m_database.ExecuteSQL(strSQL);
		*/
		MessageBox(L"已成功删除教师信息！");
	}
	initial();
}


void CInfoManager::OnBnClickedTeacherFresh()
{
	// TODO: 在此添加控件通知处理程序代码
	// 设置编辑框为空
	m_teacher_name=L"";
	m_teacher_number=L"";
	UpdateData(FALSE);
}


void CInfoManager::OnDestroy()
{
	CFormView::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	// 使菜单中‘基本信息管理’项再次可用
	((CMainFrame *)AfxGetMainWnd())->m_bItemInfoManager=TRUE;
	// 清空‘基本信息管理’窗口指针
	((CMainFrame *)AfxGetMainWnd())->m_pInfoManager=NULL;
}
