#include "StdAfx.h"
#include "BlueTooth.h"

CBlueTooth::CBlueTooth(void)
{
	m_Ary_RemoteBthDevInfo.SetSize ( 0, 10*sizeof(BLUETOOTH_DEVICE_INFO) );
	m_Ary_LocalRadioInfo.SetSize ( 0, 10*sizeof(t_LocalRadioInfo) );
}

CBlueTooth::~CBlueTooth(void)
{
	RemoveAll_RemoteBthDevInfo ();
	RemoveAllLocalRadio ();
}

//
// 用 Socket 函数搜索附近的蓝牙设备，成功时返回设备数，否则返回-1
//
int CBlueTooth::WSAScanNearbyBthDev ()
{
	m_Ary_RemoteBthDevInfo.RemoveAll ();

	WSAQUERYSET wsaq;
	HANDLE hLookup;
	union
	{
		CHAR buf[5000];
		double __unused; // ensure proper alignment
	};

	LPWSAQUERYSET pwsaResults = (LPWSAQUERYSET) buf;
	DWORD dwSize = sizeof(buf);
	BOOL bHaveName;
	ZeroMemory(&wsaq, sizeof(wsaq));
	wsaq.dwSize = sizeof(wsaq);
	wsaq.dwNameSpace = NS_BTH;
	wsaq.lpcsaBuffer = NULL;
	if (ERROR_SUCCESS != WSALookupServiceBegin (&wsaq, LUP_CONTAINERS, &hLookup))
	{
		TRACE ( _T("WSALookupServiceBegin failed\n") );
		return -1;
	}

	ZeroMemory(pwsaResults, sizeof(WSAQUERYSET));
	pwsaResults->dwSize = sizeof(WSAQUERYSET);
	pwsaResults->dwNameSpace = NS_BTH;
	pwsaResults->lpBlob = NULL;
	while (ERROR_SUCCESS == WSALookupServiceNext (hLookup, LUP_RETURN_NAME | LUP_RETURN_ADDR, &dwSize, pwsaResults))
	{
		ASSERT (pwsaResults->dwNumberOfCsAddrs == 1);
		BTH_ADDR b = ((SOCKADDR_BTH *)pwsaResults->lpcsaBuffer->RemoteAddr.lpSockaddr)->btAddr;
		bHaveName = pwsaResults->lpszServiceInstanceName && *(pwsaResults->lpszServiceInstanceName);
		t_RemoteBthDevInfo RemoteBthDevInfo;
		if ( bHaveName )
		{
			StringCchPrintf ( RemoteBthDevInfo.szName, sizeof(RemoteBthDevInfo.szName), _T("%s"), 
				pwsaResults->lpszServiceInstanceName );
		}
		RemoteBthDevInfo.Address.ullLong = b;

		TRACE (L"%s ( %04x%08x )\n", RemoteBthDevInfo.szName, GET_NAP(b), GET_SAP(b) );
		m_Ary_RemoteBthDevInfo.Add ( RemoteBthDevInfo );
	}
	WSALookupServiceEnd(hLookup);

	return (int)m_Ary_RemoteBthDevInfo.GetSize();
}

BOOL AUTHENTICATION_CALLBACK (LPVOID pvParam, PBLUETOOTH_DEVICE_INFO pDevice)
{
	t_AUTHENTICATION_CALLBACK_Para *pAUTHENTICATION_CALLBACK_Para = (t_AUTHENTICATION_CALLBACK_Para*)pvParam;
	if ( pAUTHENTICATION_CALLBACK_Para )
	{
		pDevice->fAuthenticated = TRUE;
		DWORD result = BluetoothUpdateDeviceRecord ( pDevice );
		ASSERT ( result == ERROR_SUCCESS );
		result = BluetoothSendAuthenticationResponse ( pAUTHENTICATION_CALLBACK_Para->hRadio, pDevice, AUTHENTICATION_PASSKEY );
		if ( result == ERROR_SUCCESS )
			return TRUE;
	}
	return FALSE;
}

