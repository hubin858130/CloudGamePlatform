// CaptureStreamServer.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
//#include "CNvFBCHWEncode.h"
//#include "NvFBCDX9NvEnc.h"
#include "Util.h"
#include "SystemUtil.h"
#include "HttpUtils.h"
#include "EventSelectServer.h"
#include "BaseUdpServer.h"

#include "AudioCapture/AudioRecord.hpp"
#include "Pcm2AacIns.h"

#include "BroadcastRecver.h"
#include "MsgQueue.h"

#include "dump.h"
#include "CommonRSAkey.h"

#include <process.h>
#include <string>
using std::string;
typedef unsigned __int64 _UINT64_;


int g_bLoginSuccess = 0;
int  g_nUserStatus = 0;//0 等待观众  1 进来观众 2 观众离开

int g_nUserNum = 0;
int g_nSleepMillSec = 20;

//音频相关
static COutputRecord	g_OutputRecord;
CPcm2AacIns				g_cPcm2aacIns;
bool					g_bAudioInited = false;
bool					bRunning = false;
CHttpUtils g_cHttpUtil;
int UploadVmStatus();
CBaseUdpServer g_cUpdServer;

int g_nCapWidth = 1280;
int g_nCapHeight = 720;
int g_nCapBps = 6000 * 1024;
int g_nCapFps = 30;

void UserCallback(int nUserNum, int nStatus);

//初始状态异常判断
void ExceptRunStatusThread(void* p)
{
	int nIndex = 0;
	LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), " runstatus:2,last one op is reboot.");
	while (1)
	{
		if (g_bLoginSuccess != 2)
		{
			break;
		}
		if (nIndex > 60)
		{
			g_bLoginSuccess = 0;
			break;
		}
		Sleep(1000);
		nIndex++;
	}
	LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), " ExceptRunStatusThread end.");
}

//用户IO断开回调
void UserIOConnectStatus(int nStatus, char* szUserID)
{
	if (nStatus == 0)
	{
		g_bLoginSuccess = 1;
		printf("用户登录\n");
		LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), " [net]USer 连接。" );

		SetCursorStatus(true);//初始化默认有鼠标  移动端模式
	}
	if (nStatus == 1)//IO lost
	{
		g_bLoginSuccess = 0;

		printf("用户断线\n");
		//销毁 token
		//int nUserId = 62;
		//g_cVideoEnginesIns.RemoveUserToken(nUserId);
		//g_nUserStatus = 2;
		//g_cVideoEnginesIns.AddUseridAndToken(nUserId, nUserId);
		LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "[net]USer 断线!" );
	}
	if (nStatus == 100)//普通模式
	{
		//SetCursorStatus(false);//PC端模式
		SetCursorStatus(true);//移动端模式
		LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "[mouse]普通");
	}
	if (nStatus == 101)//游戏模式
	{
		SetCursorStatus(true);
		LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "[mouse]游戏");
	}
	if (nStatus == 2002)
	{
		g_bLoginSuccess = 2;
		UploadVmStatus();
		LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "restart mediaserver");
		StopMediaServer();
		LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "StopMediaServer.");
		Sleep(50);
		StartMediaServer(UserCallback);
		Sleep(50);
		LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "StartMediaServer.");
	}

	string strExePath = GetExeFileExistDir() + "/Server.ini";
	char *strConfigFilePath = (char*)strExePath.c_str();
	char sz[5];
	memset(sz, 0, 5);
	sprintf(sz, "%d", g_bLoginSuccess);
	WritePrivateProfileString("info", "runstatus", sz, strConfigFilePath);
}

