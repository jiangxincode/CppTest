#include "StdAfx.h"
#include "PublicFunc.h"

CPublicFunc::CPublicFunc(void)
{
}

CPublicFunc::~CPublicFunc(void)
{
}

CString hwFormatMessage ( DWORD dwErrorCode )
{
	CString csError;
	LPVOID pv;
    FormatMessage (
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		dwErrorCode,
		MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),
		(LPTSTR)&pv,
		0,
		NULL);
	if(pv)
	{
		csError = (LPCTSTR)pv;
		LocalFree ( pv );
	}

	return csError;
}

//
// �ȴ��߳��˳�
//
BOOL WaitForThreadEnd ( HANDLE *phThread, DWORD dwWaitTime /*=5000*/ )
{
	BOOL bRet = TRUE;
	ASSERT ( phThread );
	if ( !(*phThread) ) return TRUE;
	if ( ::WaitForSingleObject ( *phThread, dwWaitTime ) == WAIT_TIMEOUT )
	{
		bRet = FALSE;
		::TerminateThread ( *phThread, 0 );
	}
	::CloseHandle ( *phThread );
	(*phThread) = NULL;
	return bRet;
}

CString Data2HexString ( char *data, int size, int nBytesPerLine/*=16*/ )
{
	CString csHexString, csTemp;
	for ( int i=0; i<size; i++ )
	{
		csTemp.Format ( L"%02X ", (BYTE)data[i] );
		csHexString += csTemp;
		if ( (i+1) % nBytesPerLine == 0 )
			csHexString += "\r\n";
	}
	return csHexString;
}

BYTE HexCharToData(TCHAR cChar)
{
	if ( cChar >= _T('0') && cChar <= _T('9') )
		return (BYTE)(cChar-_T('0'));
	if ( cChar >= _T('a') && cChar <= _T('f') )
		return (BYTE)(cChar-_T('a')+0x0a);
	if ( cChar >= _T('A') && cChar <= _T('F') )
		return (BYTE)(cChar-_T('A')+0x0A);
	return 0xff;
}

//
// ��һ��16���Ƶ��ַ���ת��Ϊ16���Ƶ������������ݳ���
// ���磺���ַ�����61 62 63 64 65 66 67 68��ת�������� [0x61 0x62 0x63 0x64 0x65 0x66 0x67 0x68]
// ���浽 szOutBuffer ������
//
int ConvStringToHexData(CString csOrgStr, BYTE *szOutBuffer, int nOutBufferSize)
{
	ASSERT ( szOutBuffer && nOutBufferSize > 0 );
	// �ȵõ���Ч��16�����ַ�����ͬʱ����ʾ16���Ƶı�־��0x��ȥ��
	CString csLegalHexStr;
	csOrgStr.MakeLower();
	csOrgStr.Replace ( _T("0x"), _T("") );
	for ( int i=0; i<csOrgStr.GetLength(); i++ )
	{
		TCHAR c = csOrgStr.GetAt (i);
		if ( (c>=_T('0')&&c<=_T('9')) || (c>=_T('a') && c<= _T('f')) )
		{
			csLegalHexStr += c;
		}
	}

	if ( csLegalHexStr.GetLength() < 1 ) return 0;

	// ����ż�����ַ����ں��油��0��
	if ( (csLegalHexStr.GetLength() % 2) != 0 )
		csLegalHexStr += _T("0");

	int j=0;
	for ( int i=0; j<nOutBufferSize && i<csLegalHexStr.GetLength(); i+= 2 )
	{
		BYTE btData = 0;
		BYTE bLo = ( 0x0f & HexCharToData ( csLegalHexStr.GetAt(i+1) ) );
		BYTE bHi = ( 0x0f & HexCharToData ( csLegalHexStr.GetAt(i) ) );
		if ( bLo == 0xff || bHi == 0xff )
			return -1;
		btData = ( bHi << 4 ) | bLo;
		szOutBuffer[j++] = btData;
	}

	return j;
}

