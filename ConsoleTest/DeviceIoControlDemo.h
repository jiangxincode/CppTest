
// opencadrDlg.h : header file
//

#pragma once

#include <windows.h>
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