int UploadVmStatus()
{
	char szUrl[50];
	memset(szUrl, 0, 50);
	char szHostGuid[50];
	memset(szHostGuid, 0, 50);
	string strExePath = GetExeFileExistDir() + "\\Server.ini";
	char *strConfigFilePath = (char*)strExePath.c_str();
	GetPrivateProfileString("info", "url", NULL, szUrl, 50, strConfigFilePath);
	GetPrivateProfileString("info", "id", NULL, szHostGuid, 50, strConfigFilePath);
	string strResult = "";
	string strUrl(szUrl);
	strUrl += "/vm/";
	strUrl += string(szHostGuid);

	string strHostName = string(szHostGuid);//SYSTEMUTIL::GetLocalHostName();
	string strStatus = "0";
	if (g_bLoginSuccess==1)
	{
		strStatus = "1";
	}
	if (g_bLoginSuccess == 2)
	{
		strStatus = "2";
	}
	/*string strJsonContent = "?hostname=" + strHostName;
	strJsonContent += "&statusFlag=";
	strJsonContent += strStatus;*/

	string strJsonContent = "{\"runState\":\"";
	strJsonContent += strStatus;
	strJsonContent += "\"}";

	int nRet = g_cHttpUtil.PostHttp(strUrl, strJsonContent, strResult, strJsonContent.length(),1);
	if (nRet == 0)
	{
		LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "VM status:" + strStatus + " uplaod sucess.");
	}
	else
	{
		LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "VM status:" + strStatus + " uplaod failed.");
	}
	return nRet;
}

void VmStatusThread(void* p)
{
	
	while (TRUE)
	{
		UploadVmStatus();
		Sleep(5 * 1000);
	}
}

void IOServThread(void* p)
{
	IoDomain(UserIOConnectStatus);
}

void IOUdpServThread(void* p)
{
	g_cUpdServer.IoDomain(UserIOConnectStatus);
}

void mouseRgbaCallback(char* szBuffer, int nSize)
{
	//printf("recv mouse:%d\n", nSize);
	CMsgQueue::getInstance().pushSendMsgToQueue(szBuffer, nSize, 1);
}

DWORD g_LastTime = 0;
int nIdex = 0;
time_t t1 = 0;
int nDataSize = 0;
char* szSPSPPS = NULL;
int   nSPSSize = 0;

void h264BufferCallback(char* szBuffer, int nSize, int nWidth, int nHeight, int nFrameType, void * pUserData)
{
//	fprintf(stderr, __FUNCTION__": recv h264 size:%x.\n", nSize);
	long lTimes = (long)pUserData;
	SYSTEMTIME timeSys;
	GetLocalTime(&timeSys);
	lTimes = timeSys.wMilliseconds + timeSys.wSecond * 1000 + timeSys.wMinute * 60000;
	//补偿SPSPPS
	if (nFrameType == 100)
	{
		if (szSPSPPS == NULL)
		{
			szSPSPPS = new char[nSize];
		}
		memcpy(szSPSPPS, szBuffer, nSize);
		nSPSSize = nSize;

		//char sz[100];
		//sprintf_s(sz, "./spspps.h264");
		//FILE* p = NULL;
		//fopen_s(&p, sz, "wb");
		//if (p)
		//{
		//	fwrite(szSPSPPS, 1, nSPSSize, p);
		//	fclose(p);
		//}
		return;
	}
	if (nFrameType == 0x03)
	{//I Frame

		char* szIFrameBuffer = new char[nSPSSize + nSize];
		memcpy(szIFrameBuffer, szSPSPPS, nSPSSize);
		memcpy(szIFrameBuffer + nSPSSize, szBuffer, nSize);		
		
		lTimes *= 100;

		//huqb
		if (bRunning)
			SendVideoBuffer(szIFrameBuffer , nSize+nSPSSize , lTimes);

//test
		//char sz[100];
		//sprintf_s(sz, "./h264/%ld.h264", lTimes);
		//FILE* p = NULL;
		//fopen_s(&p, sz, "wb");
		//if (p)
		//{
		//	fwrite(szIFrameBuffer, 1, nSize + nSPSSize, p);
		//	fclose(p);
		//}

		delete[] szIFrameBuffer;
		szIFrameBuffer = NULL;
		
	}
	else
	{
		if (bRunning)
			SendVideoBuffer(szBuffer, nSize , lTimes);
//test
		//char sz[100];
		//sprintf_s(sz, "./h264/%ld.h264", lTimes);
		//FILE* p = NULL;
		//fopen_s(&p, sz, "wb");
		//if (p)
		//{
		//	fwrite(szBuffer, 1, nSize, p);
		//	fclose(p);
		//}
	}

	
//	LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "Send steam time:" << lTimes);
	

	if (nFrameType == 1)
	{
		static int nBigSize = 0;
		if (nBigSize < nSize)
		{
			nBigSize = nSize;
			LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "keyframe size:" << nSize);
		}
	}

	if (nIdex == 0)
	{
		t1 = time(NULL);
	}
	nIdex++;
	nDataSize += nSize;
	if (nIdex == 2000)
	{
		time_t t2 = time(NULL);
//		fprintf(stderr, "time:%ld s,count:%d 次,len:%ld Bytes\n", t2 - t1, 3600, nDataSize);
		LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "total time:"<<t2-t1<<"秒,count:2000"<<"次,len:"<<nDataSize);
		nIdex = 0;
		nDataSize = 0;
	}
}

