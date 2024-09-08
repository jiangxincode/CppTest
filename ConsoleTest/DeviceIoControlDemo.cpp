#include <windows.h>
#include <tchar.h>
#include <stdio.h>

#include <ntddndis.h>
#include <winioctl.h>

typedef struct _ZD_CMD_STRUCT
{
    union {
        struct
        {
            USHORT  cmd;
            USHORT  param0;
            USHORT  param1;
            USHORT  param2;
            USHORT  param3;
        }
        send;
        struct
        {
            USHORT  status;
            USHORT  resp0;
            USHORT  resp1;
            USHORT  resp2;
            USHORT  resp3;
        }
        rsp;
    } u;
} ZD_CMD_STRUCT, * PZD_CMD_STRUCT;

/**
 * DeviceIoControl读取无线网卡mac完整实例
  * DeviceIoControl 函数详细解析: https://blog.csdn.net/li_wen01/article/details/80137566
 */
void main()
{
    DWORD   dwAccessMode = GENERIC_READ;
    DWORD   dwshareMode = FILE_SHARE_READ;

    //	char szFileName1[255];
    //	memset(szFileName1,0,MAX_PATH); 
    //	strcpy(szFileName1, "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\NetworkCards\\36\\ "); 
    ////	strcat(szFileName1,"{03da3a9f-f3b4-4c98-aa6a-6b883591a37e}");
    //	strcat(szFileName1,"{03DA3A9F-F3B4-4C98-AA6A-6B883591A37E}");
    //
    //	CString szFileName;
    //	szFileName.Format(_T("%s"),szFileName1);

    
    PCTSTR   strDriver;
    strDriver = _T("\\\\.\\{DAC463B6-5298-49F0-A391-D8246D2963F8}");
    //{xxxxx-xxxxx-xxxxx-xxxxx-xxxxx}改成你的网卡的名称 
    //即HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows   NT\CurrentVersion\NetworkCards键下某网卡的ServiceName值 


    HANDLE   hICDriver = CreateFile(strDriver, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    int   fak = GetLastError();

    if (hICDriver == INVALID_HANDLE_VALUE) {
        printf("INVALID_HANDLE_VALUE");
        return;
    }
    while (1)
    {

        //************************专用网卡按键部分的获取**********************************////////
        ULONG  WId = 0xFF010183;
        ZD_CMD_STRUCT  buf; // 输入输出缓冲区DWORD dwOutBytes;
        DWORD dwOutBytes;								// IOCTL输出数据长度 


        BOOL m;
        m = DeviceIoControl(hICDriver,
            IOCTL_NDIS_QUERY_GLOBAL_STATS, // 取设备属性信息 
            &WId,
            sizeof(WId), // 输入数据缓冲区 
            &buf,
            sizeof(buf), // 输出数据缓冲区 
            &dwOutBytes, // 输出数据长度 
            (LPOVERLAPPED)NULL);
        // 用同步I/O 

        int   fak = GetLastError();
        //**********************************************************************************************************************////////


        //**********************************************获取网卡的MAC地址部分********************************************************************////////

        ULONG    dwID;
        BYTE    ucData[8] = { 0 };
        DWORD    dwByteRet;

        // 获取当前MAC地址
        dwID = OID_802_3_CURRENT_ADDRESS;
        m = DeviceIoControl(hICDriver, IOCTL_NDIS_QUERY_GLOBAL_STATS, &dwID, sizeof(dwID), ucData, sizeof(ucData), &dwByteRet, NULL);
        //if( isOK )
        //{    
        //	memcpy( pMacAddress[iIndex].MACAddress, ucData, dwByteRet );

        //	// 获取原生MAC地址
        //	dwID = OID_802_3_PERMANENT_ADDRESS;
        //	isOK = DeviceIoControl( hDeviceFile, IOCTL_NDIS_QUERY_GLOBAL_STATS, &dwID, sizeof(dwID), ucData, sizeof(ucData), &dwByteRet, NULL );
        //	if( isOK )
        //	{    
        //		memcpy( pMacAddress[iIndex].PermanentAddress, ucData, dwByteRet );
        //	}
        printf("%x\t%x\t%x\t%x\t%x\t%x", ucData[0], ucData[1], ucData[2], ucData[3], ucData[4], ucData[5]);
        break;
    }

}