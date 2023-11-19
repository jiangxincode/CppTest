// CourseListManager.cpp : ʵ���ļ�
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


// CCourseListManager ���

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


// CCourseListManager ��Ϣ�������


void CCourseListManager::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	// �Զ���������
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit(FALSE);
	// ���ñ���
	GetParentFrame()->SetWindowText(L"�α���Ϣ��ϵͳ");
	CenterWindow();
	// ��������
	LOGFONT LogFont;
	GetFont()->GetLogFont(&LogFont);
	LogFont.lfHeight+=LogFont.lfHeight/2;
	LogFont.lfWidth+=LogFont.lfWidth/2;
	Font.CreateFontIndirect(&LogFont);
	GetDlgItem(IDC_STATIC_COURSE_LIST)->SetFont(&Font);
	// �����б�ؼ�
	m_course_list.InsertColumn(0,L"�γ̱��");
	m_course_list.InsertColumn(1,L"�γ�����");
	m_course_list.InsertColumn(2,L"�༶��");
	m_course_list.InsertColumn(3,L"��ʦ");
	m_course_list.InsertColumn(4,L"�Ͽ�ʱ��");
	m_course_list.InsertColumn(5,L"�Ͽ�ʱ��");
	m_course_list.InsertColumn(6,L"��ѧ¥��");
	m_course_list.InsertColumn(7,L"��ʦ��");

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
		// ���ַ������д���
		m_recordset.GetFieldValue(temp,str);
		m_course_list.InsertItem(i,str);

		m_recordset.GetFieldValue(1,str);
		m_course_list.SetItemText(i,1,str);
		
		m_recordset.GetFieldValue(2,str);
		m_course_list.SetItemText(i,2,str);

		m_recordset.GetFieldValue(3,str);
		m_course_list.SetItemText(i,3,str);

		// �����ѡ����д���
		m_recordset.GetFieldValue(4,varValue);
		switch (varValue.m_iVal)
		{
		case 0:
			m_course_list.SetItemText(i,4,L"����һ");
			break;
		case 1:
			m_course_list.SetItemText(i,4,L"���ڶ�");
			break;
		case 2:
			m_course_list.SetItemText(i,4,L"������");
			break;
		case 3:
			m_course_list.SetItemText(i,4,L"������");
			break;
		case 4:
			m_course_list.SetItemText(i,4,L"������");
			break;
		case 5:
			m_course_list.SetItemText(i,4,L"������");
			break;
		case 6:
			m_course_list.SetItemText(i,4,L"������");
			break;
		default:
			break;
		}

		// ���ַ������д���
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
	// ʹiָ��γ��б�ĵ�һ��
	i=0;
	// �ӿγ��б���ѡ���Ӧ��Ϣ��䵽��Ӧ��Ԫ
	settext(0);
	UpdateData(FALSE);
}


void CCourseListManager::settext(int index)
{
	// ��ȡ�б�ؼ��и����ֶ�ֵ��䵽��Ӧ�ı༭����
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	int m_i_weekday=m_C_weekday.GetCurSel();
	// �����Ϣ������
	if(m_courseID.GetLength()==0)
		MessageBox(L"�γ̺Ų���Ϊ�գ�");
	else if(m_course_name.GetLength()==0)
		MessageBox(L"�γ�������Ϊ�գ�");
	else if(m_class.GetLength()==0)
		MessageBox(L"�༶����Ϊ�գ�");
	else if(m_dayhour.GetLength()==0)
		MessageBox(L"�Ͽ�ʱ�䲻��Ϊ�գ�");
	else if(m_teacher.GetLength()==0)
		MessageBox(L"��ʦ����Ϊ�գ�");
	else if(m_building.GetLength()==0)
		MessageBox(L"��ѧ¥�Ų���Ϊ�գ�");
	else if(m_room.GetLength()==0)
		MessageBox(L"���ұ�Ų���Ϊ�գ�");
	else
	{
		// �����ݿ�����ӿγ���Ϣ
		CRecordset m_recordset(&m_database);
		CString strSQL;
		strSQL.Format(L"select * from COURSE_LIST where COURSE_ID='%s'",m_courseID);
		m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL);
		if(m_recordset.GetRecordCount()==0)
		{
			strSQL.Format(L"insert into COURSE_LIST (COURSE_ID,COURSE_NAME,COURSE_TEACHER,WEEKDAY,DAYHOUR,BUILDING,ROOM) values(\'%s\',\'%s\',\'%s\',\'%d\',\'%s\',\'%s\',\'%s\')",m_courseID,m_course_name,m_teacher,m_weekday,m_dayhour,m_building,m_room);
			m_database.ExecuteSQL(strSQL);
			MessageBox(L"�Ѿ��ɹ���ӿα���Ϣ��");
		}
		else
		{
			MessageBox(L"�˿α���Ϣ�Ѵ��ڣ���˶ԣ�");
		}
		initial();
	}
}


void CCourseListManager::OnBnClickedButtonDel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CRecordset m_recordset(&m_database);
	CString strSQL;
	strSQL.Format(L"select * from COURSE_LIST where COURSE_ID='%s'",m_courseID);
	m_recordset.Open(AFX_DB_USE_DEFAULT_TYPE,strSQL);
	// ���ݿ����޴˼�¼
	if(m_recordset.GetRecordCount()==0)
	{
		MessageBox(L"�޴���Ϣ����˶ԣ�");
	}
	else
	{
		strSQL.Format(L"delete from COURSE_LIST where COURSE_ID='%s'",m_courseID);
		m_database.ExecuteSQL(strSQL);
		MessageBox(L"�ѳɹ�ɾ���ÿα���Ϣ��");
		CCourseListManager::OnBnClickedButtonFresh();
	}
	initial();
}


void CCourseListManager::OnBnClickedButtonChange()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	int m_i_weekday=m_C_weekday.GetCurSel();
	// �����Ϣ������
	if(m_courseID.GetLength()==0)
		MessageBox(L"�γ̺Ų���Ϊ�գ�");
	else if(m_course_name.GetLength()==0)
		MessageBox(L"�γ�������Ϊ�գ�");
	else if(m_class.GetLength()==0)
		MessageBox(L"�༶����Ϊ�գ�");
	else if(m_dayhour.GetLength()==0)
		MessageBox(L"�Ͽ�ʱ�䲻��Ϊ�գ�");
	else if(m_teacher.GetLength()==0)
		MessageBox(L"��ʦ����Ϊ�գ�");
	else if(m_building.GetLength()==0)
		MessageBox(L"��ѧ¥�Ų���Ϊ�գ�");
	else if(m_room.GetLength()==0)
		MessageBox(L"���ұ�Ų���Ϊ�գ�");
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
			MessageBox(L"�Ѿ��޸���ӿα���Ϣ��");
		}
		else
		{
			MessageBox(L"�޴���Ϣ����˶ԣ�");
		}
		initial();
	}

}


void CCourseListManager::OnBnClickedButtonFresh()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//���ø��ؼ�Ϊ��ֵ
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ���ѡ�еĿγ̱�ʶ��Ϣ
	int i=m_course_list.GetSelectionMark();
	// ������ʾ����������ϸ��ʾ
	settext(i);
	*pResult = 0;
}


void CCourseListManager::OnDestroy()
{
	CFormView::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	// ʹ�˵��С��α���Ϣ�������ٴο���
	((CMainFrame *)AfxGetMainWnd())->m_bItemCourseListManager=TRUE;
	// ��ա��α���Ϣ��������ָ��
	((CMainFrame *)AfxGetMainWnd())->m_pCourseListManager=NULL;
}