short g_szTemp[2049];  //4096
int  g_nSize = 0;
long lLast = 0;
void AACDataCb(char* szBuffer, int nSize)
{
	if (!g_bAudioInited)
	{
		int nSamples = 0;
		int nChannels = 0;
		int nBitsPerSam = 0;
		g_OutputRecord.GetPcmBaseInfo(nSamples, nChannels, nBitsPerSam);
		g_cPcm2aacIns.InitParams(nSamples, nChannels, 0, 44100);
		g_bAudioInited = true;
	}
	//float32 -> short16
	//	short* pShortBuffer = new short[nSize / 4];
	float fC = 0.1f;
	static int nCount = 0;
	for (int n = 0; n < nSize / 4; n++)
	{
		char* sz1 = (char*)szBuffer + (n * 4);
		memcpy(&fC, sz1, 4);
		//printf("%d:%0.4f\n", n, fC);

		g_szTemp[g_nSize++] = (short)(fC * 32768);
		if (g_nSize == 2048)
		{
			unsigned char* szAACData = NULL;
			int   nAACDataSize = 0;
			g_cPcm2aacIns.SetPcmBuffer((char*)g_szTemp, g_nSize * 2, szAACData, nAACDataSize);
			
			if (nAACDataSize > 1)
			{
	/*			static int nInd = 0;
				char szPath[50];
				memset(szPath, 0, 50);
				sprintf_s(szPath, "./pcm/%d.pcm", nInd);
				FILE* pFile = NULL;
				fopen_s(&pFile, szPath, "wb");
				fwrite(g_szTemp, g_nSize * 2, 1, pFile);
				fclose(pFile);

				memset(szPath, 0, 50);
				sprintf_s(szPath, "./aac/%d.aac", nInd++);
				fopen_s(&pFile, szPath, "wb");
				fwrite(szAACData, nAACDataSize, 1, pFile);
				fclose(pFile);*/

				/*static FILE* pFile = NULL;
				static int nb = 0;
				if (nb == 0)
				{
					fopen_s(&pFile, "12.aac", "ab+");
				}
				if (nb++<2000)
				{
					fwrite(szAACData, 1, nAACDataSize, pFile);
				}
				if (nb == 2001)
				{
					fclose(pFile);
				}*/
				if (bRunning)
					SendAudioBuffer((char*)szAACData, nAACDataSize);
			}
			else
			{
				printf("audio lost:%d\n", nCount++);
			}

			g_nSize = 0;
		}
	}

}

