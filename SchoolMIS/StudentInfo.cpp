// StudentInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ODBC.h"
#include "StudentInfo.h"
/***********************by jiangxin***********************/
#include "MainFrm.h"
extern CDatabase m_database;
extern CString m_ID;
extern int m_type;
/***********************by jiangxin***********************/

// CStudentInfo

IMPLEMENT_DYNCREATE(CStudentInfo, CFormView)

CStudentInfo::CStudentInfo()
	: CFormView(CStudentInfo::IDD)
	, m_name(_T(""))
	, m_number(_T(""))
	, m_sex(0)
	, m_department(_T(""))
	, m_major(_T(""))
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
	b_starttime=FALSE;
/***********************by jiangxin***********************/
}

CStudentInfo::~CStudentInfo()
{
}

void CStudentInfo::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_name);
	DDX_Text(pDX, IDC_EDIT_ID, m_number);
	DDX_CBIndex(pDX, IDC_COMBO_SEX, m_sex);
	DDX_Control(pDX, IDC_COMBO_SEX, m_c_sex);
	DDX_Text(pDX, IDC_EDIT_DEPARTMENT, m_department);
	DDX_Text(pDX, IDC_EDIT_MAJOR, m_major);
	DDX_Control(pDX, IDC_DATETIMEPICKER_START, m_starttime);
	DDX_Control(pDX, IDC_DATETIMEPICKER_BIRTHDAY, m_birthday);
	DDX_CBIndex(pDX, IDC_COMBO_PARTY, m_party);
	DDX_Control(pDX, IDC_COMBO_PARTY, m_c_party);
	DDX_Text(pDX, IDC_EDIT_RACE, m_race);
	DDX_Text(pDX, IDC_EDIT_phone, m_phone);
	DDX_Text(pDX, IDC_EDIT_HOMETOWN, m_hometown);
	DDX_Text(pDX, IDC_EDIT_ADDRESS, m_address);
	DDX_Text(pDX, IDC_EDIT_OTHER, m_other);
}

BEGIN_MESSAGE_MAP(CStudentInfo, CFormView)
	ON_EN_CHANGE(IDC_EDIT_DEPARTMENT, &CStudentInfo::OnEnChangeEditDepartment)
	ON_EN_CHANGE(IDC_EDIT_MAJOR, &CStudentInfo::OnEnChangeEditMajor)
	ON_CBN_SELCHANGE(IDC_COMBO_SEX, &CStudentInfo::OnCbnSelchangeComboSex)
	ON_NOTIFY(DTN_CLOSEUP, IDC_DATETIMEPICKER_START, &CStudentInfo::OnDtnCloseupDatetimepickerStart)
	ON_NOTIFY(DTN_CLOSEUP, IDC_DATETIMEPICKER_BIRTHDAY, &CStudentInfo::OnDtnCloseupDatetimepickerBirthday)
	ON_CBN_SELCHANGE(IDC_COMBO_PARTY, &CStudentInfo::OnCbnSelchangeComboParty)
	ON_EN_CHANGE(IDC_EDIT_RACE, &CStudentInfo::OnEnChangeEditRace)
	ON_EN_CHANGE(IDC_EDIT_phone, &CStudentInfo::OnEnChangeEditphone)
	ON_EN_CHANGE(IDC_EDIT_HOMETOWN, &CStudentInfo::OnEnChangeEditHometown)
	ON_EN_CHANGE(IDC_EDIT_ADDRESS, &CStudentInfo::OnEnChangeEditAddress)
	ON_EN_CHANGE(IDC_EDIT_OTHER, &CStudentInfo::OnEnChangeEditOther)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, &CStudentInfo::OnBnClickedButtonChange)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_CANCLE, &CStudentInfo::OnBnClickedButtonCancle)
END_MESSAGE_MAP()


// CStudentInfo ���

#ifdef _DEBUG
void CStudentInfo::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CStudentInfo::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CStudentInfo ��Ϣ�������


