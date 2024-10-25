// USERS.h : CUSERS 类的实现



// CUSERS 实现

// 代码生成在 2013年12月12日, 21:57

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
// #error 安全问题：连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
CString CUSERS::GetDefaultConnect()
{
	return _T("DSN=学生成绩管理系统;Description=学生成绩管理系统;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae 2012;WSID=JIANGXIN;DATABASE=学生成绩管理系统");
}

CString CUSERS::GetDefaultSQL()
{
	return _T("[dbo].[USERS]");
}

void CUSERS::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Text(pFX, _T("[USER_ID]"), m_USER_ID);
	RFX_Text(pFX, _T("[USER_PASSWORD]"), m_USER_PASSWORD);
	RFX_Long(pFX, _T("[USER_TYPE]"), m_USER_TYPE);

}
/////////////////////////////////////////////////////////////////////////////
// CUSERS 诊断

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


