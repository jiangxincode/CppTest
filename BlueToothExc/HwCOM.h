// HwCOM.h: interface for the CHwCOM class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COM_H__12A72EDD_A7FD_48A8_A0FC_AEBFCA2C5C25__INCLUDED_)
#define AFX_COM_H__12A72EDD_A7FD_48A8_A0FC_AEBFCA2C5C25__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define MAX_COM_BUFSIZE				4*1024
#define INVALID_COM_NO				255		// ��Ч��COM��
#define MAX_ANSWER_NUM				5		// ����Ӧ������������һ���Ƿ�1���ֽڣ�
#define MAX_RETYR_TIMES				5

// �ȴ����ݳ�ʱʱ�䣨���룩
#define WAIT_DATA_TIMEOUT			1000
// ���ͨ�Ŵ������
#define COM_REMOVE_MAX_ERROR		10		// COM�豸����������ٴξ��� COM ��ʧ

#include <afxmt.h>

class CHwCOM 
{
public:
	void ClearComm(BOOL bClearRead);
	int Write(char *data, int size);
	int Read(char *data, int size);
	DWORD GetCommInputBuffLen ();
	CHwCOM ();
	~CHwCOM();
	DWORD GetCommOutBufRemainBytes();
	BOOL WaitForDataToRead(int iBytes,int timeout = WAIT_DATA_TIMEOUT);
	void ClearCommBufByRead();
	void CloseCOM();
	BOOL OpenCOM(int nComNO, int nBaudRate=576000, BOOL bQuiet=FALSE);
	BOOL SetCommMask(DWORD dwEvtMask);
	BOOL WaitCommEvent(LPDWORD lpEvtMask, LPOVERLAPPED lpOverlapped);

//����
public:
	HANDLE m_handleCOM;
	int m_nComNo;
	CCriticalSection *m_pCSFor_OpenCOM;
private:
	int Transmit(char *data, int size, BOOL bRead);
	COMMPROP m_CommProp;
	// �򿪴��ڵ��ټ�ֵ�����в������ڵ��̶߳�Ӧ��ʹ������ټ�ֵ
	// �������Ա�֤�������ͬһ���ڱ������߳�ͬʱ�򿪵����

	CCriticalSection m_CSFor_TransmitCOM;
	BOOL m_bDeviceGotway;

};

#endif // !defined(AFX_COM_H__12A72EDD_A7FD_48A8_A0FC_AEBFCA2C5C25__INCLUDED_)
