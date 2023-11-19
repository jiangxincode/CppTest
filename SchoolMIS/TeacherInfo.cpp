// TeacherInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "SchoolMIS.h"
#include "TeacherInfo.h"
/***********************by jiangxin***********************/
#include "MainFrm.h"
extern CDatabase m_database;
extern CString m_ID;
extern int m_type;
/***********************by jiangxin***********************/

// CTeacherInfo

IMPLEMENT_DYNCREATE(CTeacherInfo, CFormView)

CTeacherInfo::CTeacherInfo()
	: CFormView(CTeacherInfo::IDD)
	, m_name(_T(""))
	, m_number(_T(""))
	, m_department(_T(""))
	, m_major(_T(""))
	, m_sex(0)
	, m_title(0)
	, m_party(0)
	, m_race(_T(""))
	, m_phone(_T(""))
	, m_hometown(_T(""))
	, m_address(_T(""))
	, m_other(_T(""))
{
/***********************by jiangxin***********************/
	// 初始化成员变量
	b_address=FALSE;
	b_birthday=FALSE;
	b_department=FALSE;
	b_hometown=FALSE;
	b_major=FALSE;
	b_other=FALSE;
	b_party=FALSE;
	b_phone=FALSE;
	b_race=FALSE;
	b_sex=FALSE;
	b_title=FALSE;
/***********************by jiangxin***********************/
}

CTeacherInfo::~CTeacherInfo()
{
}

void CTeacherInfo::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_name);
	DDX_Text(pDX, IDC_EDIT_ID, m_number);
	DDX_Text(pDX, IDC_EDIT_DEPARTMENT, m_department);
	DDX_Text(pDX, IDC_EDIT_MAJOR, m_major);
	DDX_CBIndex(pDX, IDC_COMBO_SEX, m_sex);
	DDX_Control(pDX, IDC_COMBO_SEX, m_c_sex);
	DDX_CBIndex(pDX, IDC_COMBO_TITLE, m_title);
	DDX_Control(pDX, IDC_COMBO_TITLE, m_c_title);
	DDX_CBIndex(pDX, IDC_COMBO_PARTY, m_party);
	DDX_Control(pDX, IDC_COMBO_PARTY, m_c_party);
	DDX_Text(pDX, IDC_EDIT_RACE, m_race);
	DDX_Text(pDX, IDC_EDIT_phone, m_phone);
	DDX_Text(pDX, IDC_EDIT_HOMETOWN, m_hometown);
	DDX_Text(pDX, IDC_EDIT_ADDRESS, m_address);
	DDX_Text(pDX, IDC_EDIT_OTHER, m_other);
	DDX_Control(pDX, IDC_DATETIMEPICKER_BIRTHDAY, m_birthday);
}

BEGIN_MESSAGE_MAP(CTeacherInfo, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO_SEX, &CTeacherInfo::OnCbnSelchangeComboSex)
	ON_EN_CHANGE(IDC_EDIT_DEPARTMENT, &CTeacherInfo::OnEnChangeEditDepartment)
	ON_EN_CHANGE(IDC_EDIT_MAJOR, &CTeacherInfo::OnEnChangeEditMajor)
	ON_CBN_SELCHANGE(IDC_COMBO_TITLE, &CTeacherInfo::OnCbnSelchangeComboTitle)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_BIRTHDAY, &CTeacherInfo::OnDtnDatetimechangeDatetimepickerBirthday)
	ON_CBN_SELCHANGE(IDC_COMBO_PARTY, &CTeacherInfo::OnCbnSelchangeComboParty)
	ON_EN_CHANGE(IDC_EDIT_RACE, &CTeacherInfo::OnEnChangeEditRace)
	ON_EN_CHANGE(IDC_EDIT_phone, &CTeacherInfo::OnEnChangeEditphone)
	ON_EN_CHANGE(IDC_EDIT_HOMETOWN, &CTeacherInfo::OnEnChangeEditHometown)
	ON_EN_CHANGE(IDC_EDIT_ADDRESS, &CTeacherInfo::OnEnChangeEditAddress)
	ON_EN_CHANGE(IDC_EDIT_OTHER, &CTeacherInfo::OnEnChangeEditOther)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, &CTeacherInfo::OnBnClickedButtonChange)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_CANCLE, &CTeacherInfo::OnBnClickedButtonCancle)