//
// �� lpszOrg ת��Ϊ���ֽڱ�ʾ���ַ���
//
int GetMltiByteChar ( LPCTSTR lpszOrg, OUT char *buf, int size )
{
	if ( !lpszOrg || !buf || size<1 ) return -1;

#ifdef UNICODE
		return WideCharToMultiByte ( CP_ACP, 0, lpszOrg, (int)strlen_s(lpszOrg), (LPSTR)buf, size, NULL, NULL );
#else
		StrNCpy ( buf, lpszOrg, size-1 );
		return strlen_s(buf);
#endif
}

/********************************************************************************
* Function Type	:	Global
* Parameter		:	filename		-	�ļ���
*					data			-	Ҫ���������
*					mode			-	�ļ��򿪵�ģʽ
*					size			-	���ݴ�С
*					nStartPos		-	�ļ���ʼλ��
* Return Value	:	>=0				-	д���ļ��Ĵ�С
*					-1				-	д����ʧ��
* Description	:	�������ݵ��ļ�
*********************************************************************************/
int WriteDataToFile(LPCTSTR filename,void* data,long size,LPCTSTR mode, int nStartPos/*=-1*/ )
{
	char szFileName[MAX_PATH] = {0};
	char szMode[8] = {0};
	if ( GetMltiByteChar ( filename, szFileName, sizeof(szFileName) ) < 1 )
		return -1;
	GetMltiByteChar(mode,szMode,sizeof(szMode));

	FILE *fp;
	long retval;
	fp=fopen((const char*)szFileName,(const char*)szMode );
	if ( fp!=NULL)
	{
		if ( nStartPos >= 0 )
		{
			if ( fseek ( fp, nStartPos, SEEK_SET ) != 0 )
				return -1;
		}
		retval = (long)fwrite(data,sizeof(char),size,fp);
		fclose(fp);
		if(retval != size)
		{
			return -1;
		}
		else 	return retval;
	}
	else
	{
		return -1;
	}
}
/********************************************************************************
* Function Type	:	Global
* Parameter		:	filename		-	�ļ���
*					data			-	���������ݴ��ڴ˻���
*					size			-	�����С
*					nStartPos		-	�ļ���ʼλ��
* Return Value	:	>=0				-	�������ݵĴ�С
*					-1				-	����ʧ��
* Description	:	���ļ��ж�ȡ����
*********************************************************************************/
int ReadDataFromFile(LPCTSTR filename,void* data,long size, int nStartPos/*=-1*/)
{
	char szFileName[MAX_PATH] = {0};
	if ( GetMltiByteChar ( filename, szFileName, sizeof(szFileName) ) < 1 )
		return -1;

	FILE *fp;
	long retval;
	fp=fopen((const char*)szFileName,"rb");
	if ( fp!=NULL)
	{
		if ( nStartPos >= 0 )
		{
			if ( fseek ( fp, nStartPos, SEEK_SET ) != 0 )
				return -1;
		}
		retval = (long)fread(data,sizeof(char), size, fp);
		fclose(fp);
		if ( retval >= 0 ) return retval;
	}
	return -1;
}


