// CaptureServerManger.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
#include "SystemUtil.h"


#pragma comment(linker,"/subsystem:\"windows\" /entry:\"mainCRTStartup\"") 

string g_strFilePath = "";
string g_strProExeFileName = "";



//获取进程启动参数
string GetProcessorStartParam()
{
	string strParam;
	char sParam[2048];
	sprintf_s(sParam, "%s", (g_strFilePath + g_strProExeFileName).c_str());
	strParam = sParam;
	return strParam;
}

void Init()
{
	g_strFilePath = SYSTEMUTIL::GetExeFileExistDir()+"/";
	g_strProExeFileName = "CaptureStreamServer.exe";
}

int _tmain(int argc, _TCHAR* argv[])
{
	Init();
	while (SYSTEMUTIL::IsProcessorExist(g_strProExeFileName))
	{
		SYSTEMUTIL::TerminateProcessor(g_strProExeFileName);
		printf("process is exist,kill.\n");
//		LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "Exit process:" << pNewUnit->m_nUnitID << " processor id:" << pNewUnit->m_nProcessID);
	}
	string strStartParam = GetProcessorStartParam();
	int nProcessId = 0;
	SYSTEMUTIL::OpenProcessor(g_strProExeFileName, (char*)strStartParam.c_str(), 0, nProcessId, false);
	printf("open process,ID:%d.\n",nProcessId);

	while (1)
	{
		if (!SYSTEMUTIL::IsProcessorExist(nProcessId))
		{
			SYSTEMUTIL::OpenProcessor(g_strProExeFileName, (char*)strStartParam.c_str(), 0, nProcessId, false);
			printf("process is not live,open process again,ID:%d.\n", nProcessId);
		}
		
		Sleep(1000);
	}
	return 0;
}