string g_strFilename = "E:\\huqb\\RmServer\\lic.dat";
int VerificationFromFile(string strFile)
{
	int nRet = -2;
	FILE* flRead = NULL;
	fopen_s(&flRead, (char*)g_strFilename.c_str(), "rb");
	if (flRead != NULL)
	{
		fseek(flRead, 0, SEEK_END);
		int nDataLen = ftell(flRead);
		fseek(flRead, 0, SEEK_SET);

		char* szLicense = new char[nDataLen];
		fread(szLicense, 1, nDataLen, flRead);

		for (int i = 0; i < nDataLen; i++)
		{
			char sz[100];
			memset(sz, 0, 100);
			sprintf_s(sz,"%d:%d\n", i,szLicense[i]);
			OutputDebugString(sz);
		}

		char*szBase64 = base64_encode((char*)szLicense, nDataLen);
//		char*szBase64 = base64_encode("abcd", 4);

		string strBase(szBase64);
		


		string strUrl = "http://192.168.100.21:8080/license/validate";
		string strRet = "";
//		nRet = g_cHttpUtil.VerificationLicense(strUrl, szLicense, nDataLen, strRet);

	//	nRet = g_cHttpUtil.PostHttp(strUrl, szLicense, nDataLen, strRet);
		nRet = g_cHttpUtil.PostHttp(strUrl,strBase,strRet,strBase.length());

		fclose(flRead);
		delete []szLicense;
		base64_ReleaseDataBuffer(&szBase64);
		szLicense = NULL;
	}
	return nRet;
}

int Verification()
{
	//int nRet = -2;
	//string strMac = SYSTEMUTIL::GetLocalMacAdress();
	//string strHost = SYSTEMUTIL::GetLocalHostName() + "&";
	//strHost += strMac;

	//int nLen = strHost.length();

	//RSA_PARAM sParam = g_comSoftKeyRSA[0];
	//_UINT64_* pEnc = new _UINT64_[nLen];
	//unsigned char * q = (unsigned char *)strHost.c_str();;

	//for (unsigned long i = 0; i < nLen; i++)
	//{
	//	_UINT64_ tt = q[i];
	//	pEnc[i] = PowMod(tt, sParam.e, sParam.n);
	//}

	//char*szBase64 = base64_encode((char*)pEnc, nLen*sizeof(_UINT64_));
	//string strBase(szBase64);
	//strBase = UrlEncode(strBase);

	//string strUrl = "http://license.udoujiao.com:80/sjylicense/licenses/checkLicense";
	//string strRet = "";
	//nRet = g_cHttpUtil.VerificationLicense(strUrl, (char*)strBase.c_str(), strBase.length(), strRet);

	//delete[] pEnc; 
	//pEnc = NULL;
	//base64_ReleaseDataBuffer(&szBase64);
	//return nRet;
	return 1;//无需鉴权
}