//
// ������ data �е������ڿͻ��� rcClient �л��������
//
void DrawCurveByDataBuffer ( CDC *pDC, CRect &rcClient, COLORREF clr, BYTE *data, int size, int nCellSize/*=1*/, int nStepX/*=0*/ )
{
	if ( !pDC || !pDC->GetSafeHdc() || !data || size <= nCellSize ) return;

	ASSERT ( nCellSize <= sizeof(DWORD) );

	// �������ݵ��ڴ�DC
	CDC memDC;
	if ( !memDC.CreateCompatibleDC(pDC) )
		return;
	// �������ݵĸ��ڴ�DC��ͼ��λͼ
	CBitmap memBmp;
	if ( !memBmp.CreateCompatibleBitmap(pDC,rcClient.Width(),rcClient.Height()+1) )
	{
		memDC.DeleteDC ();
		return;
	}
	CBitmap *pOldmap = memDC.SelectObject(&memBmp);
	if ( !pOldmap )
	{
		memDC.DeleteDC ();
		memBmp.DeleteObject ();
		return;
	}

	// ���ڴ�DC����ͼ
	CPen Pen, *pOldPen;
	VERIFY(Pen.CreatePen(PS_SOLID, 1, clr ));
	pOldPen = memDC.SelectObject ( &Pen );

	DWORD dwMaxValue = GetHexDataByBitNum ( nCellSize*8 );
	DWORD dwCountValue = 0;
	memcpy ( &dwCountValue, data, nCellSize );
	int y = (int) ( (double)dwCountValue * (double)rcClient.Height() / (double)dwMaxValue );
	memDC.MoveTo ( 0, y );
	float fStepX = 0.0;
	if ( nStepX != 0 )
		fStepX = (float)nStepX;
	else
		fStepX = (float)rcClient.Width() / (float)(size/nCellSize-1);
	float fLineX = 0;
	for ( int i=nCellSize; i<size; i+=nCellSize )
	{
		fLineX += fStepX;
		if ( (int)fLineX > rcClient.Width() )
		{
			ASSERT ( FALSE );
			break;
		}
		dwCountValue = 0;
		memcpy ( &dwCountValue, &data[i], nCellSize );
	//	TRACE ( L"i = %d, Value = 0x%x, fLineX = %d\n", i, dwCountValue, (int)fLineX );	//d
		y = (int) ( (double)dwCountValue * (double)rcClient.Height() / (double)dwMaxValue );

		memDC.LineTo ( (int)fLineX, y );
	}

	// ���ڴ��е�DCͼд����Ļ��
	VERIFY ( pDC->BitBlt ( rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height()+1, &memDC, 0, 0, SRCCOPY ) );
	if ( pOldmap ) memDC.SelectObject(pOldmap);
	Pen.DeleteObject();
	if ( pOldPen ) memDC.SelectObject ( pOldPen );
	memDC.DeleteDC ();
	memBmp.DeleteObject ();
}

// ɾ��ĳ���������ʵ��
void DeleteInstance ( CWnd **ppWnd )
{
	if ( !ppWnd || !(*ppWnd) ) return;
	if ( ::IsWindow((*ppWnd)->m_hWnd) )
		(*ppWnd)->DestroyWindow();
	delete (*ppWnd);
	(*ppWnd) = NULL;
}


/********************************************************************************
* Function Type	:	global
* Parameter		:	hWnd			-	Ҫ����Ĵ��ھ��
*					bReShowWindow	-	�ٴε���ShowWindow()��������ʾ����
* Return Value	:	None
* Description	:	����һ�����ڲ���ȡ���뽹��
*********************************************************************************/
void ActiveWindowAndHoldFocus ( HWND hWnd, BOOL bReShowWindow/*=TRUE*/ )
{
	DWORD ThreadID1,ThreadID2;
	long nRet;

	//Nothing to do if already in foreground.
	if(hWnd == GetForegroundWindow())
		return;
	//First need to get the thread responsible for this window,
	//and the thread for the foreground window.
	ThreadID1 = GetWindowThreadProcessId(GetForegroundWindow(), NULL);
	ThreadID2 = GetWindowThreadProcessId(hWnd, NULL);
	//By sharing input state, threads share their concept of
	//the active window.
	if(ThreadID1 != ThreadID2)
	{
		AttachThreadInput(ThreadID1, ThreadID2, TRUE);
		nRet = SetForegroundWindow(hWnd);
		AttachThreadInput(ThreadID1, ThreadID2, FALSE);
	}
	else
	{
		nRet = SetForegroundWindow(hWnd);
	}

	if ( bReShowWindow )
	{
		//Restore and repaint
		if(IsIconic(hWnd))		//��������С����
			ShowWindow(hWnd, SW_RESTORE);
		else
			ShowWindow(hWnd, SW_SHOW);
	}
}