void CStudentInfo::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	// �Զ���������
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit(FALSE);
	// ���ñ���
	GetParentFrame()->SetWindowText(L"ѧ������");
	CenterWindow();
	// ��������
	LOGFONT LogFont;
	GetFont()->GetLogFont(&LogFont);
	LogFont.lfHeight+=LogFont.lfHeight/2;
	LogFont.lfWidth+=LogFont.lfWidth;
	LoginFont.CreateFontIndirect(&LogFont);
	GetDlgItem(IDC_STATIC_STU_INFO)->SetFont(&LoginFont);
	initial();
}



void CStudentInfo::initial(void)
{
	CDBVariant varValue;
	CRecordset m_recordset(&m_database);
	CString strSQL;
	// �õ���ѧ�����ա���Ϣ
	strSQL.Format(L"select BIRTHDAY from STUDENT_INFO where STU_ID='%s'",m_ID);
	m_recordset.Open(CRecordset::forwardOnly,strSQL);
	m_recordset.GetFieldValue(L"BIRTHDAY",varValue);
	m_birthday.SetTime(COleDateTime(varValue.m_pdate->year,varValue.m_pdate->month,varValue.m_pdate->day,0,0,0));
	m_recordset.Close();
	// �õ���ѧ����ѧʱ�䡱��Ϣ
	strSQL.Format(L"select ENROLLMENT_TIME from STUDENT_INFO where STU_ID='%s'",m_ID);
	m_recordset.Open(CRecordset::forwardOnly,strSQL);
	m_recordset.GetFieldValue(L"ENROLLMENT_TIME",varValue);
	m_starttime.SetTime(COleDateTime(varValue.m_pdate->year,varValue.m_pdate->month,varValue.m_pdate->day,0,0,0));
	m_recordset.Close();
	// �õ���ѧ����ͥסַ����Ϣ
	strSQL.Format(L"select ADDRESS from STUDENT_INFO where STU_ID='%s'",m_ID);
	m_recordset.Open(CRecordset::forwardOnly,strSQL);
	m_recordset.GetFieldValue(L"ADDRESS",m_address);
	m_recordset.Close();
	// �õ���ѧ������ѧԺ����Ϣ
	strSQL.Format(L"select DEPARTMENT from STUDENT_INFO where STU_ID='%s'",m_ID);
	m_recordset.Open(CRecordset::forwardOnly,strSQL);
	m_recordset.GetFieldValue(L"DEPARTMENT",m_department);
	m_recordset.Close();
	// �õ���ѧ�����ᡱ��Ϣ
	strSQL.Format(L"select HOMETOWN from STUDENT_INFO where STU_ID='%s'",m_ID);
	m_recordset.Open(CRecordset::forwardOnly,strSQL);
	m_recordset.GetFieldValue(L"HOMETOWN",m_hometown);
	m_recordset.Close();
	// �õ���ѧ��רҵ����Ϣ
	strSQL.Format(L"select MAJOR from STUDENT_INFO where STU_ID='%s'",m_ID);
	m_recordset.Open(CRecordset::forwardOnly,strSQL);
	m_recordset.GetFieldValue(L"MAJOR",m_major);
	m_recordset.Close();
	// �õ���ѧ����������Ϣ
	strSQL.Format(L"select STU_NAME from STUDENT_INFO where STU_ID='%s'",m_ID);
	m_recordset.Open(CRecordset::forwardOnly,strSQL);
	m_recordset.GetFieldValue(L"STU_NAME",m_name);
	m_recordset.Close();
	// �õ���ѧ��ѧ�š���Ϣ
	strSQL.Format(L"select STU_ID from STUDENT_INFO where STU_ID='%s'",m_ID);
	m_recordset.Open(CRecordset::forwardOnly,strSQL);
	m_recordset.GetFieldValue(L"STU_ID",m_number);
	m_recordset.Close();
	// �õ���ѧ������˵������Ϣ
	strSQL.Format(L"select DIRECTION from STUDENT_INFO where STU_ID='%s'",m_ID);
	m_recordset.Open(CRecordset::forwardOnly,strSQL);
	m_recordset.GetFieldValue(L"DIRECTION",m_other);
	m_recordset.Close();
	// �õ���ѧ����ϵ�绰����Ϣ
	strSQL.Format(L"select PHONE from STUDENT_INFO where STU_ID='%s'",m_ID);
	m_recordset.Open(CRecordset::forwardOnly,strSQL);
	m_recordset.GetFieldValue(L"PHONE",m_phone);
	m_recordset.Close();
	// �õ���ѧ�����塱��Ϣ
	strSQL.Format(L"select RACE from STUDENT_INFO where STU_ID='%s'",m_ID);
	m_recordset.Open(CRecordset::forwardOnly,strSQL);
	m_recordset.GetFieldValue(L"RACE",m_race);
	m_recordset.Close();
	// �õ���ѧ���Ա���Ϣ
	strSQL.Format(L"select SEX from STUDENT_INFO where STU_ID='%s'",m_ID);
	m_recordset.Open(CRecordset::forwardOnly,strSQL);
	m_recordset.GetFieldValue(L"SEX",varValue);
	m_sex=varValue.m_iVal;
	m_recordset.Close();
	// �õ���ѧ��������ò����Ϣ
	strSQL.Format(L"select PARTY from STUDENT_INFO where STU_ID='%s'",m_ID);
	m_recordset.Open(CRecordset::forwardOnly,strSQL);
	m_recordset.GetFieldValue(L"PARTY",varValue);
	m_party=varValue.m_iVal;
	m_recordset.Close();
	// ���½�������
	UpdateData(FALSE);
}


