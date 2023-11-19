// TeacherInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ODBC.h"
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
	// ��ʼ����Ա����
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


// CTeacherInfo ���

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


// CTeacherInfo ��Ϣ�������


void CTeacherInfo::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	// �Զ���������
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit(FALSE);
	// ���ñ���
	GetParentFrame()->SetWindowText(L"��ʦ��Ϣ����");
	CenterWindow();
	// ��������
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
	// �õ�����ʦ���ա���Ϣ
	strSQL.Format(L"select BIRTHDAY from TEACHER_INFO where TEA_ID='%s'",m_ID);
	m_recordset.Open(CRecordset::forwardOnly,strSQL);
	m_recordset.GetFieldValue(L"BIRTHDAY",varValue);
	m_birthday.SetTime(COleDateTime(varValue.m_pdate->year,varValue.m_pdate->month,varValue.m_pdate->day,0,0,0));
	m_recordset.Close();
	// �õ�����ʦ��ͥסַ����Ϣ
	strSQL.Format(L"select ADDRESS from TEACHER_INFO where TEA_ID='%s'",m_ID);
	m_recordset.Open(CRecordset::forwardOnly,strSQL);
	m_recordset.GetFieldValue(L"ADDRESS",m_address);
	m_recordset.Close();
	// �õ�����ʦ����ѧԺ����Ϣ
	strSQL.Format(L"select DEPARTMENT from TEACHER_INFO where TEA_ID='%s'",m_ID);
	m_recordset.Open(CRecordset::forwardOnly,strSQL);
	m_recordset.GetFieldValue(L"DEPARTMENT",m_department);
	m_recordset.Close();
	// �õ�����ʦ���ᡱ��Ϣ
	strSQL.Format(L"select HOMETOWN from TEACHER_INFO where TEA_ID='%s'",m_ID);
	m_recordset.Open(CRecordset::forwardOnly,strSQL);
	m_recordset.GetFieldValue(L"HOMETOWN",m_hometown);
	m_recordset.Close();
	// �õ�����ʦרҵ����Ϣ
	strSQL.Format(L"select MAJOR from TEACHER_INFO where TEA_ID='%s'",m_ID);
	m_recordset.Open(CRecordset::forwardOnly,strSQL);
	m_recordset.GetFieldValue(L"MAJOR",m_major);
	m_recordset.Close();
	// �õ�����ʦ��������Ϣ
	strSQL.Format(L"select TEA_NAME from TEACHER_INFO where TEA_ID='%s'",m_ID);
	m_recordset.Open(CRecordset::forwardOnly,strSQL);
	m_recordset.GetFieldValue(L"TEA_NAME",m_name);
	m_recordset.Close();
	// �õ�����ʦ�š���Ϣ
	strSQL.Format(L"select TEA_ID from TEACHER_INFO where TEA_ID='%s'",m_ID);
	m_recordset.Open(CRecordset::forwardOnly,strSQL);
	m_recordset.GetFieldValue(L"TEA_ID",m_number);
	m_recordset.Close();
	// �õ�����ʦ����˵������Ϣ
	strSQL.Format(L"select DIRECTION from TEACHER_INFO where TEA_ID='%s'",m_ID);
	m_recordset.Open(CRecordset::forwardOnly,strSQL);
	m_recordset.GetFieldValue(L"DIRECTION",m_other);
	m_recordset.Close();
	// �õ�����ʦ��ϵ�绰����Ϣ
	strSQL.Format(L"select PHONE from TEACHER_INFO where TEA_ID='%s'",m_ID);
	m_recordset.Open(CRecordset::forwardOnly,strSQL);
	m_recordset.GetFieldValue(L"PHONE",m_phone);
	m_recordset.Close();
	// �õ�����ʦ���塱��Ϣ
	strSQL.Format(L"select RACE from TEACHER_INFO where TEA_ID='%s'",m_ID);
	m_recordset.Open(CRecordset::forwardOnly,strSQL);
	m_recordset.GetFieldValue(L"RACE",m_race);
	m_recordset.Close();
	// �õ�����ʦ�Ա���Ϣ
	strSQL.Format(L"select SEX from TEACHER_INFO where TEA_ID='%s'",m_ID);
	m_recordset.Open(CRecordset::forwardOnly,strSQL);
	m_recordset.GetFieldValue(L"SEX",varValue);
	m_sex=varValue.m_iVal;
	m_recordset.Close();
	// �õ�����ʦ������ò����Ϣ
	strSQL.Format(L"select PARTY from TEACHER_INFO where TEA_ID='%s'",m_ID);
	m_recordset.Open(CRecordset::forwardOnly,strSQL);
	m_recordset.GetFieldValue(L"PARTY",varValue);
	m_party=varValue.m_iVal;
	m_recordset.Close();
	// �õ�����ʦְ�ơ���Ϣ
	strSQL.Format(L"select TITLE from TEACHER_INFO where TEA_ID='%s'",m_ID);
	m_recordset.Open(CRecordset::forwardOnly,strSQL);
	m_recordset.GetFieldValue(L"TITLE",varValue);
	m_title=varValue.m_iVal;
	m_recordset.Close();
	// ���½�������
	UpdateData(FALSE);
}


