// CourseInfoManager.cpp : ʵ���ļ�
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


// CCourseInfoManager ���

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


// CCourseInfoManager ��Ϣ�������


void CCourseInfoManager::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	// �Զ���������
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit(FALSE);
	// ���ñ���
	GetParentFrame()->SetWindowText(L"�γ���Ϣ��ϵͳ");
	CenterWindow();
	// ��������
	LOGFONT LogFont;
	GetFont()->GetLogFont(&LogFont);
	LogFont.lfHeight+=LogFont.lfHeight/2;
	LogFont.lfWidth+=LogFont.lfWidth/2;
	Font.CreateFontIndirect(&LogFont);
	GetDlgItem(IDC_STATIC_COURSE)->SetFont(&Font);
	// ��ʼ���б�ؼ�
	m_course.InsertColumn(0,L"�γ̱��");
	m_course.InsertColumn(1,L"�γ�����");
	m_course.InsertColumn(2,L"�Ͽ�ʱ��");
	m_course.InsertColumn(3,L"��������");
	m_course.InsertColumn(4,L"�������");
	m_course.InsertColumn(5,L"�γ�ѧ��");
	m_course.InsertColumn(6,L"�ڿν�ʦ");
	m_course.InsertColumn(7,L"ѡ��Ҫ��");
	m_course.InsertColumn(8,L"�γ̼��");

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
		// ���ַ������д���
		m_recordset.GetFieldValue(temp,str);
		m_course.InsertItem(i,str);

		m_recordset.GetFieldValue(1,str);
		m_course.SetItemText(i,1,str);
		
		m_recordset.GetFieldValue(2,str);
		m_course.SetItemText(i,2,str);

		// ���������ͽ��д���
		m_recordset.GetFieldValue(3,varValue);

		buf.Format(L"%d-%d-%d",varValue.m_pdate->year,varValue.m_pdate->month,varValue.m_pdate->day);
		m_course.SetItemText(i,3,buf);

		m_recordset.GetFieldValue(4,varValue);

		buf.Format(L"%d-%d-%d",varValue.m_pdate->year,varValue.m_pdate->month,varValue.m_pdate->day);
		m_course.SetItemText(i,4,buf);

		// ���������ݽ��д���
		m_recordset.GetFieldValue(5,varValue);
		buf.Format(L"%d",varValue.m_iVal);
		m_course.SetItemText(i,5,buf);

		// ���ַ������д���
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
	
	// ʹiָ��γ��б�ĵ�һ��
	i=0;
	// �ӿγ��б���ѡ���Ӧ��Ϣ��䵽��Ӧ��Ԫ
	settext(0);
	UpdateData(FALSE);
}


void CCourseInfoManager::settext(int index)
{
	// ��ȡ�б�ؼ��и����ֶ�ֵ��䵽��Ӧ�ı༭����
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ���ѡ�еĿγ̱�ʶ��Ϣ
	int i=m_course.GetSelectionMark();
	// ������ʾ����������ϸ��ʾ
	settext(i);
	*pResult = 0;
}


