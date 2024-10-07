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
 * DeviceIoControl��ȡ��������mac����ʵ��
  * DeviceIoControl ������ϸ����: https://blog.csdn.net/li_wen01/article/details/80137566
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
    //{xxxxx-xxxxx-xxxxx-xxxxx-xxxxx}�ĳ�������������� 
    //��HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows   NT\CurrentVersion\NetworkCards����ĳ������ServiceNameֵ 


    HANDLE   hICDriver = CreateFile(strDriver, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    int   fak = GetLastError();

    if (hICDriver == INVALID_HANDLE_VALUE) {
        printf("INVALID_HANDLE_VALUE");
        return;
    }
    while (1)
    {

        //************************ר�������������ֵĻ�ȡ**********************************////////
        ULONG  WId = 0xFF010183;
        ZD_CMD_STRUCT  buf; // �������������DWORD dwOutBytes;
        DWORD dwOutBytes;								// IOCTL������ݳ��� 


        BOOL m;
        m = DeviceIoControl(hICDriver,
            IOCTL_NDIS_QUERY_GLOBAL_STATS, // ȡ�豸������Ϣ 
            &WId,
            sizeof(WId), // �������ݻ����� 
            &buf,
            sizeof(buf), // ������ݻ����� 
            &dwOutBytes, // ������ݳ��� 
            (LPOVERLAPPED)NULL);
        // ��ͬ��I/O 

        int   fak = GetLastError();
        //**********************************************************************************************************************////////


        //**********************************************��ȡ������MAC��ַ����********************************************************************////////

        ULONG    dwID;
        BYTE    ucData[8] = { 0 };
        DWORD    dwByteRet;

        // ��ȡ��ǰMAC��ַ
        dwID = OID_802_3_CURRENT_ADDRESS;
        m = DeviceIoControl(hICDriver, IOCTL_NDIS_QUERY_GLOBAL_STATS, &dwID, sizeof(dwID), ucData, sizeof(ucData), &dwByteRet, NULL);
        //if( isOK )
        //{    
        //	memcpy( pMacAddress[iIndex].MACAddress, ucData, dwByteRet );

        //	// ��ȡԭ��MAC��ַ
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