void CTeacherInfo::OnCbnSelchangeComboId()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CTeacherInfo::OnCbnSelchangeComboSex()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�õ��Ա���Ͽ���ѡ�е���Ϣ
	m_sex=m_c_sex.GetCurSel();
	//��־����ʦ�Ա���Ϣ��Ķ�
	b_sex=TRUE;
}


void CTeacherInfo::OnEnChangeEditDepartment()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CFormView::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

//#1015

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//��־������ѧԺ����Ϣ��Ķ�
	b_department=TRUE;
}


void CTeacherInfo::OnEnChangeEditMajor()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CFormView::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

//#1015

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	b_major=TRUE;
}


void CTeacherInfo::OnCbnSelchangeComboTitle()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�õ�ְ����Ͽ���ѡ�е���Ϣ
	m_title=m_c_title.GetCurSel();
	//��־����ʦְ�ơ���Ϣ��Ķ�
	b_title=TRUE;
}


void CTeacherInfo::OnDtnDatetimechangeDatetimepickerBirthday(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	b_birthday=TRUE;
	*pResult = 0;
}


void CTeacherInfo::OnCbnSelchangeComboParty()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// �õ�������ò��Ͽ���ѡ�е���Ϣ
	m_party=m_c_party.GetCurSel();
	// ��־'��ʦ������ò'��Ϣ��Ķ�
	b_party=TRUE;
}


void CTeacherInfo::OnEnChangeEditRace()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CFormView::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

//#1015

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	// ��־����ʦ���塯��Ϣ��Ķ�
	b_race=TRUE;
}


void CTeacherInfo::OnEnChangeEditphone()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CFormView::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

//#1015

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	// ��־����ʦ��ϵ�绰����Ϣ��Ķ�
	b_phone=TRUE;
}


void CTeacherInfo::OnEnChangeEditHometown()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CFormView::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

//#1015

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	// ��־�����ᡯ��Ϣ��Ķ�
	b_hometown=TRUE;
}


void CTeacherInfo::OnEnChangeEditAddress()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CFormView::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

//#1015

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	// ��־����ʦ��ͥסַ����Ϣ��Ķ�
	b_address=TRUE;
}


void CTeacherInfo::OnEnChangeEditOther()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CFormView::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

//#1015

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	// ��־����ʦ����˵������Ϣ��Ķ�
	b_other=TRUE;
}


