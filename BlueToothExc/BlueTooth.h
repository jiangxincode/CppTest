#pragma once

/*
	������װ��
	ע�⣺
	1����InitInstance()�����е��� WSADATA wsd; WSAStartup (MAKEWORD(2,2), &wsd);
*/

/****************************************************************************************************************
		Ͷ��˵����
****************************************************************************************************************/
#define NOTE_Bluetooth \
	_T("����(Bluetooth)�豸���ҡ������������������������⴮��ͨ�š�������\r\n\
	�������� APIs ��д�Ķ��ַ�ʽ���������豸���ҡ��������������������⴮�ڵ�ͨ�ţ�֧��16���ƺ��ַ������ַ�ʽ��\r\n\
	����������޸ĸ��Ʊ����룬���뱣��������ֲ�Ҫ�޸ġ�\r\n\
	ϣ������Ϊ�й��������ҵ��һ�ݱ�����\r\n\
\r\n\
	������ ���� ������\r\n\
    л��ΰ �� chrys �� chrys@163.com �� http://www.howa.com.cn\r\n\
\r\n\
	������ ���� ������\r\n\
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

// ���ʱ�õ�PIN��
#define AUTHENTICATION_PASSKEY	_T("0000")

// ��Իص������Ĳ���
typedef struct _AUTHENTICATION_CALLBACK_Para
{
	LPVOID lpBlueTooth;
	HANDLE hRadio;
} t_AUTHENTICATION_CALLBACK_Para;

// Զ�������豸��ϸ��Ϣ
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

// ���������豸��Ϣ
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
