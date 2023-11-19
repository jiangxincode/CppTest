// InfoManager.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ODBC.h"
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


// CInfoManager ���

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


// CInfoManager ��Ϣ�������


void CInfoManager::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	// ��������
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit(FALSE);
	// ���ñ���
	GetParentFrame()->SetWindowText(L"������Ϣ����");
	// ����ѧ���б�ؼ�
	m_student.InsertColumn(0,L"ѧ��");
	m_student.InsertColumn(1,L"����");

	RECT rect;
	m_student.GetWindowRect(&rect);
	int width=rect.right-rect.left;
	m_student.SetColumnWidth(0,width/2);
	m_student.SetColumnWidth(1,width/2);

	m_student.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	// ���ý�ʦ�б�ؼ�
	m_teacher.InsertColumn(0,L"��ʦ���");
	m_teacher.InsertColumn(1,L"����");

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

	// ȡ��ѧ����Ϣ
	i=0;
	m_student.DeleteAllItems();
	strSQL.Format(L"select * from STUDENT_INFO");
	m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL);
	if(m_recordset.GetRecordCount()!=0)
		m_recordset.MoveFirst();
	while(!m_recordset.IsEOF())
	{
		int t=0;
		// ���ַ������д���
		m_recordset.GetFieldValue(t,temp);
		m_student.InsertItem(i,temp);

		m_recordset.GetFieldValue(1,temp);
		m_student.SetItemText(i,1,temp);

		m_recordset.MoveNext();
		i++;
	}
	m_recordset.Close();
	// ȡ�ý�ʦ��Ϣ
	i=0;
	m_teacher.DeleteAllItems();
	strSQL.Format(L"select * from TEACHER_INFO");
	m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL);
	if(m_recordset.GetRecordCount()!=0)
		m_recordset.MoveFirst();
	while(!m_recordset.IsEOF())
	{
		int t=0;
		// ���ַ������д���
		m_recordset.GetFieldValue(t,temp);
		m_teacher.InsertItem(i,temp);

		m_recordset.GetFieldValue(1,temp);
		m_teacher.SetItemText(i,1,temp);

		m_recordset.MoveNext();
		i++;
	}
	m_recordset.Close();

	// ʹiָ��γ��б��еĵ�һ��
	i=0;
	// ���б���ѡ���Ӧ��Ϣ��䵽��Ӧ��Ԫ
	settext_student(0);
	settext_teacher(0);
}


void CInfoManager::settext_student(int index)
{
	// ��ʾѧ����Ϣ
	m_student_number=m_student.GetItemText(index,0);
	m_student_name=m_student.GetItemText(index,1);
	UpdateData(FALSE);
}


void CInfoManager::settext_teacher(int index)
{
	// ��ʾ��ʦ��Ϣ
	m_teacher_number=m_teacher.GetItemText(index,0);
	m_teacher_name=m_teacher.GetItemText(index,1);
	UpdateData(FALSE);
}


void CInfoManager::OnNMClickStudent(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ��ȡѡ�е�ѧ����Ϣ��־
	int i=m_student.GetSelectionMark();
	// ������ʾ����������ϸ��ʾ
	settext_student(i);
	*pResult = 0;
}


void CInfoManager::OnNMClickTeacher(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ��ȡѡ�еĽ�ʦ��Ϣ��־
	int i=m_teacher.GetSelectionMark();
	// ������ʾ����������ϸ��ʾ
	settext_teacher(i);
	*pResult = 0;
}