//
// 用蓝牙 APIs 搜索附近的蓝牙设备，成功时返回设备数，否则返回-1
//
int CBlueTooth::ScanNearbyBthDev (
		HANDLE hRadio,
		BOOL fReturnAuthenticated/* = TRUE*/,
		BOOL fReturnRemembered/* = TRUE*/,
		BOOL fReturnUnknown/* = TRUE*/,
		BOOL fReturnConnected/* = TRUE*/,
		BOOL fIssueInquiry/* = FALSE*/,
		UCHAR cTimeoutMultiplier/* = 30*/
	)
{
	RemoveAll_RemoteBthDevInfo ();
	CWaitCursor WaitCursor;

	BLUETOOTH_DEVICE_INFO bdi = { sizeof(BLUETOOTH_DEVICE_INFO) };
	BLUETOOTH_DEVICE_SEARCH_PARAMS bdsp;
	HBLUETOOTH_DEVICE_FIND hbf;
	ZeroMemory(&bdsp, sizeof(BLUETOOTH_DEVICE_SEARCH_PARAMS));

	bdsp.dwSize = sizeof(BLUETOOTH_DEVICE_SEARCH_PARAMS);
	bdsp.hRadio = hRadio;
	bdsp.fReturnAuthenticated = fReturnAuthenticated;
	bdsp.fReturnRemembered = fReturnRemembered;
	bdsp.fReturnUnknown = fReturnUnknown;
	bdsp.fReturnConnected = fReturnConnected;
	bdsp.fIssueInquiry = fIssueInquiry;
	bdsp.cTimeoutMultiplier = cTimeoutMultiplier;

	hbf = BluetoothFindFirstDevice(&bdsp, &bdi);
	if (hbf == NULL) return -1;

	while(true)
	{
		TRACE ( _T("%s ( %s )\n"), bdi.szName, FormatBthAddress(bdi.Address.rgBytes) );
		t_RemoteBthDevInfo RemoteBthDevInfo;
		RemoteBthDevInfo.hRadio = hRadio;
		RemoteBthDevInfo.Address.ullLong = bdi.Address.ullLong;
		_snwprintf_s ( RemoteBthDevInfo.szName, LENGTH(RemoteBthDevInfo.szName), _T("%s"), bdi.szName );
		// 枚举服务
		EnumerateInstalledServices ( RemoteBthDevInfo );
		// 注册配对回调函数
		RemoteBthDevInfo.pAUTHENTICATION_CALLBACK_Para = new t_AUTHENTICATION_CALLBACK_Para;
		if ( RemoteBthDevInfo.pAUTHENTICATION_CALLBACK_Para )
		{
			RemoteBthDevInfo.pAUTHENTICATION_CALLBACK_Para->lpBlueTooth = this;
			RemoteBthDevInfo.pAUTHENTICATION_CALLBACK_Para->hRadio = hRadio;
		}
		BluetoothRegisterForAuthentication ( &bdi, &RemoteBthDevInfo.hRegHandle, AUTHENTICATION_CALLBACK, RemoteBthDevInfo.pAUTHENTICATION_CALLBACK_Para );

		m_Ary_RemoteBthDevInfo.Add ( RemoteBthDevInfo );
		if ( !BluetoothFindNextDevice(hbf, &bdi) )
			break;
	}
	BluetoothFindDeviceClose(hbf);

	return (int)m_Ary_RemoteBthDevInfo.GetSize();
}