END_MESSAGE_MAP()


// CTeacherInfo 诊断

#ifdef _DEBUG
void CTeacherInfo::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CTeacherInfo::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTeacherInfo 消息处理程序


void CTeacherInfo::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	// 自动调整窗口
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit(FALSE);
	// 设置标题
	GetParentFrame()->SetWindowText(L"教师信息管理");
	CenterWindow();
	// 设置字体
	LOGFONT LogFont;
	GetFont()->GetLogFont(&LogFont);
	LogFont.lfHeight+=LogFont.lfHeight/2;
	LogFont.lfWidth+=LogFont.lfWidth;
	Font.CreateFontIndirect(&LogFont);
	GetDlgItem(IDC_STATIC_TEA_INFO)->SetFont(&Font);
	initial();
}


void CTeacherInfo::initial(void)
{
	CDBVariant varValue;
	CRecordset m_recordset(&m_database);
	CString strSQL;
	// 得到“教师生日”信息
	strSQL.Format(L"select BIRTHDAY from TEACHER_INFO where TEA_ID='%s'",m_ID);
	m_recordset.Open(CRecordset::forwardOnly,strSQL);
	m_recordset.GetFieldValue(L"BIRTHDAY",varValue);
	m_birthday.SetTime(COleDateTime(varValue.m_pdate->year,varValue.m_pdate->month,varValue.m_pdate->day,0,0,0));
	m_recordset.Close();
	// 得到“教师家庭住址”信息
	strSQL.Format(L"select ADDRESS from TEACHER_INFO where TEA_ID='%s'",m_ID);
	m_recordset.Open(CRecordset::forwardOnly,strSQL);
	m_recordset.GetFieldValue(L"ADDRESS",m_address);
	m_recordset.Close();
	// 得到“教师所在学院”信息
	strSQL.Format(L"select DEPARTMENT from TEACHER_INFO where TEA_ID='%s'",m_ID);
	m_recordset.Open(CRecordset::forwardOnly,strSQL);
	m_recordset.GetFieldValue(L"DEPARTMENT",m_department);
	m_recordset.Close();
	// 得到“教师籍贯”信息
	strSQL.Format(L"select HOMETOWN from TEACHER_INFO where TEA_ID='%s'",m_ID);
	m_recordset.Open(CRecordset::forwardOnly,strSQL);
	m_recordset.GetFieldValue(L"HOMETOWN",m_hometown);
	m_recordset.Close();
	// 得到“教师专业”信息
	strSQL.Format(L"select MAJOR from TEACHER_INFO where TEA_ID='%s'",m_ID);
	m_recordset.Open(CRecordset::forwardOnly,strSQL);
	m_recordset.GetFieldValue(L"MAJOR",m_major);
	m_recordset.Close();
	// 得到“教师姓名”信息
	strSQL.Format(L"select TEA_NAME from TEACHER_INFO where TEA_ID='%s'",m_ID);
	m_recordset.Open(CRecordset::forwardOnly,strSQL);
	m_recordset.GetFieldValue(L"TEA_NAME",m_name);
	m_recordset.Close();
	// 得到“教师号”信息
	strSQL.Format(L"select TEA_ID from TEACHER_INFO where TEA_ID='%s'",m_ID);
	m_recordset.Open(CRecordset::forwardOnly,strSQL);
	m_recordset.GetFieldValue(L"TEA_ID",m_number);
	m_recordset.Close();
	// 得到“教师其他说明”信息
	strSQL.Format(L"select DIRECTION from TEACHER_INFO where TEA_ID='%s'",m_ID);
	m_recordset.Open(CRecordset::forwardOnly,strSQL);
	m_recordset.GetFieldValue(L"DIRECTION",m_other);
	m_recordset.Close();
	// 得到“教师联系电话”信息
	strSQL.Format(L"select PHONE from TEACHER_INFO where TEA_ID='%s'",m_ID);
	m_recordset.Open(CRecordset::forwardOnly,strSQL);
	m_recordset.GetFieldValue(L"PHONE",m_phone);
	m_recordset.Close();
	// 得到“教师民族”信息
	strSQL.Format(L"select RACE from TEACHER_INFO where TEA_ID='%s'",m_ID);
	m_recordset.Open(CRecordset::forwardOnly,strSQL);
	m_recordset.GetFieldValue(L"RACE",m_race);
	m_recordset.Close();
	// 得到“教师性别”信息
	strSQL.Format(L"select SEX from TEACHER_INFO where TEA_ID='%s'",m_ID);
	m_recordset.Open(CRecordset::forwardOnly,strSQL);
	m_recordset.GetFieldValue(L"SEX",varValue);
	m_sex=varValue.m_iVal;
	m_recordset.Close();
	// 得到“教师政治面貌”信息
	strSQL.Format(L"select PARTY from TEACHER_INFO where TEA_ID='%s'",m_ID);
	m_recordset.Open(CRecordset::forwardOnly,strSQL);
	m_recordset.GetFieldValue(L"PARTY",varValue);
	m_party=varValue.m_iVal;
	m_recordset.Close();
	// 得到“教师职称”信息
	strSQL.Format(L"select TITLE from TEACHER_INFO where TEA_ID='%s'",m_ID);
	m_recordset.Open(CRecordset::forwardOnly,strSQL);
	m_recordset.GetFieldValue(L"TITLE",varValue);
	m_title=varValue.m_iVal;
	m_recordset.Close();
	// 更新界面数据
	UpdateData(FALSE);
}