void CStudentInfo::OnEnChangeEditDepartment()
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


void CStudentInfo::OnEnChangeEditMajor()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CFormView::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

//#1015

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	b_major=TRUE;
}


void CStudentInfo::OnCbnSelchangeComboSex()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�õ��Ա���Ͽ���ѡ�е���Ϣ
	m_sex=m_c_sex.GetCurSel();
	//��־��ѧ���Ա���Ϣ��Ķ�
	b_sex=TRUE;
}


void CStudentInfo::OnDtnCloseupDatetimepickerStart(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);//
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ��־'��ѧʱ��'��Ϣ��Ķ�
	b_starttime=TRUE;
	*pResult = 0;
}


void CStudentInfo::OnDtnCloseupDatetimepickerBirthday(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);//
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ��־'ѧ������'��Ϣ��Ķ�
	b_birthday=TRUE;
	*pResult = 0;
}


void CStudentInfo::OnCbnSelchangeComboParty()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// �õ�������ò��Ͽ���ѡ�е���Ϣ
	m_party=m_c_party.GetCurSel();
	// ��־'ѧ��������ò'��Ϣ��Ķ�
	b_party=TRUE;
}


void CStudentInfo::OnEnChangeEditRace()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CFormView::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

//#1015

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	// ��־��ѧ�����塯��Ϣ��Ķ�
	b_race=TRUE;
}


void CStudentInfo::OnEnChangeEditphone()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CFormView::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

//#1015

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	// ��־��ѧ����ϵ�绰����Ϣ��Ķ�
	b_phone=TRUE;
}


void CStudentInfo::OnEnChangeEditHometown()
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


void CStudentInfo::OnEnChangeEditAddress()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CFormView::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

//#1015

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	// ��־��ѧ����ͥסַ����Ϣ��Ķ�
	b_address=TRUE;
}


void CStudentInfo::OnEnChangeEditOther()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CFormView::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

//#1015

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	// ��־��ѧ������˵������Ϣ��Ķ�
	b_other=TRUE;
}


