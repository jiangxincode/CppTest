/*
Copyright (c) 2005, code_tin
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
Neither the name of the code_tin nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <stdio.h>
#include <windows.h>

int main()
{
	char FilePath[]="c:\\windows\\system32\\"; //the path of the logfile
    char FileName[]="History.txt"; //the name of the logfile
    char cmdLine[] = "cmd.exe";
    char LogFile[MAX_PATH];
    strcpy(LogFile,FilePath);
    strcat(LogFile,FileName);
    FILE *fp;
    fp = fopen(LogFile, "a");
    SECURITY_ATTRIBUTES sa;
    sa.nLength=sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor=0;
    sa.bInheritHandle=true;
    HANDLE hReadPipe1,hWritePipe1,hReadPipe2,hWritePipe2;
    char Buff[204800];
    int ret;
    ret=CreatePipe(&hReadPipe1,&hWritePipe1,&sa,0);
    ret=CreatePipe(&hReadPipe2,&hWritePipe2,&sa,0);
    STARTUPINFO si;
    ZeroMemory(&si,sizeof(si));
    si.dwFlags = STARTF_USESHOWWINDOW|STARTF_USESTDHANDLES;
    si.wShowWindow = SW_HIDE;
    si.hStdInput = hReadPipe2;
    si.hStdOutput = si.hStdError = hWritePipe1;
    PROCESS_INFORMATION ProcessInformation;
    ret=CreateProcess(NULL,cmdLine,NULL,NULL,1,0,NULL,NULL,&si,&ProcessInformation);
    unsigned long lBytesRead;
    unsigned long lCmdLen=0;
    SYSTEMTIME SystemTime;
    //CMD开始时间
    GetLocalTime(&SystemTime);
    fprintf(fp,"<%d-%d-%d %d:%d:%d>%s",
            SystemTime.wYear,SystemTime.wMonth,SystemTime.wDay,
            SystemTime.wHour,SystemTime.wMinute,SystemTime.wSecond,
            "---Open---\n"); 
    fclose(fp);
    while(1) {
        Sleep(100);
        ret=PeekNamedPipe(hReadPipe1,Buff,204800,&lBytesRead,0,0);
        if(lBytesRead) {
            ret=ReadFile(hReadPipe1,Buff,lBytesRead,&lBytesRead,0);
            if(!ret)
                break;
            Buff[lBytesRead]='\0';
            strcpy(Buff,Buff+lCmdLen);
            printf("%s",Buff);
        }
        else {
            gets(Buff);
            if(!strcmp(Buff,"exit"))
                break;
            strcat(Buff,"\n");
            lBytesRead=strlen(Buff);
            lCmdLen=strlen(Buff);
            GetLocalTime(&SystemTime);
            //记录运行过得命令
            fp = fopen(LogFile, "a");
            if(fp != NULL) {
                fprintf(fp,"<%d-%d-%d %d:%d:%d>%s",
                        SystemTime.wYear,SystemTime.wMonth,SystemTime.wDay,
                        SystemTime.wHour,SystemTime.wMinute,SystemTime.wSecond,
                        Buff);
            }
            fclose(fp);
            //将命令传送到CMD上
            ret=WriteFile(hWritePipe2,Buff,strlen(Buff),&lBytesRead,0);
            if(!ret)
                break;
        }
    }
    //CMD结束时间
    GetLocalTime(&SystemTime);
    fp = fopen(LogFile, "a");
    fprintf(fp,"<%d-%d-%d %d:%d:%d>%s",
            SystemTime.wYear,SystemTime.wMonth,SystemTime.wDay,
            SystemTime.wHour,SystemTime.wMinute,SystemTime.wSecond,
            "---Close---\n");
    fclose(fp);
    TerminateProcess(ProcessInformation.hProcess,0);

    return 0;
}