//
// ��ȡ���������С
//
CSize GetWorkAreaSize ()
{
	CSize sz;
	RECT rect;
	SystemParametersInfo ( SPI_GETWORKAREA,0,&rect,0 );
	sz.cx = rect.right - rect.left;
    sz.cy = rect.bottom - rect.top;
	return sz;
}
//
// ����΢����ť
//
void HandleSpanClick(
		CWnd *pOwnerWnd,
		UINT nEditCtrlID,
		NMHDR* pNMHDR,
		LRESULT* pResult,
		int nMaxValue,
		int nMinValue,
		int nInterval/*=1*/)
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	int nNumber = pOwnerWnd->GetDlgItemInt ( nEditCtrlID, NULL );
	if ( nInterval < 1 ) nInterval = 1;
	BOOL nMultiple = ( ( nNumber % nInterval ) == 0 );	// �Ƿ�Ϊ������

	if ( pNMUpDown->iDelta == 1 )	// ����
	{
		if ( nMultiple )
			nNumber -= nInterval;
		else
			nNumber = ( nNumber / nInterval * nInterval );

	}
	else	// ����
	{
		if ( nMultiple )
			nNumber += nInterval;
		else
			nNumber = ( ( nNumber / nInterval + 1 ) * nInterval );
	}

	if ( nNumber > nMaxValue )
			nNumber = nMaxValue;
	if ( nNumber < nMinValue )
			nNumber = nMinValue;

	pOwnerWnd->SetDlgItemInt ( nEditCtrlID, nNumber );
	CEdit *pEdit = (CEdit*)pOwnerWnd->GetDlgItem(nEditCtrlID);
	ASSERT ( pEdit );
	pEdit->SetSel ( 0, -1 );
	pEdit->SetFocus();

	*pResult = 0;
}

int hwSnprintf ( LPTSTR buffer, int count, LPCTSTR format, ... )
{
	if ( count < 1 ) return 0;
	ASSERT_ADDRESS ( buffer, count );
	memset ( buffer, 0, count );
	// ��ʽ��
	va_list  va;
	va_start (va, format);
#ifdef UNICODE
	int nRet = _vsnwprintf ( buffer, count, (const wchar_t*)format, va);
#else
	int nRet = _vsnprintf ( buffer, count, (const char*)format, va);
#endif
	va_end(va);
	buffer [count-1] = _T('\0');

	int nLen = nRet;
	if ( nLen < 0 ) nLen = strlen_s(buffer);
	if ( nLen > count ) nLen = count;

	return nLen;
}

//
// ��׼��·�����ļ������Ѳ������ļ�������������ַ��滻��ָ�����ַ���
// ���ϸú���
//
CString StandardizationFileForPathName ( LPCTSTR lpszFileOrPathName, BOOL bIsFileName, char cReplaceChar/*=_T('_')*/ )
{
	CString csFileOrPathName = GET_SAFE_STRING(lpszFileOrPathName);
	CString csHead, csTail;
	// ·���������һ��'\\'�������ġ��������ơ�c:\\�����ַ�Ҳ�������ġ���������ȡ���������������滻�����滻���Ժ��ٲ�����
	if ( !bIsFileName )
	{
		if ( csFileOrPathName.GetLength() >= 1 && (csFileOrPathName[csFileOrPathName.GetLength()-1] == _T('\\') || csFileOrPathName[csFileOrPathName.GetLength()-1] == _T('/')) )
		{
			csTail += csFileOrPathName[csFileOrPathName.GetLength()-1];
			csFileOrPathName = csFileOrPathName.Left ( csFileOrPathName.GetLength()-1 );
		}

		if ( csFileOrPathName.GetLength() >= 2 && isalpha(csFileOrPathName[0]) && csFileOrPathName[1]==_T(':') )
		{
			csHead = csFileOrPathName.Left(2);
			csFileOrPathName = csFileOrPathName.Mid(2);
		}
		if ( csFileOrPathName.GetLength() >= 1 && (csFileOrPathName[0]==_T('\\') || csFileOrPathName[0]==_T('/')) )
		{
			csHead += csFileOrPathName[0];
			csFileOrPathName = csFileOrPathName.Mid(1);
		}
	}
	else
	{
		csFileOrPathName.Replace ( _T("\\"), _T("_") );
		csFileOrPathName.Replace ( _T("/"), _T("_") );
	}
	csFileOrPathName.Replace ( _T(":"), _T("_") );
	csFileOrPathName.Replace ( _T("*"), _T("_") );
	csFileOrPathName.Replace ( _T("?"), _T("_") );
	csFileOrPathName.Replace ( _T("\""), _T("_") );
	csFileOrPathName.Replace ( _T("<"), _T("_") );
	csFileOrPathName.Replace ( _T(">"), _T("_") );
	csFileOrPathName.Replace ( _T("|"), _T("_") );
	csFileOrPathName.Insert ( 0, csHead );
	csFileOrPathName += csTail;

	return csFileOrPathName;
}