int InitConfig()
{
	//VerificationFromFile();
	int nLicRet = Verification();//-1 服务器不通 0 没有权限 >0 可以使用
	if (nLicRet == 0)
	{
		LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "服务器授权不足，请联系qq:642681716");
		int nIndex = 0;
		while (1)
		{
			Sleep(1000);
			if (nIdex++ > 59)
			{
				break;
			}
		}
		exit(0);
	}
	LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "lic info:"<<nLicRet);
	//读取配置文件
	int nRet = 0;
	string strExePath = GetExeFileExistDir() + "/Server.ini";
	char *strConfigFilePath = (char*)strExePath.c_str();

	//test:
	char szPN[20];
	memset(szPN, 0, 20);
	sprintf(szPN, "p_%d", 1);
	char szprocess[150];
	memset(szprocess, 0, 150);
	GetPrivateProfileString("info", szPN, NULL, szprocess, 150, strConfigFilePath);

	char szUrl[50];
	memset(szUrl, 0, 50);
	GetPrivateProfileString("info", "url", NULL, szUrl, 50, strConfigFilePath);

	char szRmID[50];
	memset(szRmID, 0, 50);
	GetPrivateProfileString("info", "RmId", NULL, szRmID, 50, strConfigFilePath);

	char szGuid[50];
	memset(szGuid, 0, 50);
	GetPrivateProfileString("info", "id", NULL, szGuid, 50, strConfigFilePath);
	string strGuid(szGuid);

	//校验键盘值：
	int nKeyStatus = GetPrivateProfileInt("info", "keystu", 7, strConfigFilePath);
	if (nKeyStatus == 6)
	{
		int nKey = GetPrivateProfileInt("info", "key", VK_ESCAPE, strConfigFilePath);
		char szVal = nKey;
		keybd_event(szVal, MapVirtualKey(szVal, 0), KEYEVENTF_KEYUP, 0);
		LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "[huqb] key is not reset:" << nKey<<" reset it!");
	}
	//记录重启动作
	int nRunstatus = GetPrivateProfileInt("info", "runstatus", 0, strConfigFilePath);
	if (nRunstatus == 2)
	{
		g_bLoginSuccess = nRunstatus;
		_beginthread(ExceptRunStatusThread, 0, NULL);
	}

	string strHostIp = SYSTEMUTIL::GetLocalIP();
	string strMac = SYSTEMUTIL::GetLocalMacAdress();
	LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "$$$:" << strGuid.c_str());
	int nPos = strMac.find(":");
	while (nPos > 0)
	{
		strMac.replace(nPos,1,"");
		nPos = strMac.find(":");
	}
	
	string strHostName = SYSTEMUTIL::GetLocalHostName();

	if (strGuid.empty())
	{
		strGuid = strMac;//CreateGuidString(false);
		WritePrivateProfileString("info", "id", (char*)strGuid.c_str(), strConfigFilePath);
	}
	else
	{
		if (strGuid.length() >= 32)
		{
			strGuid = strMac;
			WritePrivateProfileString("info", "id", (char*)strGuid.c_str(), strConfigFilePath);
		}
	}
	
	//string strJsonContent = "?hostName=" + strGuid;
	//strJsonContent += "&";
	//strJsonContent += "interIp=" + strIp;
	//strJsonContent += "&";
	//strJsonContent += "mac=" + strMac;
	//strJsonContent += "&";
	//strJsonContent += "hostIp=" + strHostIp;

	char szContent[2048];

	sprintf_s(szContent, "{\"id\":\"%s\",\
							\"ip\":\"%s\",\
							\"port\":\"554\",\
							\"rmId\":\"%s\",\
							\"runState\":0\
							}", strGuid.c_str(), strHostIp.c_str(), szRmID);
	

	string strJsonContent = szContent;

	string strResult = "";
	string strUrl(szUrl);
	strUrl += "/vm/";
	nRet = g_cHttpUtil.PostHttp(strUrl, strJsonContent, strResult, strJsonContent.length());
	if (nRet != 0)
	{
		LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "upload mathine info failed，sleep().....");
		//while (nRet != 0)
		//{
		//	Sleep(5000);
		//	nRet = g_cHttpUtil.PostHttp(strUrl, strJsonContent, strResult, strJsonContent.length());
		//}
	}

	nPos = strResult.find("\"id\":\"");//Find("\"ip\":\"");
	if (nPos > 0)
	{
		string strId = strResult.substr(nPos+6, strResult.length() - nPos - 6);
		nPos = strId.find("\",");
		if (nPos > 0)
		{
			strGuid = strId.substr(0,nPos);
			WritePrivateProfileString("info", "id", (char*)strGuid.c_str(), strConfigFilePath);
			LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "&&&:" << strGuid);
		}
		else
		{
			LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "regist exception," << strResult.c_str());
		}
	}
		

	int  cx = GetSystemMetrics(SM_CXFULLSCREEN);
	if (cx == 1920)
	{
		g_nSleepMillSec = 10;
	}
	return nRet;
}

void UserCallback(int nUserNum, int nStatus)
{
	g_nUserNum = nUserNum;
	LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "[rtsp]USer envent,use num:" << nUserNum);
	if (g_nUserNum > 0)
	{
		g_nUserStatus = 1;
	}
	else
	{
		g_nUserStatus = 2;
	}
}

