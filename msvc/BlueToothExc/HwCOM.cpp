// COM.cpp: implementation of the CHwCOM class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HwCOM.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHwCOM::CHwCOM ()
	: m_bDeviceGotway ( FALSE )
	, m_pCSFor_OpenCOM ( NULL )
{
	m_nComNo = INVALID_COM_NO;
	ZeroMemory(&m_CommProp,sizeof(COMMPROP));
	m_handleCOM = NULL;
}

CHwCOM::~CHwCOM()
{
	CloseCOM();
}

/********************************************************************************
* Function Type	:	Public
* Parameter		:	buf			-	�����ݻ���
*					dwSize		-	Ҫ�����ֽ���
* Return Value	:	>=0			-	�������ֽ���
*					-1			-	���ڶ�ʧ
* Description	:	�Ӵ����ж�����, �����޷��жϽ��ڴ����ϵ��豸�����ߵ����������
*					�ɵ����߸��ݲ�ͬ��ͨ��Э�����ж��豸�����ߵ����
*********************************************************************************/
int CHwCOM::Read(char *data, int size)
{
	if ( GetCommInputBuffLen () <= 0 ) return 0;

	int nRet = Transmit ( data, size, TRUE );
	return nRet;
}
/********************************************************************************
* Function Type	:	Public
* Parameter		:	buf			-	д���ݻ���
*					dwSize		-	Ҫд���ֽ���
* Return Value	:	>=0			-	д��ȥ���ֽ���
*					-1			-	���ڶ�ʧ
* Description	:	��������д����, �����޷��жϽ��ڴ����ϵ��豸�����ߵ����������
*					�ɵ����߸��ݲ�ͬ��ͨ��Э�����ж��豸�����ߵ����
*********************************************************************************/
int CHwCOM::Write(char *data, int size)
{
	if ( size < 1 ) return 0;
	return Transmit ( data, size, FALSE );
}

/********************************************************************************
* Function Type	:	Public
* Parameter		:	buf			-	д���ݻ���
*					dwSize		-	Ҫд���ֽ���
* Return Value	:	>=0			-	����ɹ����ֽ���
*					-1			-	���ڶ�ʧ
* Description	:	�봮������ͨ��, �����޷��жϽ��ڴ����ϵ��豸�����ߵ����������
*					�ɵ����߸��ݲ�ͬ��ͨ��Э�����ж��豸�����ߵ����
*********************************************************************************/
int CHwCOM::Transmit(char *data, int size, BOOL bRead)
{
	if ( m_bDeviceGotway ) return 0;

	DWORD dwTransmitBytes = 0;
	m_CSFor_TransmitCOM.Lock();

	BOOL bRet = FALSE;
	for ( int i=0; i< COM_REMOVE_MAX_ERROR; i++ )
	{
		if ( bRead )
			bRet = ::ReadFile ( m_handleCOM, data, size, &dwTransmitBytes, NULL );
		else
			bRet = ::WriteFile ( m_handleCOM, data, size, &dwTransmitBytes, NULL );
		if ( bRet ) break;
		Sleep ( 1 );
	}
	m_CSFor_TransmitCOM.Unlock();

	// ����ͨ�ųɹ�
	if ( bRet )
	{
		return (int)dwTransmitBytes;
	}

	// ���ڶ�ʧ
	m_bDeviceGotway = TRUE;
	return -1;
}

/********************************************************************************
* Function Type	:	Private
* Parameter		:	bClearRead	-	TRUE  : ��ֹ�����������������
*									FALSE : ��ֹд���������д����
* Return Value	:	None
* Description	:	��մ������л�����ַ�
*********************************************************************************/
void CHwCOM::ClearComm(BOOL bClearRead)
{
	m_CSFor_TransmitCOM.Lock();
	if(bClearRead)
		PurgeComm(m_handleCOM, PURGE_RXABORT | PURGE_RXCLEAR);
	else
		PurgeComm(m_handleCOM, PURGE_TXABORT | PURGE_TXCLEAR);
	m_CSFor_TransmitCOM.Unlock();
}
/********************************************************************************
* Function Type	:	Public
* Parameter		:	None
* Return Value	:	����
* Description	:	��ô������뻺�����ĳ���
*********************************************************************************/
DWORD CHwCOM::GetCommInputBuffLen ()
{
	DWORD Errors;
	COMSTAT Stat;
	m_CSFor_TransmitCOM.Lock();
	BOOL bRet = ClearCommError(m_handleCOM,&Errors,&Stat);
	m_CSFor_TransmitCOM.Unlock();
	return Stat.cbInQue;
}
/********************************************************************************
* Function Type	:	Public
* Parameter		:	None
* Return Value	:	����
* Description	:	��ô�������������л��ж����ֽ�����δ����
*********************************************************************************/
DWORD CHwCOM::GetCommOutBufRemainBytes()
{
	DWORD Errors;
	COMSTAT Stat;
	m_CSFor_TransmitCOM.Lock();
	ClearCommError(m_handleCOM,&Errors,&Stat);
	m_CSFor_TransmitCOM.Unlock();
	return Stat.cbOutQue;
}