void CCourseInfoManager::OnBnClickedButtonAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	// ��ȡʱ����Ϣ

	m_C_start.GetTime(m_start);
	m_C_end.GetTime(m_end);
	int cent=_ttoi(m_cent);
	// �����Ϣ������
	if(m_courseID.GetLength()==0)
		MessageBox(L"�γ̺Ų���Ϊ�գ�");
	else if(m_course_name.GetLength()==0)
		MessageBox(L"�γ�������Ϊ�գ�");
	else if(m_course_time.GetLength()==0)
		MessageBox(L"�Ͽ�ʱ�䲻��Ϊ�գ�");
	else if(m_cent.GetLength()==0)
		MessageBox(L"ѧ�ֲ���Ϊ�գ�");
	else if(m_teacher.GetLength()==0)
		MessageBox(L"��ʦ����Ϊ�գ�");
	else if(m_require.GetLength()==0)
		MessageBox(L"�γ�Ҫ����Ϊ�գ�");
	else if(m_instruction.GetLength()==0)
		MessageBox(L"�γ̽��ܲ���Ϊ�գ�");
	else
	{
		// �����ݿ�����ӿγ���Ϣ
		CRecordset m_recordset(&m_database);
		CString strSQL;
		strSQL.Format(L"select * from COURSE where COURSE_ID='%s'",m_courseID);
		m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL);
		if(m_recordset.GetRecordCount()==0)
		{
			strSQL.Format(L"insert into COURSE (COURSE_ID,COURSE_NAME,COURSE_TIME,START_DATE,END_DATE,CENT,COURSE_TEACHER,REQUIRE,INSTRUCTION) values(\'%s\',\'%s\',\'%s\',\'%d-%d-%d\',\'%d-%d-%d\',\'%d\',\'%s\',\'%s\',\'%s\')",m_courseID,m_course_name,m_course_time,m_start.GetYear(),m_start.GetMonth(),m_start.GetDay(),m_end.GetYear(),m_end.GetMonth(),m_end.GetDay(),cent,m_teacher,m_require,m_instruction);
			m_database.ExecuteSQL(strSQL);
			MessageBox(L"�Ѿ��ɹ���ӿγ���Ϣ��");
		}
		else
		{
			MessageBox(L"�˿γ���Ϣ�Ѵ��ڣ���˶ԣ�");
		}
		initial();
	}
}


void CCourseInfoManager::OnBnClickedButtonDel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CRecordset m_recordset(&m_database);
	CString strSQL;
	strSQL.Format(L"select * from COURSE where COURSE_ID='%s'",m_courseID);
	m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL);
	// ���ݿ����޴˼�¼
	if(m_recordset.GetRecordCount()==0)
	{
		MessageBox(L"�޴���Ϣ����˶ԣ�");
	}
	else
	{
		strSQL.Format(L"delete from COURSE where COURSE_ID='%s'",m_courseID);
		m_database.ExecuteSQL(strSQL);
		MessageBox(L"�ѳɹ�ɾ���ÿγ���Ϣ��");
		CCourseInfoManager::OnBnClickedButtonFresh();
	}
	initial();
}


void CCourseInfoManager::OnBnClickedButtonFresh()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//���ø��ؼ�Ϊ��ֵ
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	// ��ȡʱ����Ϣ
	m_C_start.GetTime(m_start);
	m_C_end.GetTime(m_end);
	int cent=_ttoi(m_cent);
	// �����Ϣ������
	if(m_courseID.GetLength()==0)
		MessageBox(L"�γ̺Ų���Ϊ�գ�");
	else if(m_course_name.GetLength()==0)
		MessageBox(L"�γ�������Ϊ�գ�");
	else if(m_course_time.GetLength()==0)
		MessageBox(L"�Ͽ�ʱ�䲻��Ϊ�գ�");
	else if(m_cent.GetLength()==0)
		MessageBox(L"ѧ�ֲ���Ϊ�գ�");
	else if(m_teacher.GetLength()==0)
		MessageBox(L"��ʦ����Ϊ�գ�");
	else if(m_require.GetLength()==0)
		MessageBox(L"�γ�Ҫ����Ϊ�գ�");
	else if(m_instruction.GetLength()==0)
		MessageBox(L"�γ̽��ܲ���Ϊ�գ�");
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
			MessageBox(L"�Ѿ��ɹ����¿γ���Ϣ��");
		}
		else
		{
			MessageBox(L"�޴���Ϣ����˶ԣ�");
		}
		initial();
	}
}


void CCourseInfoManager::OnDestroy()
{
	CFormView::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	// ʹ�˵��С�������Ϣ�������ٴο���
	((CMainFrame *)AfxGetMainWnd())->m_bItemCourseInfoManager=TRUE;
	// ��ա�������Ϣ��������ָ��
	((CMainFrame *)AfxGetMainWnd())->m_pCourseInfoManager=NULL;
}
