// HwCOM.h: interface for the CHwCOM class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COM_H__12A72EDD_A7FD_48A8_A0FC_AEBFCA2C5C25__INCLUDED_)
#define AFX_COM_H__12A72EDD_A7FD_48A8_A0FC_AEBFCA2C5C25__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define MAX_COM_BUFSIZE				4*1024
#define INVALID_COM_NO				255		// 无效的COM口
#define MAX_ANSWER_NUM				5		// 发送应答码最大个数（一般是发1个字节）
#define MAX_RETYR_TIMES				5

// 等待数据超时时间（毫秒）
#define WAIT_DATA_TIMEOUT			1000
// 最大通信错误次数
#define COM_REMOVE_MAX_ERROR		10		// COM设备连续错误多少次就算 COM 丢失

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

//属性
public:
	HANDLE m_handleCOM;
	int m_nComNo;
	CCriticalSection *m_pCSFor_OpenCOM;
private:
	int Transmit(char *data, int size, BOOL bRead);
	COMMPROP m_CommProp;
	// 打开串口的临间值，所有操作串口的线程都应该使用这个临间值
	// 这样可以保证不会出现同一串口被几个线程同时打开的情况

	CCriticalSection m_CSFor_TransmitCOM;
	BOOL m_bDeviceGotway;

};

#endif // !defined(AFX_COM_H__12A72EDD_A7FD_48A8_A0FC_AEBFCA2C5C25__INCLUDED_)