void CTeacherInfo::OnCbnSelchangeComboId()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CTeacherInfo::OnCbnSelchangeComboSex()
{
	// TODO: 在此添加控件通知处理程序代码
	//得到性别组合框中选中的信息
	m_sex=m_c_sex.GetCurSel();
	//标志‘教师性别’信息需改动
	b_sex=TRUE;
}


void CTeacherInfo::OnEnChangeEditDepartment()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CFormView::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

//#1015

	// TODO:  在此添加控件通知处理程序代码
	//标志‘所在学院’信息需改动
	b_department=TRUE;
}


void CTeacherInfo::OnEnChangeEditMajor()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CFormView::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

//#1015

	// TODO:  在此添加控件通知处理程序代码
	b_major=TRUE;
}


void CTeacherInfo::OnCbnSelchangeComboTitle()
{
	// TODO: 在此添加控件通知处理程序代码
	//得到职称组合框中选中的信息
	m_title=m_c_title.GetCurSel();
	//标志‘教师职称’信息需改动
	b_title=TRUE;
}


void CTeacherInfo::OnDtnDatetimechangeDatetimepickerBirthday(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	b_birthday=TRUE;
	*pResult = 0;
}


void CTeacherInfo::OnCbnSelchangeComboParty()
{
	// TODO: 在此添加控件通知处理程序代码
	// 得到政治面貌组合框中选中的信息
	m_party=m_c_party.GetCurSel();
	// 标志'教师政治面貌'信息需改动
	b_party=TRUE;
}


void CTeacherInfo::OnEnChangeEditRace()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CFormView::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

//#1015

	// TODO:  在此添加控件通知处理程序代码
	// 标志‘教师民族’信息需改动
	b_race=TRUE;
}


void CTeacherInfo::OnEnChangeEditphone()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CFormView::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

//#1015

	// TODO:  在此添加控件通知处理程序代码
	// 标志‘教师联系电话’信息需改动
	b_phone=TRUE;
}


void CTeacherInfo::OnEnChangeEditHometown()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CFormView::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

//#1015

	// TODO:  在此添加控件通知处理程序代码
	// 标志‘籍贯’信息需改动
	b_hometown=TRUE;
}


void CTeacherInfo::OnEnChangeEditAddress()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CFormView::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

//#1015

	// TODO:  在此添加控件通知处理程序代码
	// 标志‘教师家庭住址’信息需改动
	b_address=TRUE;
}


void CTeacherInfo::OnEnChangeEditOther()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CFormView::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

//#1015

	// TODO:  在此添加控件通知处理程序代码
	// 标志‘教师其他说明’信息需改动
	b_other=TRUE;
}