void CTeacherInfo::OnBnClickedButtonChange()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ��ʼ�����޸ı�־flagΪFALSE����ʾ�����޸�
	BOOL flag;
	flag=FALSE;
	// �õ��ؼ��е���Ϣ
	UpdateData();
	CString strSQL;

	//�޸ġ���ʦ��ͥסַ����Ϣ
	if(b_address=TRUE)
	{
		strSQL.Format(L"update TEACHER_INFO set ADDRESS = '%s' where TEA_ID='%s'",m_address,m_ID);
		m_database.ExecuteSQL(strSQL);
		flag=TRUE;
	}
	//�޸ġ���ʦ����ѧԺ����Ϣ
	if(b_department=TRUE)
	{
		strSQL.Format(L"update TEACHER_INFO set DEPARTMENT = '%s' where TEA_ID='%s'",m_department,m_ID);
		m_database.ExecuteSQL(strSQL);
		flag=TRUE;
	}
	//�޸ġ���ʦ���ᡯ��Ϣ
	if(b_hometown=TRUE)
	{
		strSQL.Format(L"update TEACHER_INFO set HOMETOWN = '%s' where TEA_ID='%s'",m_hometown,m_ID);
		m_database.ExecuteSQL(strSQL);
		flag=TRUE;
	}
	//�޸ġ���ʦרҵ����Ϣ
	if(b_major=TRUE)
	{
		strSQL.Format(L"update TEACHER_INFO set MAJOR = '%s' where TEA_ID='%s'",m_major,m_ID);
		m_database.ExecuteSQL(strSQL);
		flag=TRUE;
	}
	//�޸ġ���ʦ����˵������Ϣ
	if(b_other=TRUE)
	{
		strSQL.Format(L"update TEACHER_INFO set DIRECTION = '%s' where TEA_ID='%s'",m_other,m_ID);
		m_database.ExecuteSQL(strSQL);
		flag=TRUE;
	}
	//�޸ġ���ʦ��ϵ�绰����Ϣ
	if(b_phone=TRUE)
	{
		strSQL.Format(L"update TEACHER_INFO set PHONE = '%s' where TEA_ID='%s'",m_phone,m_ID);
		m_database.ExecuteSQL(strSQL);
		flag=TRUE;
	}
	//�޸ġ���ʦ���塯��Ϣ
	if(b_race=TRUE)
	{
		strSQL.Format(L"update TEACHER_INFO set RACE = '%s' where TEA_ID='%s'",m_race,m_ID);
		m_database.ExecuteSQL(strSQL);
		flag=TRUE;
	}
	//�޸ġ���ʦ���ա���Ϣ
	if(b_birthday=TRUE)
	{
		CTime dtChosen;
		m_birthday.GetTime(dtChosen);
		strSQL.Format(L"update TEACHER_INFO set BIRTHDAY = '%d-%d-%d' where TEA_ID='%s'",dtChosen.GetYear(),dtChosen.GetMonth(),dtChosen.GetDay(),m_ID);
		m_database.ExecuteSQL(strSQL);
		flag=TRUE;
	}
	//�޸ġ���ʦְ�ơ���Ϣ
	if(b_party=TRUE)
	{
		strSQL.Format(L"update TEACHER_INFO set TITLE = '%d' where TEA_ID='%s'",m_title,m_ID);
		m_database.ExecuteSQL(strSQL);
		flag=TRUE;
	}
	//�޸ġ���ʦ������ò����Ϣ
	if(b_party=TRUE)
	{
		strSQL.Format(L"update TEACHER_INFO set PARTY = '%d' where TEA_ID='%s'",m_party,m_ID);
		m_database.ExecuteSQL(strSQL);
		flag=TRUE;
	}
	//�޸ġ���ʦ�Ա���Ϣ
	if(b_sex=TRUE)
	{
		strSQL.Format(L"update TEACHER_INFO set SEX = '%d' where TEA_ID='%s'",m_sex,m_ID);
		m_database.ExecuteSQL(strSQL);
		flag=TRUE;
	}

	if(flag==TRUE)
		MessageBox(L"�޸ĳɹ���");
	else
		MessageBox(L"���޸����ݣ�",L"����ϸ�˶ԣ�");
}


void CTeacherInfo::OnDestroy()
{
	CFormView::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	// ʹ�˵��С���ʦ������Ϣ�����ٴο���
	((CMainFrame *)AfxGetMainWnd())->m_bItemTeacherInfo=TRUE;
	// ��ա���ʦ������Ϣ������ָ��
	((CMainFrame *)AfxGetMainWnd())->m_pTeacherInfo=NULL;
}


void CTeacherInfo::OnBnClickedButtonCancle()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	((CMainFrame *)AfxGetMainWnd())->m_pTeacherInfo->DestroyWindow();
}