//
// 用向导手工搜索附近的蓝牙设备并建立连接，得到设备的详细信息，成功时返回设备数
//
int CBlueTooth::ScanNearbyBthDev_Wizard (
		HWND	hwndParent,
		HANDLE	hRadio,
		LPWSTR  pszInfo/*=NULL*/,						//  IN  If not NULL, sets the "information" text
		BOOL    fForceAuthentication/*=FALSE*/,			//  IN  If TRUE, authenication will be forced before returning
		BOOL    fShowAuthenticated/*=FALSE*/,			//  IN  If TRUE, authenticated devices will be shown in the picker
		BOOL    fShowRemembered/*=TRUE*/,				//  IN  If TRUE, remembered devices will be shown in the picker
		BOOL    fShowUnknown/*=TRUE*/,					//  IN  If TRUE, unknown devices that are not authenticated or "remember" will be shown.
		BOOL    fAddNewDeviceWizard/*=TRUE*/,			//  IN  If TRUE, invokes the add new device wizard.
		BOOL    fSkipServicesPage/*=FALSE*/,			//  IN  If TRUE, skips the "Services" page in the wizard.
		PFN_DEVICE_CALLBACK pfnDeviceCallback/*=NULL*/,	//  IN  If non-NULL, a callback that will be called for each device. If the
														//      the callback returns TRUE, the item will be added. If the callback is
														//      is FALSE, the item will not be shown.
		LPVOID  pvParam/*=NULL*/						//  IN  Parameter to be passed to pfnDeviceCallback as the pvParam.
	)
{
	RemoveAll_RemoteBthDevInfo ();
	BLUETOOTH_SELECT_DEVICE_PARAMS btsdp = { sizeof(btsdp) };

	btsdp.hwndParent = hwndParent;
	btsdp.pszInfo = pszInfo;
	btsdp.fForceAuthentication = fForceAuthentication;
	btsdp.fShowAuthenticated = fShowAuthenticated;
	btsdp.fShowRemembered = fShowRemembered;
	btsdp.fShowUnknown = fShowUnknown;
	btsdp.fAddNewDeviceWizard = fAddNewDeviceWizard;
	btsdp.fSkipServicesPage = fSkipServicesPage;
	btsdp.pfnDeviceCallback = pfnDeviceCallback;
	btsdp.pvParam = pvParam;

	BOOL b = BluetoothSelectDevices( &btsdp );
	if ( b )
	{
		BLUETOOTH_DEVICE_INFO *pbtdi = btsdp.pDevices;
		for ( ULONG cDevice = 0; cDevice < btsdp.cNumDevices; cDevice ++ )
		{
			if ( pbtdi->fAuthenticated || pbtdi->fRemembered )
			{
				t_RemoteBthDevInfo RemoteBthDevInfo;
				RemoteBthDevInfo.hRadio = hRadio;
				RemoteBthDevInfo.Address = pbtdi->Address;
				_snwprintf_s ( RemoteBthDevInfo.szName, LENGTH(RemoteBthDevInfo.szName), _T("%s"), pbtdi->szName );
				EnumerateInstalledServices ( RemoteBthDevInfo );
				m_Ary_RemoteBthDevInfo.Add ( RemoteBthDevInfo );
			}
			pbtdi = (BLUETOOTH_DEVICE_INFO *) ((LPBYTE)pbtdi + pbtdi->dwSize);
		}
		BluetoothSelectDevicesFree( &btsdp );
	}

	return (int)m_Ary_RemoteBthDevInfo.GetSize();
}

//
// 根据远程蓝牙设备的地址获取详细信息
//
BOOL CBlueTooth::BluetoothGetDeviceInfo ( IN t_RemoteBthDevInfo& RemoteBthDevInfo, OUT BLUETOOTH_DEVICE_INFO *pbtdi )
{
	BLUETOOTH_DEVICE_INFO bdi = { sizeof(BLUETOOTH_DEVICE_INFO) };
	bdi.Address.ullLong = RemoteBthDevInfo.Address.ullLong;
	if ( ERROR_SUCCESS != ::BluetoothGetDeviceInfo ( RemoteBthDevInfo.hRadio, &bdi ) )
		return FALSE;
	if ( pbtdi ) memcpy ( pbtdi, &bdi, sizeof(BLUETOOTH_DEVICE_INFO) );
	return TRUE;
}