void CInfoManager::OnBnClickedStudentAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ��ȡ�༭���е���Ϣ
	UpdateData(TRUE);
	// �����Ϣ�Ƿ�����
	if(m_student_name.GetLength()==0)
		MessageBox(L"ѧ����������Ϊ�գ�");
	else if(m_student_number.GetLength()==0)
		MessageBox(L"ѧ��ѧ�Ų���Ϊ��1");
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
			/* �˴���Ϊ�����ݿ����
			strSQL.Format(L"insert into USERS(USER_ID,USER_PASSWORD,USER_TYPE) values('%s','%s','1')"
				,m_student_number,m_student_number);
			m_database.ExecuteSQL(strSQL);
			*/
			MessageBox(L"�ѳɹ����ѧ����Ϣ��");
		}
		else
		{
			MessageBox(L"��ѧ����Ϣ�Ѵ��ڣ���˶ԣ�");
		}
		initial();
	}
}


void CInfoManager::OnBnClickedStudentDel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CRecordset m_recordset(&m_database);
	CString strSQL;
	strSQL.Format(L"select * from STUDENT_INFO where STU_ID='%s'",m_student_number);
	m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL);
	if(m_recordset.GetRecordCount()==0)
	{
		MessageBox(L"�޴���Ϣ����˶ԣ�");
	}
	else
	{
		strSQL.Format(L"delete from STUDENT_INFO where STU_ID='%s'",m_student_number);
		m_database.ExecuteSQL(strSQL);
		/* �˴���Ϊ�����ݿ����
		strSQL.Format(L"delete from USERS where USER_ID='%s'",m_student_number);
		m_database.ExecuteSQL(strSQL);
		*/
		MessageBox(L"�ѳɹ�ɾ��ѧ����Ϣ��");
	}
	initial();
}


void CInfoManager::OnBnClickedStudentFresh()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ���ñ༭��Ϊ��
	m_student_name=L"";
	m_student_number=L"";
	UpdateData(FALSE);
}


void CInfoManager::OnBnClickedTeacherAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ��ȡ�༭���е���Ϣ
	UpdateData(TRUE);
	// �����Ϣ�Ƿ�����
	if(m_teacher_name.GetLength()==0)
		MessageBox(L"��ʦ��������Ϊ�գ�");
	else if(m_teacher_number.GetLength()==0)
		MessageBox(L"��ʦ��Ų���Ϊ��1");
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
			/* �˴���Ϊ�����ݿ����
			strSQL.Format(L"insert into USERS(USER_ID,USER_PASSWORD,USER_TYPE) values('%s','%s',2)",m_teacher_number,m_teacher_number);
			m_database.ExecuteSQL(strSQL);
			*/
			MessageBox(L"�ѳɹ���ӽ�ʦ��Ϣ��");
		}
		else
		{
			MessageBox(L"�˽�ʦ��Ϣ�Ѵ��ڣ���˶ԣ�");
		}
		initial();
	}
}


void CInfoManager::OnBnClickedTeacherDel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CRecordset m_recordset(&m_database);
	CString strSQL;
	strSQL.Format(L"select * from TEACHER_INFO where TEA_ID='%s'",m_teacher_number);
	m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL);
	if(m_recordset.GetRecordCount()==0)
	{
		MessageBox(L"�޴���Ϣ����˶ԣ�");
	}
	else
	{
		strSQL.Format(L"delete from TEACHER_INFO where TEA_ID='%s'",m_teacher_number);
		m_database.ExecuteSQL(strSQL);
		/* �˴���Ϊ�����ݿ����
		strSQL.Format(L"delete from USERS where USER_ID='%s'",m_teacher_number);
		m_database.ExecuteSQL(strSQL);
		*/
		MessageBox(L"�ѳɹ�ɾ����ʦ��Ϣ��");
	}
	initial();
}


void CInfoManager::OnBnClickedTeacherFresh()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ���ñ༭��Ϊ��
	m_teacher_name=L"";
	m_teacher_number=L"";
	UpdateData(FALSE);
}


void CInfoManager::OnDestroy()
{
	CFormView::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	// ʹ�˵��С�������Ϣ�������ٴο���
	((CMainFrame *)AfxGetMainWnd())->m_bItemInfoManager=TRUE;
	// ��ա�������Ϣ��������ָ��
	((CMainFrame *)AfxGetMainWnd())->m_pInfoManager=NULL;
}