//
// ��׼��·�����壬��������ԡ�\����β�����Զ�����
//
void StandardizationPathBuffer ( LPTSTR szPath, int nSize, TCHAR cFlagChar/*=_T('\\')*/ )
{
	int nLen = strlen_s(szPath);
	if ( nLen < 1 ) return;
	ASSERT_ADDRESS ( szPath, nLen+1 );
	TCHAR szTemp[4] = {0};
	szTemp[0] = cFlagChar;
	if ( szPath[nLen-1] != cFlagChar )
		StrNCat ( szPath, szTemp, nSize/sizeof(TCHAR) );

	CString csPath = StandardizationFileForPathName ( szPath, FALSE );
	StrNCpy ( szPath, csPath, nSize );
}

CString StandardizationPathBuffer ( LPTSTR lpszPath, TCHAR cFlagChar/*=_T('\\')*/ )
{
	TCHAR szPath[MAX_PATH] = {0};
	StrNCpy ( szPath, lpszPath, LENGTH(szPath) );
	StandardizationPathBuffer ( (LPTSTR)szPath, (int)sizeof(szPath), (TCHAR)cFlagChar );
	return szPath;
}

//
//
// ��һ��������ȫ·����(�����ļ���)�з����·����û���ļ�������
// �ļ������磺�ӡ�E:\001\002.exe���зֵá�E:\001\����������뵽
// lsOnlyPath�У���002.exe������szOnlyFileName��
//
BOOL PartFileAndPathByFullPath (
		IN LPCTSTR lpszFilePath,			// ȫ·����(�����ļ���)
		OUT TCHAR *szOnlyFileName,			// ���ļ�����û��·����
		int nFileNameSize,
		OUT TCHAR *szOnlyPath /*=NULL*/,	// ��·����û���ļ�����
		int nPathSize/*=0*/
	)
{
	ASSERT ( lpszFilePath );
	TCHAR chDirPart = _T('\\');
	if ( StrChrI ( lpszFilePath, _T('/') ) )
		chDirPart = _T('/');

	if ( szOnlyFileName )
	{
		memset ( szOnlyFileName, 0, nFileNameSize );
	}
	if ( szOnlyPath )
	{
		memset ( szOnlyPath, 0, nPathSize );
	}
	
	WIN32_FILE_ATTRIBUTE_DATA FileAttrData;
	if ( GetFileAttributesEx ( lpszFilePath, GetFileExInfoStandard, (LPVOID)&FileAttrData ) &&
		( FileAttrData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) == FILE_ATTRIBUTE_DIRECTORY
		&& FileAttrData.dwFileAttributes != 0xffffffff ) //	�������Ŀ¼
	{
		if ( szOnlyPath )
		{
			StrNCpy ( szOnlyPath, lpszFilePath, nPathSize/sizeof(TCHAR) );
			StandardizationPathBuffer ( szOnlyPath, nPathSize, chDirPart );
		}
		return TRUE;
	}

	LPTSTR p = StrRChr ( lpszFilePath, NULL, chDirPart );
	if ( !p )
	{
		StrNCpy ( szOnlyFileName, lpszFilePath, nFileNameSize/sizeof(TCHAR) );
		return TRUE;
	}

	if ( szOnlyFileName )
		StrNCpy ( szOnlyFileName, p+1, nFileNameSize/sizeof(TCHAR) );
	if ( szOnlyPath )
	{
		StrNCpy ( szOnlyPath, lpszFilePath, nPathSize/sizeof(TCHAR) );
		int nLen = p-lpszFilePath+1;
		if ( nPathSize-1 < nLen ) return FALSE;
		szOnlyPath [ nLen ] = _T('\0');
	}
	return TRUE;
}