BOOL CBlueTooth::BluetoothSetServiceState ( HANDLE hRadio, BLUETOOTH_DEVICE_INFO &bdi, GUID guidService, DWORD dwServiceFlags )
{
	DWORD result = ::BluetoothSetServiceState(hRadio, &bdi, &guidService, dwServiceFlags);
	if ( ERROR_SUCCESS != result && ERROR_SERVICE_DOES_NOT_EXIST != result )
	{
		TRACE ( _T("BluetoothSetServiceState failed : %s\n"), hwFormatMessage (result) );
		return FALSE;
	}
	return TRUE;
}

// 枚举已安装的服务
int CBlueTooth::EnumerateInstalledServices( t_RemoteBthDevInfo& RemoteBthDevInfo )
{
	BLUETOOTH_DEVICE_INFO bdi = { sizeof(BLUETOOTH_DEVICE_INFO) };
	if ( !BluetoothGetDeviceInfo ( RemoteBthDevInfo, &bdi ) )
		return -1;

	BluetoothSetServiceState ( RemoteBthDevInfo.hRadio, bdi, SerialPortServiceClass_UUID, BLUETOOTH_SERVICE_ENABLE );
	BluetoothSetServiceState ( RemoteBthDevInfo.hRadio, bdi, LANAccessUsingPPPServiceClass_UUID, BLUETOOTH_SERVICE_ENABLE );
	BluetoothSetServiceState ( RemoteBthDevInfo.hRadio, bdi, DialupNetworkingServiceClass_UUID, BLUETOOTH_SERVICE_ENABLE );

	if ( !BluetoothGetDeviceInfo ( RemoteBthDevInfo, &bdi ) )
		return -1;
	DWORD numServices = LENGTH(RemoteBthDevInfo.guidServices);	
	DWORD result = BluetoothEnumerateInstalledServices(RemoteBthDevInfo.hRadio,&bdi, &numServices, RemoteBthDevInfo.guidServices);
	if ( ERROR_SUCCESS == result ) return numServices;
	return -1;
}

// 显示序号为 nIndex 的蓝牙设备属性框
BOOL CBlueTooth::ShowPropertySheet(int nIndex, HWND hwdParent/*=NULL*/)
{
	if ( nIndex < 0 || nIndex >=m_Ary_RemoteBthDevInfo.GetSize() )
		return FALSE;

	t_RemoteBthDevInfo &RemoteBthDevInfo = m_Ary_RemoteBthDevInfo.GetAt ( nIndex );
	BLUETOOTH_DEVICE_INFO bdi = { sizeof(BLUETOOTH_DEVICE_INFO) };
	if ( !BluetoothGetDeviceInfo ( RemoteBthDevInfo, &bdi ) )
		return FALSE;

	return BluetoothDisplayDeviceProperties ( hwdParent, &bdi );
}

// 请求与远程蓝牙设备配对
BOOL CBlueTooth::RequestAuthenticateDevice(int nIndex, HWND hwdParent/*=NULL*/, DWORD *presult/*=NULL*/)
{
	if ( nIndex < 0 || nIndex >=m_Ary_RemoteBthDevInfo.GetSize() )
		return FALSE;

	t_RemoteBthDevInfo &RemoteBthDevInfo = m_Ary_RemoteBthDevInfo.GetAt ( nIndex );
	BLUETOOTH_DEVICE_INFO bdi = { sizeof(BLUETOOTH_DEVICE_INFO) };
	if ( !BluetoothGetDeviceInfo ( RemoteBthDevInfo, &bdi ) )
		return FALSE;

	if ( bdi.fAuthenticated ) return TRUE;	// 已经配对了
	bdi.fAuthenticated = TRUE;
	VERIFY ( ERROR_SUCCESS == BluetoothUpdateDeviceRecord ( &bdi ) );
	DWORD result = BluetoothAuthenticateDevice ( hwdParent, RemoteBthDevInfo.hRadio, &bdi, AUTHENTICATION_PASSKEY, (ULONG)wcslen(AUTHENTICATION_PASSKEY) );
	if ( presult ) *presult = result;
	if ( result == ERROR_SUCCESS ) return TRUE;

	return FALSE;
}