void BroadcastEventCb(int nEventType)
{
	int nStatus = 0;
	if (g_nUserStatus == 1 || g_bLoginSuccess)
	{
		nStatus = 1;
	}
	CBroadcastRecver::getInstance().setMatchineInfo(nStatus, 0);
	LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "Recv msg,check machine status:"<<nStatus);
}

//用来提升系统权限
//更改LookupPrivilegeValue的第二个参数即可  
BOOL EnableShutDownPriv()
{
	HANDLE hToken = NULL;
	TOKEN_PRIVILEGES tkp = { 0 };
	//打开当前程序的权限令牌  
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
	{
		return FALSE;
	}
	//获得某一特定权限的权限标识LUID，保存在tkp中  
	if (!LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid))
	{
		CloseHandle(hToken);
		return FALSE;
	}
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	//调用AdjustTokenPrivileges来提升我们需要的系统权限  
	if (!AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof(TOKEN_PRIVILEGES), NULL, NULL))
	{
		CloseHandle(hToken);
		return FALSE;
	}
	return TRUE;
}

long __stdcall callback(_EXCEPTION_POINTERS*   excp)
{
	LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "EXCEPTION happened.");
	return   EXCEPTION_EXECUTE_HANDLER;
}

int _tmain(int argc, _TCHAR* argv[])
{
	
	//启动配置和日志
//	NSDumpFile::RunCrashHandler();
	LogInit("CaptureServer_0");
	LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "server Start, InitLog......");

	//捕获异常
	SetUnhandledExceptionFilter(callback);

	int nRet = InitConfig();
	if (nRet == 0)//启动状态上报线程
	{
		_beginthread(VmStatusThread, 0, NULL);
		LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "VM status upload init......");
	}
	if (!EnableShutDownPriv())
	{
		LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "LookupPrivilegeValue failed......");
	}

	//初始化com组件
	CoInitialize(NULL);
	//初始化I/O线程
//	_beginthread(IOServThread, 0, NULL);

	_beginthread(IOUdpServThread, 0, NULL);
	LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "IO server Init......");

	//启动广播接收服务
//	CBroadcastRecver::getInstance().startBroadcastRecv(BroadcastEventCb);

	//启动推流服务
	LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "start media!");
	StartMediaServer(UserCallback);

	while (g_nUserNum<1)
	{
		Sleep(100);
	}
	Sleep(1000);
	//初始化NVIDIA硬件
	bRunning = false;
	while (TRUE)
	{
		switch (g_nUserStatus)
		{
		case 0:
			{
				Sleep(1000);
			}
			break;
		case 1:
			{
				if (!bRunning)
				{//run capture sdk
					  
					bRunning = true;
					Sleep(50);
					printf("user Enter success! capture thread start.\n");
					LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "user login success! capture video thread start.");
					SetBufferCallback(h264BufferCallback, mouseRgbaCallback);
					StartCapture(g_nCapWidth,g_nCapHeight,g_nCapBps,g_nCapFps);
					LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "capture info:" << g_nCapWidth << "," << g_nCapHeight << "," << g_nCapBps << "," << g_nCapFps);
					//启动音频
					bool b = g_OutputRecord.StartCapture(AACDataCb);
					LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "capture audio thread start.ret:"<<b);
					//唤醒屏幕
					for (int n = 0; n < 30; n++)
					{
						mouse_event(MOUSEEVENTF_MOVE, n, n, 0, 0);
						Sleep(20);
					}
					 
				}
				else
				{
					Sleep(1000);
				}
			}
			break;
		case 2:
			{
				
				  printf("user leave success! \n");
				  LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "user leave begin!");
				  if (bRunning)
				  {//relase capture sdk
					  bRunning = false;
					  EndCapture();
					  LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "user leave 1!");
					  g_OutputRecord.StopCapture();
					  LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "user leave 2!");

					  //StopMediaServer();
					  //LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "stop media!");
				  }
				  g_nUserStatus = 0;
				  LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "user leave success!");
			}
			break;
		}
	}
	g_cPcm2aacIns.StopPcmEncode();
	CoUninitialize();

	return 0;
}