void CStudentInfo::OnBnClickedButtonChange()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ��ʼ�����޸ı�־flagΪFALSE����ʾ�����޸�
	BOOL flag;
	flag=FALSE;
	// �õ��ؼ��е���Ϣ
	UpdateData();
	CString strSQL;

	//�޸ġ�ѧ����ͥסַ����Ϣ
	if(b_address=TRUE)
	{
		strSQL.Format(L"update STUDENT_INFO set ADDRESS = '%s' where STU_ID='%s'",m_address,m_ID);
		m_database.ExecuteSQL(strSQL);
		flag=TRUE;
	}
	//�޸ġ�ѧ������ѧԺ����Ϣ
	if(b_department=TRUE)
	{
		strSQL.Format(L"update STUDENT_INFO set DEPARTMENT = '%s' where STU_ID='%s'",m_department,m_ID);
		m_database.ExecuteSQL(strSQL);
		flag=TRUE;
	}
	//�޸ġ�ѧ�����ᡯ��Ϣ
	if(b_hometown=TRUE)
	{
		strSQL.Format(L"update STUDENT_INFO set HOMETOWN = '%s' where STU_ID='%s'",m_hometown,m_ID);
		m_database.ExecuteSQL(strSQL);
		flag=TRUE;
	}
	//�޸ġ�ѧ��רҵ����Ϣ
	if(b_major=TRUE)
	{
		strSQL.Format(L"update STUDENT_INFO set MAJOR = '%s' where STU_ID='%s'",m_major,m_ID);
		m_database.ExecuteSQL(strSQL);
		flag=TRUE;
	}
	//�޸ġ�ѧ������˵������Ϣ
	if(b_other=TRUE)
	{
		strSQL.Format(L"update STUDENT_INFO set DIRECTION = '%s' where STU_ID='%s'",m_other,m_ID);
		m_database.ExecuteSQL(strSQL);
		flag=TRUE;
	}
	//�޸ġ�ѧ����ϵ�绰����Ϣ
	if(b_phone=TRUE)
	{
		strSQL.Format(L"update STUDENT_INFO set PHONE = '%s' where STU_ID='%s'",m_phone,m_ID);
		m_database.ExecuteSQL(strSQL);
		flag=TRUE;
	}
	//�޸ġ�ѧ�����塯��Ϣ
	if(b_race=TRUE)
	{
		strSQL.Format(L"update STUDENT_INFO set RACE = '%s' where STU_ID='%s'",m_race,m_ID);
		m_database.ExecuteSQL(strSQL);
		flag=TRUE;
	}
	//�޸ġ�ѧ�����ա���Ϣ
	if(b_birthday=TRUE)
	{
		CTime dtChosen;
		m_birthday.GetTime(dtChosen);
		strSQL.Format(L"update STUDENT_INFO set BIRTHDAY = \'%d-%d-%d\' where STU_ID='%s'",dtChosen.GetYear(),dtChosen.GetMonth(),dtChosen.GetDay(),m_ID);
		m_database.ExecuteSQL(strSQL);
		flag=TRUE;
	}
	//�޸ġ�ѧ����ѧʱ�䡯��Ϣ
	if(b_starttime=TRUE)
	{
		CTime dtChosen;
		m_starttime.GetTime(dtChosen);
		strSQL.Format(L"update STUDENT_INFO set ENROLLMENT_TIME = \'%d-%d-%d\' where STU_ID='%s'",dtChosen.GetYear(),dtChosen.GetMonth(),dtChosen.GetDay(),m_ID);
		m_database.ExecuteSQL(strSQL);
		flag=TRUE;
	}
	//�޸ġ�ѧ��������ò����Ϣ
	if(b_party=TRUE)
	{
		strSQL.Format(L"update STUDENT_INFO set PARTY = '%d' where STU_ID='%s'",m_party,m_ID);
		m_database.ExecuteSQL(strSQL);
		flag=TRUE;
	}
	//�޸ġ�ѧ���Ա���Ϣ
	if(b_sex=TRUE)
	{
		strSQL.Format(L"update STUDENT_INFO set SEX = '%d' where STU_ID='%s'",m_sex,m_ID);
		m_database.ExecuteSQL(strSQL);
		flag=TRUE;
	}

	if(flag==TRUE)
		MessageBox(L"�޸ĳɹ���");
	else
		MessageBox(L"���޸����ݣ�",L"����ϸ�˶ԣ�");
}


void CStudentInfo::OnDestroy()
{
	CFormView::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	// ʹ�˵��С�ѧ��������Ϣ�����ٴο���
	((CMainFrame *)AfxGetMainWnd())->m_bItemStudentInfo=TRUE;
	// ��ա�ѧ��������Ϣ������ָ��
	((CMainFrame *)AfxGetMainWnd())->m_pStudentInfo=NULL;
}


void CStudentInfo::OnBnClickedButtonCancle()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ɾ���˴���
	((CMainFrame *)AfxGetMainWnd())->m_pStudentInfo->DestroyWindow();
}