/********************************************************************************
* Function Type	:	Public
* Parameter		:	nComNO				-	���ں�(�磺2,��ʾCOM2)
*					nBaudRate			-	������
* Return Value	:	None
* Description	:	��ʼ������
*********************************************************************************/
BOOL CHwCOM::OpenCOM(int nComNO, int nBaudRate/*=576000*/, BOOL bQuiet/*=FALSE*/)
{
	if ( m_handleCOM && m_handleCOM != INVALID_HANDLE_VALUE )
		return TRUE;

	ASSERT ( nComNO > 0 && nComNO < 255 );
	m_nComNo = nComNO;
	TCHAR ucFileName[20];
	//�򿪴���
	_snwprintf_s(ucFileName,sizeof(ucFileName), _T("\\\\.\\COM%d"),m_nComNo);
	if ( m_pCSFor_OpenCOM )
		m_pCSFor_OpenCOM->Lock();
	m_handleCOM = CreateFile((LPCTSTR)ucFileName,
		GENERIC_READ | GENERIC_WRITE,				//������Ϊ�ɶ�д
		0,											//�Զ�ռģʽ�򿪴���
		NULL,										//�����ð�ȫ����
		OPEN_EXISTING,								//�豸������ʱ��ʧ��
		0,											//���������ļ�����
		NULL);										// �������ģ���ļ�
	if ( m_pCSFor_OpenCOM )
		m_pCSFor_OpenCOM->Unlock();

	if ( !m_handleCOM || m_handleCOM == INVALID_HANDLE_VALUE )
	{
		if ( !bQuiet )
		{
			TRACE ( L"Open(#2) [COM%d] failed\n",m_nComNo );
		}
		m_handleCOM = NULL;
		return FALSE;
	}

	// ����DCB
	DCB MyDcb;
	if(GetCommState(m_handleCOM,&MyDcb))
	{
		MyDcb.BaudRate = nBaudRate;
		MyDcb.ByteSize = 8;
		MyDcb.Parity = NOPARITY;
		MyDcb.StopBits = ONESTOPBIT;
		MyDcb.fBinary=1;
		SetCommState(m_handleCOM,&MyDcb);
	}
	SetupComm(m_handleCOM,MAX_COM_BUFSIZE,MAX_COM_BUFSIZE/4);

	// ���г�ʱ����
	COMMTIMEOUTS CommTimeouts =
	{
		100,				// ���ַ������ʱʱ��: 100 ms
		2,					// ������ʱÿ�ַ���ʱ��: 2 ms (n���ַ��ܹ�Ϊ2*n ms)
		1000,				// ������(�����)����ʱʱ��: 1000 ms
		2,					// д����ʱÿ�ַ���ʱ��: 2 ms (n���ַ��ܹ�Ϊ2*n ms)
		500,				// ������(�����)д��ʱʱ��: 500 ms
	};
	if ( !SetCommTimeouts(m_handleCOM, &CommTimeouts) )
	{
		TRACE ( L"Set [COM%d] timeout parameter failed\n", nComNO );
		CloseCOM ();
		return FALSE;
	}

	if ( !EscapeCommFunction ( m_handleCOM,SETDTR ) )
	{
		TRACE ( L"[COM%d] EscapeCommFunction failed\n", nComNO );
	}

	BOOL bRet = GetCommProperties ( m_handleCOM, &m_CommProp );
	if( !bRet || !(m_CommProp.dwProvCapabilities&PCF_INTTIMEOUTS) )
	{
		TRACE ( L"[COM%d] not supported capabilities\n", nComNO );
	}

	ClearCommBufByRead();

	m_bDeviceGotway = FALSE;
	if ( !bQuiet )
	{
		TRACE ( L"Open(#2) [COM%d] successfully\n", nComNO );
	}
	return TRUE;
}

void CHwCOM::CloseCOM()
{
	if ( m_handleCOM && m_handleCOM != INVALID_HANDLE_VALUE )
	{
		CloseHandle ( m_handleCOM );
		m_handleCOM = NULL;
	}
}
/********************************************************************************
* Function Type	:	Private
* Parameter		:	None
* Return Value	:	None
* Description	:	ͨ������������մ������л�����ַ�
*********************************************************************************/
void CHwCOM::ClearCommBufByRead()
{
	ClearComm ( TRUE ); ClearComm ( FALSE );
	char buf[1024] = {0};
	int nReadyBytes = 0;
	while ( ( nReadyBytes = (int)GetCommInputBuffLen() ) > 0 )
	{
		Read ( buf, nReadyBytes );
	}
}
/********************************************************************************
* Function Type	:	Private
* Parameter		:	iBytes		-	[in] �ȴ������ֽ���
*					timeout		-	[in] �ȴ����ݵ����ʱ��(����)
* Return Value	:	TRUE		-	�ȵ�����
*					FALSE		-	û�ȵ�
* Description	:	�ȵ�ָ���ֽ����ݿɶ�
*********************************************************************************/
BOOL CHwCOM::WaitForDataToRead(int iBytes,int timeout/* = WAIT_DATA_TIMEOUT*/)
{
	DWORD start_time = GetTickCount();
	while ( (DWORD)( GetTickCount() - start_time ) < (DWORD)timeout)
	{
		if( GetCommInputBuffLen() < (DWORD)iBytes)	//û�н��յ�iBytes������
			Sleep ( 100 );
		else
		{
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CHwCOM::SetCommMask(DWORD dwEvtMask)
{
	if ( m_handleCOM && m_handleCOM != INVALID_HANDLE_VALUE )
	{
		return ::SetCommMask ( m_handleCOM, dwEvtMask );
	}
	return FALSE;
}

BOOL CHwCOM::WaitCommEvent(LPDWORD lpEvtMask, LPOVERLAPPED lpOverlapped)
{
	if ( m_handleCOM && m_handleCOM != INVALID_HANDLE_VALUE )
	{
		return ::WaitCommEvent ( m_handleCOM, lpEvtMask, lpOverlapped );
	}
	return FALSE;
}
