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
// 等待线程退出
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
// 将一个16进制的字符串转换为16进制的数，返回数据长度
// 例如：将字符串“61 62 63 64 65 66 67 68”转换成数据 [0x61 0x62 0x63 0x64 0x65 0x66 0x67 0x68]
// 保存到 szOutBuffer 缓冲中
//
int ConvStringToHexData(CString csOrgStr, BYTE *szOutBuffer, int nOutBufferSize)
{
	ASSERT ( szOutBuffer && nOutBufferSize > 0 );
	// 先得到有效的16进制字符串，同时将表示16进制的标志“0x”去掉
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

	// 不是偶数个字符则在后面补“0”
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
// 将 lpszOrg 转换为多字节表示的字符串
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
* Parameter		:	filename		-	文件名
*					data			-	要保存的数据
*					mode			-	文件打开的模式
*					size			-	数据大小
*					nStartPos		-	文件开始位置
* Return Value	:	>=0				-	写入文件的大小
*					-1				-	写操作失败
* Description	:	保存数据到文件
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
* Parameter		:	filename		-	文件名
*					data			-	读到的数据存于此缓冲
*					size			-	缓冲大小
*					nStartPos		-	文件开始位置
* Return Value	:	>=0				-	读到数据的大小
*					-1				-	操作失败
* Description	:	从文件中读取数据
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
// 将缓冲 data 中的数据在客户区 rcClient 中绘出曲线来
//
void DrawCurveByDataBuffer ( CDC *pDC, CRect &rcClient, COLORREF clr, BYTE *data, int size, int nCellSize/*=1*/, int nStepX/*=0*/ )
{
	if ( !pDC || !pDC->GetSafeHdc() || !data || size <= nCellSize ) return;

	ASSERT ( nCellSize <= sizeof(DWORD) );

	// 创建兼容的内存DC
	CDC memDC;
	if ( !memDC.CreateCompatibleDC(pDC) )
		return;
	// 创建兼容的给内存DC做图的位图
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

	// 在内存DC中作图
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

	// 将内存中的DC图写到屏幕上
	VERIFY ( pDC->BitBlt ( rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height()+1, &memDC, 0, 0, SRCCOPY ) );
	if ( pOldmap ) memDC.SelectObject(pOldmap);
	Pen.DeleteObject();
	if ( pOldPen ) memDC.SelectObject ( pOldPen );
	memDC.DeleteDC ();
	memBmp.DeleteObject ();
}

// 删除某个窗体对象实例
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
* Parameter		:	hWnd			-	要激活的窗口句柄
*					bReShowWindow	-	再次调用ShowWindow()函数来显示窗口
* Return Value	:	None
* Description	:	激活一个窗口并获取输入焦点
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
		if(IsIconic(hWnd))		//窗口是最小化的
			ShowWindow(hWnd, SW_RESTORE);
		else
			ShowWindow(hWnd, SW_SHOW);
	}
}

//
// 获取工作区间大小
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
// 处理微调按钮
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
	BOOL nMultiple = ( ( nNumber % nInterval ) == 0 );	// 是否为整数倍

	if ( pNMUpDown->iDelta == 1 )	// 减少
	{
		if ( nMultiple )
			nNumber -= nInterval;
		else
			nNumber = ( nNumber / nInterval * nInterval );

	}
	else	// 增加
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
	// 格式化
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
// 标准化路径或文件名，把不符合文件名命名规则的字符替换成指定的字符。
// 加上该函数
//
CString StandardizationFileForPathName ( LPCTSTR lpszFileOrPathName, BOOL bIsFileName, char cReplaceChar/*=_T('_')*/ )
{
	CString csFileOrPathName = GET_SAFE_STRING(lpszFileOrPathName);
	CString csHead, csTail;
	// 路径名中最后一个'\\'是正常的。另外类似“c:\\”的字符也是正常的。所以先提取出来不参与后面的替换，等替换完以后再补回来
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
// 标准化路径缓冲，如果不是以“\”结尾，将自动加上
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
// 从一个完整的全路径名(包含文件名)中分离出路径（没有文件名）和
// 文件名，如：从“E:\001\002.exe”中分得“E:\001\”，结果存入到
// lsOnlyPath中，“002.exe”存入szOnlyFileName中
//
BOOL PartFileAndPathByFullPath (
		IN LPCTSTR lpszFilePath,			// 全路径名(包含文件名)
		OUT TCHAR *szOnlyFileName,			// 光文件名（没有路径）
		int nFileNameSize,
		OUT TCHAR *szOnlyPath /*=NULL*/,	// 光路径（没有文件名）
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
		&& FileAttrData.dwFileAttributes != 0xffffffff ) //	本身就是目录
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
* Parameter		:	lpProgram	-	存放当前执行程序所在的路径字符串的缓冲
*					dwSize		-	缓冲大小
* Return Value	:	字符个数
* Description	:	得到当前执行程序所在的路径
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
// 显示打开文件对话框，并将用户选择的文件结果返回
// 注意：调用完本函数后一定要删除返回的指针
//
CString CommonFileDialog (
		LPCTSTR lpszIdentifier,				// 唯一标识符，相关数据保存在这个标识符指定的注册表键值下
		BOOL bOpen,							// TRUE - 打开文件； FALSE - 保存文件
		LPCTSTR lpszDefExt /*= NULL*/,
		LPCTSTR lpszFileName /*= NULL*/,
		CStringArray *pStrAry/*=NULL*/,		// bOpen 为 TRUE 时这个参数才有意义，表示是否打开多个文件，多个文件保存在这里
		CWnd* pParentWnd/*=NULL*/,
		LPCTSTR lpszTitle/*=NULL*/,			// 标题
		LPCTSTR lpszInitialDir/*=NULL*/,	// 初始路径
		LPCTSTR szFilter/*=NULL*/				// 文件过滤器
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
	//检测目前的操作系统
	int structsize=0; 
	DWORD dwVersion,dwWindowsMajorVersion,dwWindowsMinorVersion; 
	dwVersion = GetVersion(); 
	dwWindowsMajorVersion = (DWORD)(LOBYTE(LOWORD(dwVersion))); 
	dwWindowsMinorVersion = (DWORD)(HIBYTE(LOWORD(dwVersion))); 
	// 如果运行的操作系统是Windows NT/2000 
	if ( dwVersion < 0x80000000 )
		structsize = 88;//显示新的文件对话框 
	//运行的操作系统Windows 95/98  
	else 
		structsize = 76;//显示老的文件对话框
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

	// 将初始路径保存起来
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
* Parameter		:	lpFileName	-	文件路径
* Return Value	:	-1			-	失败
*					>=0			-	文件大小
* Description	:	获取文件属性来 ( 文件大小、创建时间 )
*********************************************************************************/
int hwGetFileAttr ( LPCTSTR lpFileName, DWORD *p_dwCreateTime/*=NULL*/ )
{
	WIN32_FILE_ATTRIBUTE_DATA FileAttrData;
	BOOL bRet = GetFileAttributesEx ( lpFileName,
		GetFileExInfoStandard, (LPVOID)&FileAttrData );
	if ( !bRet ) return 0;
	if ( ( FileAttrData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) == FILE_ATTRIBUTE_DIRECTORY ) //	是目录
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
// 根据位数来制作一个所有位全为“1”的十六进制的数，比如输入 7 位
// 返回 0x7F，8位则返回 0xFF，即根据位数得到最大值
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
