#include <stdio.h>
#include <windows.h>
#include <string.h>

int main(int argc, char* argv[])
{
	char FilePath[]=""; //the path of the logfile
    char FileName[]="History.txt"; //the name of the logfile
    char cmdLine[] = "cmd.exe";
    char LogFile[MAX_PATH]; //the path_name of the logfile
    int flag_time = 1; //the flag to display the time
    if(argc > 1)
    {
    	int i; //just for the "for" loop;
		for(i=1;i<argc;i++)
    	{
    		int n; //just for the judge
			if((n=strncmp(argv[i],"-p",sizeof("-p")))==0)
    		{
    			i++;
				strcpy(FilePath,argv[i]);
    		}
    		if((n=strncmp(argv[i],"-n",sizeof("-n")))==0)
    		{
    			i++;
				strcpy(FileName,argv[i]);
    		}
    		if((n=strncmp(argv[i],"--ntime",sizeof("--ntime")))==0)
    		{
				flag_time = 0;
    		}
    	}
    }
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
    if(flag_time == 1)
    {
    	fprintf(fp,"<%d-%d-%d %d:%d:%d:%d>%s",
		SystemTime.wYear,SystemTime.wMonth,SystemTime.wDay,SystemTime.wHour,SystemTime.wMinute,SystemTime.wSecond,SystemTime.wMilliseconds,"---Open---\n");
    }
    else if(flag_time == 0)
    {
    	fprintf(fp,"%s","---Open---\n");
    }

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
            if(fp != NULL)
			{
                if(flag_time == 1)
                {
                	fprintf(fp,"<%d-%d-%d %d:%d:%d:%d>%s",
					SystemTime.wYear,SystemTime.wMonth,SystemTime.wDay,SystemTime.wHour,SystemTime.wMinute,SystemTime.wSecond,SystemTime.wMilliseconds,Buff); 
                }
                else if(flag_time == 0)
                {
                	fprintf(fp,"%s",Buff);
                }
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
    if(flag_time == 1)
    {
		fprintf(fp,"<%d-%d-%d %d:%d:%d:%d>%s",
		SystemTime.wYear,SystemTime.wMonth,SystemTime.wDay,SystemTime.wHour,SystemTime.wMinute,SystemTime.wSecond,SystemTime.wMilliseconds,"---Close---\n"); 
    }
    else if(flag_time == 0)
    {
    	fprintf(fp,"%s","---Close---\n");
    }
 
    fclose(fp);
    TerminateProcess(ProcessInformation.hProcess,0);

    return 0;
}

