#pragma once

/*
	蓝牙封装类
	注意：
	1、在InitInstance()函数中调用 WSADATA wsd; WSAStartup (MAKEWORD(2,2), &wsd);
*/

/****************************************************************************************************************
		投稿说明：
****************************************************************************************************************/
#define NOTE_Bluetooth \
	_T("蓝牙(Bluetooth)设备查找、蓝牙服务发现启动、蓝牙虚拟串口通信》◆◆◆\r\n\
	利用蓝牙 APIs 编写的多种方式进行蓝牙设备查找、服务发现启动，蓝牙虚拟串口的通信，支持16进制和字符串两种方式。\r\n\
	你可以任意修改复制本代码，但请保留这段文字不要修改。\r\n\
	希望我能为中国的软件行业尽一份薄力！\r\n\
\r\n\
	◆◆◆ 作者 ◆◆◆\r\n\
    谢红伟 · chrys · chrys@163.com · http://www.howa.com.cn\r\n\
\r\n\
	◆◆◆ 日期 ◆◆◆\r\n\
    2007-08-07 00:32:53\r\n")

#include "PublicFunc.h"

// for WSALookupServiceBegin() WSALookupServiceNext etc.
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#include <ws2bth.h>

// for BluetoothFindFirstDevice() BluetoothFindNextDevice() etc.
#include <bthsdpdef.h>
#include <BluetoothAPIs.h>
#pragma comment ( lib, "bthprops.lib")

// 配对时用得PIN码
#define AUTHENTICATION_PASSKEY	_T("0000")

// 配对回调函数的参数
typedef struct _AUTHENTICATION_CALLBACK_Para
{
	LPVOID lpBlueTooth;
	HANDLE hRadio;
} t_AUTHENTICATION_CALLBACK_Para;

// 远程蓝牙设备详细信息
typedef struct _RemoteBthDevInfo
{
	_RemoteBthDevInfo ()
	{
		hRadio = NULL;
		memset ( szName, 0, sizeof(szName) );
		memset ( &Address, 0, sizeof(BLUETOOTH_ADDRESS) );
		memset ( guidServices, 0, sizeof(guidServices) );
		hRegHandle = NULL;
		pAUTHENTICATION_CALLBACK_Para = NULL;
	}
	HANDLE  hRadio;
	TCHAR szName[64];
	BLUETOOTH_ADDRESS Address;
	GUID guidServices[10];
	HBLUETOOTH_AUTHENTICATION_REGISTRATION hRegHandle;
	t_AUTHENTICATION_CALLBACK_Para *pAUTHENTICATION_CALLBACK_Para;
} t_RemoteBthDevInfo;
typedef CArray<t_RemoteBthDevInfo,t_RemoteBthDevInfo&> t_Ary_RemoteBthDevInfo;

// 本地蓝牙设备信息
typedef struct _LocalRadioInfo
{
	_LocalRadioInfo()
	{
		memset ( &RadioInfo, 0, sizeof(BLUETOOTH_RADIO_INFO) );
		RadioInfo.dwSize = sizeof(BLUETOOTH_RADIO_INFO);
		hRadio = NULL;
	}
	BLUETOOTH_RADIO_INFO RadioInfo;
	HANDLE hRadio;
} t_LocalRadioInfo;
typedef CArray<t_LocalRadioInfo,t_LocalRadioInfo&> t_Ary_LocalRadioInfo;

class CBlueTooth
{
public:
	CBlueTooth(void);
	~CBlueTooth(void);
	int WSAScanNearbyBthDev ();
	int ScanNearbyBthDev (
		HANDLE hRadio,
		BOOL fReturnAuthenticated = TRUE,
		BOOL fReturnRemembered = TRUE,
		BOOL fReturnUnknown = TRUE,
		BOOL fReturnConnected = TRUE,
		BOOL fIssueInquiry = FALSE,
		UCHAR cTimeoutMultiplier = 30
	);
	BOOL ShowPropertySheet(int nIndex, HWND hwdParent=NULL);
	BOOL RequestAuthenticateDevice(int nIndex, HWND hwdParent=NULL, DWORD *presult=NULL);
	CString FormatBthAddress(BYTE *BthAddress);
	int EnumerateLocalRadios(void);
	int ScanNearbyBthDev_Wizard (
		HWND	hwndParent,
		HANDLE	hRadio,
		LPWSTR  pszInfo=NULL,
		BOOL    fForceAuthentication=FALSE,
		BOOL    fShowAuthenticated=FALSE,
		BOOL    fShowRemembered=TRUE,
		BOOL    fShowUnknown=TRUE,
		BOOL    fAddNewDeviceWizard=TRUE,
		BOOL    fSkipServicesPage=FALSE,
		PFN_DEVICE_CALLBACK pfnDeviceCallback=NULL,
		LPVOID  pvParam=NULL
	);
	BOOL BluetoothGetDeviceInfo ( IN t_RemoteBthDevInfo& RemoteBthDevInfo, OUT BLUETOOTH_DEVICE_INFO *pbtdi );

private:
	void RemoveAllLocalRadio(void);
	int EnumerateInstalledServices(t_RemoteBthDevInfo& RemoteBthDevInfo);
	void RemoveAll_RemoteBthDevInfo(void);
	BOOL BluetoothSetServiceState ( HANDLE hRadio, BLUETOOTH_DEVICE_INFO &bdi, GUID guidService, DWORD dwServiceFlags );

public:
	t_Ary_RemoteBthDevInfo m_Ary_RemoteBthDevInfo;
	t_Ary_LocalRadioInfo m_Ary_LocalRadioInfo;
public:
	int Test(void);
};