/********************************************************************************
* Function Type	:	Global
* Parameter		:	lpProgram	-	��ŵ�ǰִ�г������ڵ�·���ַ����Ļ���
*					dwSize		-	�����С
* Return Value	:	�ַ�����
* Description	:	�õ���ǰִ�г������ڵ�·��
*********************************************************************************/
int GetProgramDir(LPTSTR lpProgram,DWORD dwSize)
{
	ASSERT ( lpProgram );
	ZeroMemory(lpProgram,dwSize);
	GetModuleFileName(AfxGetInstanceHandle(),(LPTSTR)lpProgram,dwSize);
	LPTSTR p = StrRChr((LPCTSTR)lpProgram,NULL,_T('\\'));
	if(!p) return 0;
	p[1] = _T('\0');
	int nLength = (int)(p - lpProgram)/sizeof(TCHAR);

	TCHAR szAppDir[MAX_PATH] = {0};
	StrNCpy ( szAppDir, AfxGetApp()->m_pszHelpFilePath, MAX_PATH );
	p = StrRChr((LPCTSTR)szAppDir,NULL,_T('\\'));
	if(!p) return nLength;
	p[1] = _T('\0');
	int nLength1 = (int)(p - szAppDir)/sizeof(TCHAR);
	if ( StrCmpI ( szAppDir, lpProgram ) != 0 )
	{
		CString csMsg;
		csMsg.Format ( _T("Get program directory maybe error occurred.\r\n%s\r\n%s"),
			lpProgram, szAppDir );
		StrNCpy ( lpProgram, szAppDir, dwSize );
		AfxMessageBox ( csMsg );
		return nLength1;
	}

	return nLength;
}

CString GetProgramDir()
{
	TCHAR szProgram[MAX_PATH] = {0};
	GetProgramDir ( szProgram, sizeof(szProgram) );
	return szProgram;
}

//
// ��ʾ���ļ��Ի��򣬲����û�ѡ����ļ��������
// ע�⣺�����걾������һ��Ҫɾ�����ص�ָ��
//
CString CommonFileDialog (
		LPCTSTR lpszIdentifier,				// Ψһ��ʶ����������ݱ����������ʶ��ָ����ע����ֵ��
		BOOL bOpen,							// TRUE - ���ļ��� FALSE - �����ļ�
		LPCTSTR lpszDefExt /*= NULL*/,
		LPCTSTR lpszFileName /*= NULL*/,
		CStringArray *pStrAry/*=NULL*/,		// bOpen Ϊ TRUE ʱ��������������壬��ʾ�Ƿ�򿪶���ļ�������ļ�����������
		CWnd* pParentWnd/*=NULL*/,
		LPCTSTR lpszTitle/*=NULL*/,			// ����
		LPCTSTR lpszInitialDir/*=NULL*/,	// ��ʼ·��
		LPCTSTR szFilter/*=NULL*/				// �ļ�������
	)
{
	ASSERT ( (!bOpen && !pStrAry) || bOpen );
	if ( !szFilter ) szFilter = _T("All Files (*.*)|*.*||");
	CWinApp *pApp = AfxGetApp ();
	TCHAR szInitialDir[MAX_PATH] = {0};
	CString csStringFromReg;
	CString csIdentifier;
	if ( pApp && lpszIdentifier && strlen_s(lpszIdentifier) > 0 )
	{
		csIdentifier.Format ( _T("FileDialog_%s"), lpszIdentifier );
		csStringFromReg = pApp->GetProfileString ( csIdentifier, _T("InitialDir"), _T("") );
		if ( csStringFromReg.GetLength() > 0 )
		{
			PartFileAndPathByFullPath ( csStringFromReg, NULL, 0, szInitialDir, sizeof(szInitialDir) );
		}
	}
	
	if ( strlen_s(szInitialDir) < 1 )
	{
		TCHAR szCurDir[MAX_PATH] = {0};
		if ( !lpszInitialDir || strlen_s(lpszInitialDir) < 1 )
		{
			GetProgramDir ( szCurDir, sizeof(szCurDir) );
			lpszInitialDir = szCurDir;
		}
		PartFileAndPathByFullPath ( lpszInitialDir, NULL, 0, szInitialDir, sizeof(szInitialDir) );
	}

	CFileDialog filedlg( bOpen, lpszDefExt, lpszFileName,
		pStrAry?OFN_ALLOWMULTISELECT:OFN_OVERWRITEPROMPT,
		szFilter, pParentWnd );
	//���Ŀǰ�Ĳ���ϵͳ
	int structsize=0; 
	DWORD dwVersion,dwWindowsMajorVersion,dwWindowsMinorVersion; 
	dwVersion = GetVersion(); 
	dwWindowsMajorVersion = (DWORD)(LOBYTE(LOWORD(dwVersion))); 
	dwWindowsMinorVersion = (DWORD)(HIBYTE(LOWORD(dwVersion))); 
	// ������еĲ���ϵͳ��Windows NT/2000 
	if ( dwVersion < 0x80000000 )
		structsize = 88;//��ʾ�µ��ļ��Ի��� 
	//���еĲ���ϵͳWindows 95/98  
	else 
		structsize = 76;//��ʾ�ϵ��ļ��Ի���
	filedlg.m_ofn.lStructSize=structsize;

	TCHAR* buf = NULL;
	DWORD MAXFILE = 1024*100; // allocate enough memory space
	if ( pStrAry )
	{
		filedlg.m_ofn.nMaxFile = MAXFILE; // set the buffer size
		buf = new TCHAR[MAXFILE];
		if ( !buf ) return _T("");
		filedlg.m_ofn.lpstrFile = buf;
		filedlg.m_ofn.lpstrFile[0] = NULL; 
	}
	if ( lpszTitle )
		filedlg.m_ofn.lpstrTitle = lpszTitle;
	filedlg.m_ofn.hwndOwner = ( pParentWnd ? pParentWnd->GetSafeHwnd() : NULL );
	if ( strlen_s(szInitialDir) > 0 )
	{
		filedlg.m_ofn.lpstrInitialDir = szInitialDir;
	}

	if ( filedlg.DoModal() != IDOK )
	{
		if ( buf ) delete[]buf;
		return _T("");
	}
	
	CString strFileName;
	int nLen = 0;
	if ( pStrAry )
	{
		POSITION pos = filedlg.GetStartPosition();
		while ( pos != NULL )
		{
			strFileName = filedlg.GetNextPathName(pos);
			strFileName.TrimLeft(); strFileName.TrimRight();
			pStrAry->Add ( strFileName );
		}
	}
	else
	{
		strFileName = filedlg.GetPathName ();
	}

	// ����ʼ·����������
	if ( !strFileName.IsEmpty () )
	{
		hwSnprintf ( szInitialDir, sizeof(szInitialDir), (LPCTSTR)_T("%s"), strFileName );
		if ( csIdentifier.GetLength() > 0 && strlen_s(szInitialDir) > 0 )
		{
			pApp->WriteProfileString ( csIdentifier, _T("InitialDir"), szInitialDir );
		}
	}
	
	if ( buf ) delete[]buf;
	
	return strFileName;
}