void CTeacherInfo::OnBnClickedButtonChange()
{
	// TODO: 在此添加控件通知处理程序代码
	// 初始设置修改标志flag为FALSE，表示无需修改
	BOOL flag;
	flag=FALSE;
	// 得到控件中的信息
	UpdateData();
	CString strSQL;

	//修改‘教师家庭住址’信息
	if(b_address=TRUE)
	{
		strSQL.Format(L"update TEACHER_INFO set ADDRESS = '%s' where TEA_ID='%s'",m_address,m_ID);
		m_database.ExecuteSQL(strSQL);
		flag=TRUE;
	}
	//修改‘教师所在学院’信息
	if(b_department=TRUE)
	{
		strSQL.Format(L"update TEACHER_INFO set DEPARTMENT = '%s' where TEA_ID='%s'",m_department,m_ID);
		m_database.ExecuteSQL(strSQL);
		flag=TRUE;
	}
	//修改‘教师籍贯’信息
	if(b_hometown=TRUE)
	{
		strSQL.Format(L"update TEACHER_INFO set HOMETOWN = '%s' where TEA_ID='%s'",m_hometown,m_ID);
		m_database.ExecuteSQL(strSQL);
		flag=TRUE;
	}
	//修改‘教师专业’信息
	if(b_major=TRUE)
	{
		strSQL.Format(L"update TEACHER_INFO set MAJOR = '%s' where TEA_ID='%s'",m_major,m_ID);
		m_database.ExecuteSQL(strSQL);
		flag=TRUE;
	}
	//修改‘教师其他说明’信息
	if(b_other=TRUE)
	{
		strSQL.Format(L"update TEACHER_INFO set DIRECTION = '%s' where TEA_ID='%s'",m_other,m_ID);
		m_database.ExecuteSQL(strSQL);
		flag=TRUE;
	}
	//修改‘教师联系电话’信息
	if(b_phone=TRUE)
	{
		strSQL.Format(L"update TEACHER_INFO set PHONE = '%s' where TEA_ID='%s'",m_phone,m_ID);
		m_database.ExecuteSQL(strSQL);
		flag=TRUE;
	}
	//修改‘教师民族’信息
	if(b_race=TRUE)
	{
		strSQL.Format(L"update TEACHER_INFO set RACE = '%s' where TEA_ID='%s'",m_race,m_ID);
		m_database.ExecuteSQL(strSQL);
		flag=TRUE;
	}
	//修改‘教师生日’信息
	if(b_birthday=TRUE)
	{
		CTime dtChosen;
		m_birthday.GetTime(dtChosen);
		strSQL.Format(L"update TEACHER_INFO set BIRTHDAY = '%d-%d-%d' where TEA_ID='%s'",dtChosen.GetYear(),dtChosen.GetMonth(),dtChosen.GetDay(),m_ID);
		m_database.ExecuteSQL(strSQL);
		flag=TRUE;
	}
	//修改‘教师职称’信息
	if(b_party=TRUE)
	{
		strSQL.Format(L"update TEACHER_INFO set TITLE = '%d' where TEA_ID='%s'",m_title,m_ID);
		m_database.ExecuteSQL(strSQL);
		flag=TRUE;
	}
	//修改‘教师政治面貌’信息
	if(b_party=TRUE)
	{
		strSQL.Format(L"update TEACHER_INFO set PARTY = '%d' where TEA_ID='%s'",m_party,m_ID);
		m_database.ExecuteSQL(strSQL);
		flag=TRUE;
	}
	//修改‘教师性别’信息
	if(b_sex=TRUE)
	{
		strSQL.Format(L"update TEACHER_INFO set SEX = '%d' where TEA_ID='%s'",m_sex,m_ID);
		m_database.ExecuteSQL(strSQL);
		flag=TRUE;
	}

	if(flag==TRUE)
		MessageBox(L"修改成功！");
	else
		MessageBox(L"无修改内容！",L"请仔细核对！");
}


void CTeacherInfo::OnDestroy()
{
	CFormView::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	// 使菜单中‘教师基本信息’项再次可用
	((CMainFrame *)AfxGetMainWnd())->m_bItemTeacherInfo=TRUE;
	// 清空‘教师基本信息’窗口指针
	((CMainFrame *)AfxGetMainWnd())->m_pTeacherInfo=NULL;
}


void CTeacherInfo::OnBnClickedButtonCancle()
{
	// TODO: 在此添加控件通知处理程序代码
	((CMainFrame *)AfxGetMainWnd())->m_pTeacherInfo->DestroyWindow();
}