CString CBlueTooth::FormatBthAddress(BYTE *BthAddress)
{
	ASSERT ( BthAddress );
	BLUETOOTH_ADDRESS Address;
	ASSERT_ADDRESS ( BthAddress, LENGTH(Address.rgBytes)*sizeof(TCHAR) );
	CString csBthAddress;
	for ( int i=0; i<LENGTH(Address.rgBytes); i++ )
	{
		CString csNode;
		csNode.Format ( _T("%.2x"), BthAddress[LENGTH(Address.rgBytes)-i-1] );
		if ( !csBthAddress.IsEmpty() ) csBthAddress += ":";
		csBthAddress += csNode;
	}
	return csBthAddress;
}

// 枚举本地蓝牙设备，返回本地蓝牙设备数
int CBlueTooth::EnumerateLocalRadios(void)
{
	m_Ary_LocalRadioInfo.RemoveAll ();

	HANDLE hRadio = NULL;
	BLUETOOTH_FIND_RADIO_PARAMS btfrp = { sizeof(btfrp) };

	HBLUETOOTH_RADIO_FIND hFind = BluetoothFindFirstRadio( &btfrp, &hRadio );
	if ( NULL != hFind )
	{
		do
		{
			if ( hRadio )
			{
				t_LocalRadioInfo LocalRadioInfo;
				LocalRadioInfo.hRadio = hRadio;
				if ( ERROR_SUCCESS == BluetoothGetRadioInfo ( hRadio, &LocalRadioInfo.RadioInfo ) )
				{
					// 千万注意：以下代码让蓝牙虚拟传出串口能正常工作，我是花了一个通宵的时间才找到这个原因的。
					if (FALSE == BluetoothEnableDiscovery(hRadio, TRUE))
					{
						TRACE(_T("%s\n"), hwFormatMessage(GetLastError()));
					}
					if (FALSE == BluetoothEnableIncomingConnections(hRadio, TRUE))
					{
						TRACE(_T("%s\n"), hwFormatMessage(GetLastError()));
					}

					m_Ary_LocalRadioInfo.Add ( LocalRadioInfo );
				}
			}

		} while( BluetoothFindNextRadio( hFind, &hRadio ) );
		BluetoothFindRadioClose( hFind );
		return (int)m_Ary_LocalRadioInfo.GetSize ();
	}

	return 0;
}

void CBlueTooth::RemoveAllLocalRadio(void)
{
	for ( int i=0; i<m_Ary_LocalRadioInfo.GetSize(); i++ )
	{
		t_LocalRadioInfo &LocalRadioInfo = m_Ary_LocalRadioInfo.GetAt(i);
		if ( LocalRadioInfo.hRadio )
			CloseHandle ( LocalRadioInfo.hRadio );
	}
	m_Ary_LocalRadioInfo.RemoveAll ();
}

void CBlueTooth::RemoveAll_RemoteBthDevInfo(void)
{
	for ( int i=0; i<m_Ary_RemoteBthDevInfo.GetSize(); i++ )
	{
		t_RemoteBthDevInfo &RemoteBthDevInfo = m_Ary_RemoteBthDevInfo.GetAt(i);
		if ( RemoteBthDevInfo.hRegHandle )
			BluetoothUnregisterAuthentication ( RemoteBthDevInfo.hRegHandle );

		if ( RemoteBthDevInfo.pAUTHENTICATION_CALLBACK_Para )
			delete RemoteBthDevInfo.pAUTHENTICATION_CALLBACK_Para;

	}
	m_Ary_RemoteBthDevInfo.RemoveAll ();
}

int CBlueTooth::Test(void)
{
	
	return 0;
}