/********************************************************************************
* Function Type	:	Global
* Parameter		:	lpFileName	-	�ļ�·��
* Return Value	:	-1			-	ʧ��
*					>=0			-	�ļ���С
* Description	:	��ȡ�ļ������� ( �ļ���С������ʱ�� )
*********************************************************************************/
int hwGetFileAttr ( LPCTSTR lpFileName, DWORD *p_dwCreateTime/*=NULL*/ )
{
	WIN32_FILE_ATTRIBUTE_DATA FileAttrData;
	BOOL bRet = GetFileAttributesEx ( lpFileName,
		GetFileExInfoStandard, (LPVOID)&FileAttrData );
	if ( !bRet ) return 0;
	if ( ( FileAttrData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) == FILE_ATTRIBUTE_DIRECTORY ) //	��Ŀ¼
	{
		return 0;
	}
	if ( p_dwCreateTime )
	{
		CTime t ( FileAttrData.ftCreationTime );
		*p_dwCreateTime = t.GetTime();
	}
	return ( GETFILESIZE ( FileAttrData ) );
}

//
// ����λ��������һ������λȫΪ��1����ʮ�����Ƶ������������� 7 λ
// ���� 0x7F��8λ�򷵻� 0xFF��������λ���õ����ֵ
//
DWORD GetHexDataByBitNum(int nBitNum, BOOL bReverse/*=FALSE*/)
{
	DWORD dwHex = 0;
	for ( int i=0; i<nBitNum; i++ )
	{
		dwHex |= (1<<i);
	}
	if ( bReverse ) return (~dwHex);
	return dwHex;
}
