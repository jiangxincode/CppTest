#include <stdio.h>
#include <windows.h>
#include <string.h>

void fprintf_info(int flag_time,char* info,char* LogFile);

int main(int argc, char* argv[])
{
	char FilePath[]=""; //the path of the logfile
    char FileName[]="History.txt"; //the name of the logfile
    char cmdLine[] = "cmd.exe";
    char LogFile[MAX_PATH]; //the path_name of the logfile
    int flag_time = 1; //Display the time with default set
    
    if(argc > 1)
    {
    	int i; //just for the "for" loop;
		for(i=1;i<argc;i++)
    	{
    		int n; //just for the judge
			if((n=strncmp(argv[i],"-p",sizeof("-p")))==0) //set the path of the logfile
    		{
    			i++;
				strcpy(FilePath,argv[i]);
				printf("%s\n",FilePath);
    		}
    		else if((n=strncmp(argv[i],"-n",sizeof("-n")))==0) //set the filename of the logfile
    		{
    			printf("%s\n",FilePath);
				i++;
    			printf("%s\n",FilePath);
				strcpy(FileName,argv[i]);
				printf("%s\n",FilePath);
    		}
    		else if((n=strncmp(argv[i],"--ntime",sizeof("--ntime")))==0) //pick up the time or not
    		{
				flag_time = 0; //Do not display the time of every command 
    		}
    		else if((n=strncmp(argv[i],"--mtime",sizeof("--mtime")))==0) //pick up the time at lest Millisecond
    		{
				flag_time = 2; //Display the time with the accuracy:Millisecond
    		}
    	}
    }
    strcpy(LogFile,FilePath);
    strcat(LogFile,FileName);
    printf("%s",FilePath);
    printf("%s",FileName);
    printf("%s",LogFile);
    
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
    
    //CMD开始时间
    fprintf_info(flag_time,(char *)"---Open---\n",LogFile);
    
    while(1)
	{
        Sleep(100);
        ret=PeekNamedPipe(hReadPipe1,Buff,204800,&lBytesRead,0,0);
        if(lBytesRead)
		{
            ret=ReadFile(hReadPipe1,Buff,lBytesRead,&lBytesRead,0);
            if(!ret)
                break;
            Buff[lBytesRead]='\0';
            strcpy(Buff,Buff+lCmdLen);
            printf("%s",Buff);
        }
        else
		{
            gets(Buff);
            if(!strcmp(Buff,"exit"))
                break;
            strcat(Buff,"\n");
            lBytesRead=strlen(Buff);
            lCmdLen=strlen(Buff);
            //记录运行过得命令
            fprintf_info(flag_time,Buff,LogFile);
            //将命令传送到CMD上
            ret=WriteFile(hWritePipe2,Buff,strlen(Buff),&lBytesRead,0);
            if(!ret)
                break;
        }
    }
    //CMD结束时间
    fprintf_info(flag_time,(char*)"---Close---\n",LogFile);

    TerminateProcess(ProcessInformation.hProcess,0);

    return 0;
}

void fprintf_info(int flag_time,char* info,char* LogFile)
{
    printf("%s",LogFile);
	FILE *fp; //the decriptor of file
    SYSTEMTIME SystemTime;
	GetLocalTime(&SystemTime);
	fp = fopen(LogFile, "a");
	if(fp == NULL)
	{
		printf("error!\n");
	}
	if(flag_time == 0)
    {
    	fprintf(fp,"%s",info);
    }
    else if(flag_time == 1)
    {
		fprintf(fp,"<%d-%d-%d %d:%d:%d>%s",
		SystemTime.wYear,SystemTime.wMonth,SystemTime.wDay,SystemTime.wHour,SystemTime.wMinute,SystemTime.wSecond,info); 
    }
    else if(flag_time == 2)
    {
		fprintf(fp,"<%d-%d-%d %d:%d:%d:%d>%s",
		SystemTime.wYear,SystemTime.wMonth,SystemTime.wDay,SystemTime.wHour,SystemTime.wMinute,SystemTime.wSecond,SystemTime.wMilliseconds,info); 
    }
    fclose(fp);
}
