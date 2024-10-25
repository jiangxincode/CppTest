#pragma once

#include <shlwapi.h>	// for StrChrI()

//==========================================================================
// ���ò�����
//==========================================================================
#define LENGTH(x) sizeof(x)/sizeof(x[0])
#define MIN(x,y) (((DWORD)(x)<(DWORD)(y))?(x):(y))
#define MAX(x,y) (((DWORD)(x)>(DWORD)(y))?(x):(y))
#define ASSERT_ADDRESS(p,size) ASSERT((p)!=NULL && AfxIsValidAddress((p),(size),TRUE))
#define GET_SAFE_STRING(str) ( (str)?(str):_T("") )
#define	GETFILESIZE(fad) (( (fad).nFileSizeHigh << sizeof(DWORD) ) | (fad).nFileSizeLow)

// strlen ����
#ifdef UNICODE
#define strlen_s wcslen
#else
#define strlen_s strlen
#endif

// ����Ƿ���Ч
#define HANDLE_IS_VALID(h) ( HANDLE(h) && HANDLE(h) != INVALID_HANDLE_VALUE )
// �رվ��
#define SAFE_CLOSE_HANDLE(h)\
{\
	if ( HANDLE_IS_VALID ( h ) )\
	{\
		CloseHandle ( h );\
		h = NULL;\
	}\
}

// �ȴ��¼��� Sleep() ����
#define SLEEP_RETURN(x)\
{\
	if ( ::WaitForSingleObject ( m_hEvtEndModule, x ) == WAIT_OBJECT_0 )\
		return FALSE;\
}
#define SLEEP_BREAK(x)\
{\
	if ( ::WaitForSingleObject ( m_hEvtEndModule, x ) == WAIT_OBJECT_0 )\
		break;\
}

// �����Ի���ʵ��ģ�庯��
template<class T>
T* TGetInstance (
		T **pptDlg,						// ����Ի���ָ���ָ��
		UINT nIDTemplate,				// �Ի�����Դ ID
		CWnd *pParentWnd=NULL,			// �����ھ��
		BOOL bRecreateWhenExist=FALSE,	// �Ի������ʱ�Ƿ����´�����ɾ���Ѿ����ڵ�
		BOOL bNotCreateWindow=FALSE,	// ���������ڣ����� New һ������
		BYTE nShowImmediately=1			// �Ƿ�������ʾ�Ի���0 - ����ʾ��1 - ��ʾ�������ȡ���㣻2 - ������ʾ������ȡ����
)
{
	if ( !pptDlg ) return NULL;
	if ( *pptDlg )
	{
		if ( bRecreateWhenExist )
		{
			::DeleteInstance ( (CWnd**)pptDlg );
		}
		else if ( ::IsWindow ( (*pptDlg)->m_hWnd ) )
		{
			ActiveWindowAndHoldFocus ( (*pptDlg)->m_hWnd );
			return (*pptDlg);
		}
	}
	
	if ( !(*pptDlg) )
	{
		*pptDlg = new T ( pParentWnd );
	}

	if ( !(*pptDlg) ) return NULL;
	if ( bNotCreateWindow ) return (*pptDlg);

	if ( !::IsWindow ( (*pptDlg)->GetSafeHwnd() ) )
	{
		if ( !(*pptDlg)->Create ( nIDTemplate, pParentWnd ) )
		{
			::DeleteInstance ( (CWnd**)pptDlg );
			return NULL;
		}
	}

	if ( nShowImmediately != 0 )
	{
		(*pptDlg)->ShowWindow ( SW_SHOW );
//		(*pptDlg)->SetForegroundWindow ();
		if ( nShowImmediately == 1 )
			ActiveWindowAndHoldFocus ( (*pptDlg)->m_hWnd );
	}

	ASSERT ( (*pptDlg) && ::IsWindow ( (*pptDlg)->GetSafeHwnd() ) );
	return (*pptDlg);
}

class CPublicFunc
{
public:
	CPublicFunc(void);
public:
	~CPublicFunc(void);
};

CString hwFormatMessage ( DWORD dwErrorCode );
BOOL WaitForThreadEnd ( HANDLE *phThread, DWORD dwWaitTime=5000 );
CString Data2HexString ( char *data, int size, int nBytesPerLine=16 );
int ConvStringToHexData(CString csOrgStr, BYTE *szOutBuffer, int nOutBufferSize);
int GetMltiByteChar ( LPCTSTR lpszOrg, OUT char *buf, int size );
int WriteDataToFile(LPCTSTR filename,void* data,long size,LPCTSTR mode, int nStartPos=-1 );
int ReadDataFromFile(LPCTSTR filename,void* data,long size, int nStartPos=-1);
void DrawCurveByDataBuffer ( CDC *pDC, CRect &rcClient, COLORREF clr, BYTE *data, int size, int nCellSize=1, int nStepX=0 );
void DeleteInstance ( CWnd **ppWnd );
void ActiveWindowAndHoldFocus ( HWND hWnd, BOOL bReShowWindow=TRUE );
CSize GetWorkAreaSize ();
void HandleSpanClick(
		CWnd *pOwnerWnd,
		UINT nEditCtrlID,
		NMHDR* pNMHDR,
		LRESULT* pResult,
		int nMaxValue,
		int nMinValue,
		int nInterval=1);
int hwSnprintf ( LPTSTR buffer, int count, LPCTSTR *format, ... );
CString StandardizationFileForPathName ( LPCTSTR lpszFileOrPathName, BOOL bIsFileName, char cReplaceChar=_T('_') );
void StandardizationPathBuffer ( LPTSTR szPath, int nSize, TCHAR cFlagChar=_T('\\') );
CString StandardizationPathBuffer ( LPTSTR lpszPath, TCHAR cFlagChar=_T('\\') );
BOOL PartFileAndPathByFullPath (
		IN LPCTSTR lpszFilePath,
		OUT TCHAR *szOnlyFileName,
		int nFileNameSize,
		OUT TCHAR *szOnlyPath =NULL,
		int nPathSize=0
	);
int GetProgramDir(LPTSTR lpProgram,DWORD dwSize);
CString GetProgramDir();
CString CommonFileDialog (
		LPCTSTR lpszIdentifier,
		BOOL bOpen,
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		CStringArray *pStrAry=NULL,
		CWnd* pParentWnd=NULL,
		LPCTSTR lpszTitle=NULL,
		LPCTSTR lpszInitialDir=NULL,
		LPCTSTR szFilter=NULL
	);
int hwGetFileAttr ( LPCTSTR lpFileName, DWORD *p_dwCreateTime=NULL );
DWORD GetHexDataByBitNum(int nBitNum, BOOL bReverse=FALSE);
