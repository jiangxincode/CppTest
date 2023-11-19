// USERS.h : CUSERS ���ʵ��



// CUSERS ʵ��

// ���������� 2013��12��12��, 21:57

#include "stdafx.h"
#include "USERS.h"
IMPLEMENT_DYNAMIC(CUSERS, CRecordset)

CUSERS::CUSERS(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_USER_ID = "";
	m_USER_PASSWORD = "";
	m_USER_TYPE = 0;
	m_nFields = 3;
	m_nDefaultType = dynaset;
}
// #error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CUSERS::GetDefaultConnect()
{
	return _T("DSN=ѧ���ɼ�����ϵͳ;Description=ѧ���ɼ�����ϵͳ;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae 2012;WSID=JIANGXIN;DATABASE=ѧ���ɼ�����ϵͳ");
}

CString CUSERS::GetDefaultSQL()
{
	return _T("[dbo].[USERS]");
}

void CUSERS::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Text(pFX, _T("[USER_ID]"), m_USER_ID);
	RFX_Text(pFX, _T("[USER_PASSWORD]"), m_USER_PASSWORD);
	RFX_Long(pFX, _T("[USER_TYPE]"), m_USER_TYPE);

}
/////////////////////////////////////////////////////////////////////////////
// CUSERS ���

#ifdef _DEBUG
void CUSERS::AssertValid() const
{
	CRecordset::AssertValid();
}

void CUSERS::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


