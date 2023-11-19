// DelCourse.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ODBC.h"
#include "DelCourse.h"
/***********************by jiangxin***********************/
#include "MainFrm.h"
extern CDatabase m_database;
extern CString m_ID;
extern int m_type;
/***********************by jiangxin***********************/


// CDelCourse

IMPLEMENT_DYNCREATE(CDelCourse, CFormView)

CDelCourse::CDelCourse()
	: CFormView(CDelCourse::IDD)
	, m_courseID(_T(""))
	, m_course_name(_T(""))
	, m_course_time(_T(""))
	, m_teacher(_T(""))
	, m_start(_T(""))
	, m_end(_T(""))
	, m_cent(_T(""))
	, m_require(_T(""))
	, m_instruction(_T(""))
{

}

CDelCourse::~CDelCourse()
{
}

void CDelCourse::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_COURSE_ID, m_courseID);
	DDX_Text(pDX, IDC_EDIT_COURSE_NAME, m_course_name);
	DDX_Text(pDX, IDC_EDIT_TIME, m_course_time);
	DDX_Text(pDX, IDC_EDIT_TEACHER, m_teacher);
	DDX_Text(pDX, IDC_EDIT_START, m_start);
	DDX_Text(pDX, IDC_EDIT_END, m_end);
	DDX_Text(pDX, IDC_EDIT_CENT, m_cent);
	DDX_Text(pDX, IDC_EDIT_REQUIRE, m_require);
	DDX_Text(pDX, IDC_EDIT_INSTRUCTION, m_instruction);
	DDX_Control(pDX, IDC_LIST_COURSE, m_course);
}

BEGIN_MESSAGE_MAP(CDelCourse, CFormView)
	ON_NOTIFY(NM_CLICK, IDC_LIST_COURSE, &CDelCourse::OnNMClickListCourse)
	ON_BN_CLICKED(IDC_BUTTON_CHOICE, &CDelCourse::OnBnClickedButtonChoice)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_CANCLE, &CDelCourse::OnBnClickedButtonCancle)
END_MESSAGE_MAP()


// CDelCourse ���

#ifdef _DEBUG
void CDelCourse::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDelCourse::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDelCourse ��Ϣ�������


void CDelCourse::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	// �Զ���������
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit(FALSE);
	// ���ñ���
	GetParentFrame()->SetWindowText(L"ɾ����ѡ�γ���ϵͳ");
	CenterWindow();
	// ��������
	LOGFONT LogFont;
	GetFont()->GetLogFont(&LogFont);
	LogFont.lfHeight+=LogFont.lfHeight/2;
	LogFont.lfWidth+=LogFont.lfWidth/2;
	Font.CreateFontIndirect(&LogFont);
	GetDlgItem(IDC_STATIC_DEL_COURSE)->SetFont(&Font);
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


void CDelCourse::initial(void)
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


void CDelCourse::settext(int index)
{
	// ��ȡ�б�ؼ��и����ֶ�ֵ��䵽��Ӧ�ı༭����
	m_courseID=m_course.GetItemText(index,0);
	m_course_name=m_course.GetItemText(index,1);
	m_course_time=m_course.GetItemText(index,2);
	m_start=m_course.GetItemText(index,3);
	m_end=m_course.GetItemText(index,4);
	m_cent=m_course.GetItemText(index,5);
	m_teacher=m_course.GetItemText(index,6);
	m_require=m_course.GetItemText(index,7);
	m_instruction=m_course.GetItemText(index,8);

	UpdateData(FALSE);
}


void CDelCourse::OnNMClickListCourse(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ���ѡ�еĿγ̱�ʶ��Ϣ
	int i=m_course.GetSelectionMark();
	// ������ʾ����������ϸ��ʾ
	settext(i);
	*pResult = 0;
}


void CDelCourse::OnBnClickedButtonChoice()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// �õ��ؼ��е���Ϣ
	UpdateData(TRUE);
	CRecordset m_recordset(&m_database);
	CString strSQL;
	// �ж��û�����
	if(m_type==1)
	{
		strSQL.Format(L"delete from COURSE_SCORE where COURSE_ID='%s'",m_courseID);
		m_database.ExecuteSQL(strSQL);
		MessageBox(L"��ɾ�����ſγ̣�",L"ɾ���γ�",MB_OK);
	}
	else if(m_type=2)
	{
		strSQL.Format(L"update COURSE set COURSE_TEACHER='' where COURSE_ID='%s'",m_courseID);
		m_database.ExecuteSQL(strSQL);
		MessageBox(L"��ɾ�����ſγ̣�",L"ɾ���γ�",MB_OK);
	}
	initial();
}


void CDelCourse::OnDestroy()
{
	CFormView::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	// ʹ�˵��С�������Ϣ�������ٴο���
	((CMainFrame *)AfxGetMainWnd())->m_bItemDelCourse=TRUE;
	// ��ա�������Ϣ��������ָ��
	((CMainFrame *)AfxGetMainWnd())->m_pDelCourse=NULL;
}


void CDelCourse::OnBnClickedButtonCancle()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ɾ���˴���
	((CMainFrame *)AfxGetMainWnd())->m_pDelCourse->DestroyWindow();
}
