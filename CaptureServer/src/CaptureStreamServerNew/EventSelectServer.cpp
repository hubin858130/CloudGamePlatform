///////////////////////////////////////////
// EventSelectServer.cpp文件

#include "stdafx.h"
#include "./common/initsock.h"

#include <stdio.h>
#include <windows.h>

#include "EventSelectServer.h"
#include "MsgQueue.h"
#include "Util.h"

#include <process.h>
#include <string>
using std::string;

#define   MOUSE_RATE_BASE    15000
#define   MOUSE_RATE         4

DWORD WINAPI ServerThread(LPVOID lpParam);
// 线程列表
PTHREAD_OBJ g_pThreadList;		// 指向线程对象列表表头
CRITICAL_SECTION g_cs;			// 同步对此全局变量的访问


// 状态信息
LONG g_nTatolConnections;		// 总共连接数量
LONG g_nCurrentConnections;		// 当前连接数量

// 初始化Winsock库
CInitSock theSock;
OnEventUserIOStatus g_IoStatusCallback = NULL;

////当前鼠标运行模式
//int g_nMouseModel = 0;
//
//int nWidth = 1280;
//int nHeight = 720;

// 申请一个套节字对象，初始化它的成员
PSOCKET_OBJ GetSocketObj(SOCKET s)
{
	PSOCKET_OBJ pSocket = (PSOCKET_OBJ)::GlobalAlloc(GPTR, sizeof(SOCKET_OBJ));
	if (pSocket != NULL)
	{
		pSocket->s = s;
		pSocket->event = ::WSACreateEvent();
		pSocket->bSendTag = false;
		pSocket->bBeginHeatbeat = false;
		pSocket->pHeartInfo = NULL;
	}
	return pSocket;
}

// 释放一个套节字对象
void FreeSocketObj(PSOCKET_OBJ pSocket)
{
	::CloseHandle(pSocket->event);
	if (pSocket->s != INVALID_SOCKET)
	{
		::closesocket(pSocket->s);
	}
	if (pSocket->pHeartInfo != NULL)
	{
		delete pSocket->pHeartInfo;
		pSocket->pHeartInfo = NULL;
	}
	::GlobalFree(pSocket);
	pSocket = NULL;
}

// 申请一个线程对象，初始化它的成员，并将它添加到线程对象列表中
PTHREAD_OBJ GetThreadObj()
{
	PTHREAD_OBJ pThread = (PTHREAD_OBJ)::GlobalAlloc(GPTR, sizeof(THREAD_OBJ));
	if (pThread != NULL)
	{
		::InitializeCriticalSection(&pThread->cs);
		// 创建一个事件对象，用于指示该线程的句柄数组需要重组
		pThread->events[0] = ::WSACreateEvent();

		// 将新申请的线程对象添加到列表中
		::EnterCriticalSection(&g_cs);
		pThread->pNext = g_pThreadList;
		g_pThreadList = pThread;
		::LeaveCriticalSection(&g_cs);
	}
	return pThread;
}

// 释放一个线程对象，并将它从线程对象列表中移除
void FreeThreadObj(PTHREAD_OBJ pThread)
{
	// 在线程对象列表中查找pThread所指的对象，如果找到就从中移除
	::EnterCriticalSection(&g_cs);
	PTHREAD_OBJ p = g_pThreadList;
	if (p == pThread)		// 是第一个？
	{
		g_pThreadList = p->pNext;
	}
	else
	{
		while (p != NULL && p->pNext != pThread)
		{
			p = p->pNext;
		}
		if (p != NULL)
		{
			// 此时，p是pThread的前一个，即“p->pNext == pThread”
			p->pNext = pThread->pNext;
		}
	}
	::LeaveCriticalSection(&g_cs);

	// 释放资源
	::CloseHandle(pThread->events[0]);
	::DeleteCriticalSection(&pThread->cs);
	::GlobalFree(pThread);
}

// 重新建立线程对象的events数组
void RebuildArray(PTHREAD_OBJ pThread)
{
	::EnterCriticalSection(&pThread->cs);
	PSOCKET_OBJ pSocket = pThread->pSockHeader;
	int n = 1;	// 从第1个开始写，第0个用于指示需要重建了
	while (pSocket != NULL)
	{
		pThread->events[n++] = pSocket->event;
		pSocket = pSocket->pNext;
	}
	::LeaveCriticalSection(&pThread->cs);
}

/////////////////////////////////////////////////////////////////////

// 向一个线程的套节字列表中插入一个套节字
BOOL InsertSocketObj(PTHREAD_OBJ pThread, PSOCKET_OBJ pSocket)
{
	BOOL bRet = FALSE;
	::EnterCriticalSection(&pThread->cs);
	if (pThread->nSocketCount < WSA_MAXIMUM_WAIT_EVENTS - 1)
	{
		if (pThread->pSockHeader == NULL)
		{
			pThread->pSockHeader = pThread->pSockTail = pSocket;
		}
		else
		{
			pThread->pSockTail->pNext = pSocket;
			pThread->pSockTail = pSocket;
		}
		pThread->nSocketCount++;
		bRet = TRUE;
	}
	::LeaveCriticalSection(&pThread->cs);

	// 插入成功，说明成功处理了客户的连接请求
	if (bRet)
	{
		::InterlockedIncrement(&g_nTatolConnections);
		::InterlockedIncrement(&g_nCurrentConnections);
	}
	if (g_IoStatusCallback != NULL)
	{
		g_IoStatusCallback(0, NULL);
	}
	return bRet;
}

// 将一个套节字对象安排给空闲的线程处理
void AssignToFreeThread(PSOCKET_OBJ pSocket)
{
	pSocket->pNext = NULL;

	::EnterCriticalSection(&g_cs);
	PTHREAD_OBJ pThread = g_pThreadList;
	// 试图插入到现存线程
	while (pThread != NULL)
	{
		if (InsertSocketObj(pThread, pSocket))
			break;
		pThread = pThread->pNext;
	}

	// 没有空闲线程，为这个套节字创建新的线程
	if (pThread == NULL)
	{
		pThread = GetThreadObj();
		InsertSocketObj(pThread, pSocket);
		::CreateThread(NULL, 0, ServerThread, pThread, 0, NULL);
	}
	::LeaveCriticalSection(&g_cs);

	// 指示线程重建句柄数组
	::WSASetEvent(pThread->events[0]);
}

// 从给定线程的套节字对象列表中移除一个套节字对象
void RemoveSocketObj(PTHREAD_OBJ pThread, PSOCKET_OBJ pSocket)
{
	::EnterCriticalSection(&pThread->cs);

	// 在套节字对象列表中查找指定的套节字对象，找到后将之移除
	PSOCKET_OBJ pTest = pThread->pSockHeader;
	if (pTest == pSocket)
	{
		if (pThread->pSockHeader == pThread->pSockTail)
			pThread->pSockTail = pThread->pSockHeader = pTest->pNext;
		else
			pThread->pSockHeader = pTest->pNext;
	}
	else
	{
		while (pTest != NULL && pTest->pNext != pSocket)
			pTest = pTest->pNext;
		if (pTest != NULL)
		{
			if (pThread->pSockTail == pSocket)
				pThread->pSockTail = pTest;
			pTest->pNext = pSocket->pNext;
		}
	}
	pThread->nSocketCount--;

	::LeaveCriticalSection(&pThread->cs);

	// 指示线程重建句柄数组
	::WSASetEvent(pThread->events[0]);

	// 说明一个连接中断
	::InterlockedDecrement(&g_nCurrentConnections);
	//回调给主线程，告知有客户失去IO连接
	if (g_IoStatusCallback != NULL)
	{
		g_IoStatusCallback(1, NULL);
	}
}

// 获取系统的当前时间，单位微秒(us)
int64_t GetSysTimeMicros()
{
#ifdef _WIN32
	// 从1601年1月1日0:0:0:000到1970年1月1日0:0:0:000的时间(单位100ns)
#define EPOCHFILETIME   (116444736000000000UL)
	FILETIME ft;
	LARGE_INTEGER li;
	int64_t tt = 0;
	GetSystemTimeAsFileTime(&ft);
	li.LowPart = ft.dwLowDateTime;
	li.HighPart = ft.dwHighDateTime;
	// 从1970年1月1日0:0:0:000到现在的微秒数(UTC时间)
	tt = (li.QuadPart - EPOCHFILETIME) / 10;
	return tt;
#else
	timeval tv;
	gettimeofday(&tv, 0);
	return (int64_t)tv.tv_sec * 1000000 + (int64_t)tv.tv_usec;
#endif // _WIN32
	return 0;
}

/*
//I/O 相关消息
public static final int TYPE_MOUSE_MOVE = 0;
public static final int TYPE_MOUSE_LEFT_DOWN = 1;
public static final int TYPE_MOUSE_LEFT_UP = 2;
public static final int TYPE_MOUSE_RIGHT_DOWN = 3;
public static final int TYPE_MOUSE_RIGHT_UP = 4;
public static final int TYPE_MOUSE_WHEEL = 5;
public static final int TYPE_KEY_DOWN = 6;
public static final int TYPE_KEY_UP = 7;
public static final int TYPE_MSG_HB = 8;//心跳
// mouse Model相关消息
public static final int TYPE_MODEL_NOMAL = 100;
public static final int TYPE_MODEL_GAME = 101;

//其它业务消息
public static final int TYPE_BUINSESS_SERVERTYPE = 1000;//启动指定进程
public static final int TYPE_BUINSESS_GETTOKEN = 1001;//请求获取userid和token
public static final int TYPE_BUINSESS_GETTOKEN_Rsps = 2001;//反馈userid和token
// login logout
public static final int TYPE_BUINSESS_LOGIN = 2100;
public static final int TYPE_BUINSESS_LOGOUT = 2101;
public static final int TYPE_BUINSESS_LOGOFF = 2102;//[20180712]注销 关机 重启命令处理
public static final int TYPE_BUINSESS_SHUTDOWN = 2103;
public static final int TYPE_BUINSESS_REBOOT = 2104;
//test
public static final int TYPE_TEST_LOOP_BETWEEN_SERVER_AND_CLIENT = 2200
*/
//void DoKeyEvent(char szVal, int nKeyType)
//{
//	/*	if (szVal >= 0x41 && szVal <= 0x5A)
//	{
//	if (nKeyType == 6)
//	{
//	HWND wnd;//窗口句柄
//	wnd = GetForegroundWindow();//获得当前激活的窗口句柄
//	DWORD SelfThreadId = GetCurrentThreadId();//获取本身的线程ID
//	DWORD ForeThreadId = GetWindowThreadProcessId(wnd, NULL);//根据窗口句柄获取线程ID
//	AttachThreadInput(ForeThreadId, SelfThreadId, true);//附加线程
//	wnd = GetFocus();//获取具有输入焦点的窗口句柄
//	AttachThreadInput(ForeThreadId, SelfThreadId, false);//取消附加的线程
//	PostMessage(wnd, WM_CHAR, WPARAM(szVal & 0xFF), 0);//发送一个字消息
//	}
//	}
//	else*/
//	{
//		if (nKeyType == 6)
//		{
//			keybd_event(szVal, MapVirtualKey(szVal, 0), 0, 0);
//		}
//		if (nKeyType == 7)
//		{
//			keybd_event(szVal, MapVirtualKey(szVal, 0), KEYEVENTF_KEYUP, 0);
//		}
//	}
//}
//
//long g_lTime = 0;
//void DealMouseAndKeyboard(string strContent)
//{
//	int nPos = strContent.find("{");
//	if (nPos<0)
//	{
//		LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "not find { :" << strContent.c_str());
//	}
//	string strExePath = GetExeFileExistDir() + "\\Server.ini";
//	char *strConfigFilePath = (char*)strExePath.c_str();
//	char szPN[20];
//	memset(szPN, 0, 20);
//	char szprocess[150];
//	memset(szprocess, 0, 150);
//
//	while (nPos > -1)
//	{
//		int nPosRight = strContent.find("}");
//		if (nPosRight > 0)
//		{
//			string strMsg = strContent.substr(nPos, nPosRight - nPos);
//			strContent = strContent.substr(nPosRight + 1, strContent.length() - nPosRight - 1);
//			nPos = strContent.find("{");
//			int nMsgPos = strMsg.find("type\":");
//			if (nMsgPos > 0)
//			{
//				
//				int nMsgPosRight = strMsg.find(",");
//				string strType = strMsg.substr(nMsgPos + 6, nMsgPosRight - nMsgPos - 6);
////				LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "type:" << strType.c_str() << " msg:" << strMsg.c_str());
//				int nType = atoi(strType.c_str());
//				if (nType == 100)
//				{
//					if (g_IoStatusCallback != NULL)
//					{
//						g_IoStatusCallback(nType, NULL);
//					}
//					g_nMouseModel = 0;
//					break;
//				}
//				if (nType==101)
//				{
//					if (g_IoStatusCallback != NULL)
//					{
//						g_IoStatusCallback(nType, NULL);
//					}
//					g_nMouseModel = 1;
//					break;
//				}
//				if (nType == 0 || nType>4)
//				{
//					nMsgPos = strMsg.find("[");
//					if (nMsgPos > 0)
//					{
//						nPosRight = strMsg.find("]");
//						if (nPosRight < 0)
//						{
//							LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "not find ] :" << strContent.c_str());
//							break;
//						}
//						strMsg = strMsg.substr(nMsgPos + 1, nPosRight - nMsgPos - 1);
//
//						nMsgPos = strMsg.find(",");
//						string strX = strMsg.substr(0, nMsgPos);
//						strMsg = strMsg.substr(nMsgPos + 1, strMsg.length() - nMsgPos - 1);
//						nMsgPos = strMsg.find(",");
//						string strY = strMsg.substr(0, nMsgPos); 
//						string strExtern = strMsg.substr(nMsgPos + 1, strMsg.length() - nMsgPos - 1);
//						int nX = atoi(strX.c_str());
//						int nY = atoi(strY.c_str());
//						int nExtern = atoi(strExtern.c_str());
//
//						int nUserId = 0;
//						int nToken = 0;
//						//LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "Move x:" << nX << " y:"<<nY);
//
//						//鼠标移动和键盘
////						INPUT input[1];
//						char szV = nX;
//						switch (nType)
//						{
//						case 0:
//							{//SetCursorPos(nX, nY);
//								  if (g_nMouseModel == 0)
//								  {
//									mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, nX * 65535 / nWidth, nY * 65535 / nHeight, 0, 0);
//								  }
//								  else
//								  {
//									  //计算偏移量
//									  //float fFactor = 1.0f;
//									  //
//									  //if (nExtern != 0)
//									  //{
//										 // fFactor = (float)MOUSE_RATE_BASE / (float)nExtern;;
//										 // if (fFactor > 1)
//										 // {
//											//  fFactor *= MOUSE_RATE;
//										 // }
//										 // if (fFactor < 1)
//										 // {
//											// // fFactor /= MOUSE_RATE;
//										 // }
//									  //}
//
//									  mouse_event(MOUSEEVENTF_MOVE, nX, nY, 0, 0);
//
//								  }
//							}			
//							break;
//						case 5:
//							//滚轮
//							if (nX == 0)
//							{
//								mouse_event(MOUSEEVENTF_WHEEL, 0, 0, 0-100, 0);
//							}
//							else
//							{
//								mouse_event(MOUSEEVENTF_WHEEL, 0, 0, 100, 0);
//							}
//							break;
//						case 6:
//							DoKeyEvent(szV, 6);
//							//LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "keydown value:" << nX);
//							/*memset(input, 0, sizeof(input));
//							input[0].ki.wVk = szV;
//							input[0].type = INPUT_KEYBOARD;
//							SendInput(1, input, sizeof(INPUT));*/
//							break;
//						case 7:
//							DoKeyEvent(szV, 7);
//							//LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "keyup value:" << nX);
//							/*memset(input, 0, sizeof(input));
//							input[0].ki.wVk = 0;
//							input[0].type = INPUT_KEYBOARD;
//							input[0].ki.dwFlags = KEYEVENTF_KEYUP;
//							SendInput(1, input, sizeof(INPUT));*/
//							break;
//						case 8://心跳//huqb 20180522
//							//CMsgQueue::getInstance().pushSendMsgToQueue("received hb!");
//							break;
//						case 9: //校验分辨率
//							{
//								LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "recv change resolution msg,resultion:" << nX);
//								switch (nX)
//								{
//								case 0:
//									nWidth = 1280;
//									nHeight = 720;
//									break;
//								case 1:
//									nWidth = 1920;
//									nHeight = 1080;
//									break;
//								default:
//									nWidth = 1280;
//									nHeight = 720;
//									break;
//								}
//								int currentWidth = GetSystemMetrics(SM_CXSCREEN);
//								int currentHeight = GetSystemMetrics(SM_CYSCREEN);
//								if (nWidth != currentWidth&&nHeight != currentHeight)
//								{
//									DEVMODE lpDevMode;
//									lpDevMode.dmBitsPerPel = 32;
//									lpDevMode.dmPelsWidth = nWidth;
//									lpDevMode.dmPelsHeight = nHeight;
//									lpDevMode.dmSize = sizeof(lpDevMode);
//									lpDevMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;
//									LONG result;
//									result = ChangeDisplaySettings(&lpDevMode, 0);
//									if (result == DISP_CHANGE_SUCCESSFUL)
//									{
//										ChangeDisplaySettings(&lpDevMode, CDS_UPDATEREGISTRY);
//										LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "change resolution success:" << nX << "old wh:" << currentWidth << "," << currentHeight << ". new wh:" << nWidth << "," << nHeight << ".");
//									}
//									else
//									{
//										ChangeDisplaySettings(NULL, 0);
//										LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "change resolution failed:" << nX << "old wh:" << currentWidth << "," << currentHeight << ". new wh:" << nWidth << "," << nHeight << ".");
//
//									}
//								}
//							}
//							break;
//						case 1000://设置启动进程
//							//int nProgress = nX;
//							sprintf(szPN, "p_%d", nX);
//							GetPrivateProfileString("info", szPN, NULL, szprocess, 150, strConfigFilePath);
//							ShellExecute(NULL, "open", szprocess, NULL, NULL, SW_SHOWNORMAL);
//							//switch (nX)//progress id
//							//{
//							//case 0:
//							//	ShellExecute(NULL, "open", "C:\\Program Files\\腾讯游戏\\英雄联盟\\TCLS\\Client.exe", NULL, NULL, SW_SHOWNORMAL);
//							//	break;
//							//case 1:
//							//	ShellExecute(NULL, "open", "C:\\Program Files (x86)\\Steam\\Steam.exe", NULL, NULL, SW_SHOWNORMAL);
//							//	break;
//							//case 2:
//							//	//ShellExecute(NULL, "open", "C:\\Program Files (x86)\\Tencent\\QQ\\Bin\\QQScLauncher.exe", NULL, NULL, SW_SHOW);
//							//	break;
//							//}
//							LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "Client request start progress:" << nX);
//							break;
//						case 1001://获取用户ID和Token
//							
//							/*g_cVideoEnginesIns.GetUseridAndToken(nUserId, nToken);
//							char szBuffer[200];
//							memset(szBuffer, 0, 200);
//							sprintf(szBuffer, "{\"type\":%d,\"value\":[\"id\":%d,\"token\":%d]}", 2001, nUserId, nToken);
//							CMsgQueue::getInstance().pushSendMsgToQueue(szBuffer);
//							LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "Client request id:" << szBuffer);*/
//							break;
//						case 2101:
//							if (g_IoStatusCallback != NULL)
//							{
//								g_IoStatusCallback(3, 0);
//							}
//							break;
//						case 2102://logoff
//						{
//							LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "recv logoff cmd." );
//							//ReSetWindows(EWX_LOGOFF, TRUE);
//						}
//							break;
//						case 2103://shutdown
//						{
//							LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "recv shutdown cmd.");
//	//						ReSetWindows(EWX_SHUTDOWN, TRUE);
//						}
//							break;
//						case 2104://reboot
//						{
//							LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "recv reboot cmd.");
//							ReSetWindows(EWX_REBOOT, TRUE);
//						}
//							break;
//						case 2200://test 链路
//						{
//							SYSTEMTIME timeSys;
//							GetLocalTime(&timeSys);
//							long lTime = timeSys.wMilliseconds + timeSys.wSecond * 1000 + timeSys.wMinute * 60000;
//							LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "recv cycle msg: send time:" << g_lTime << " current time:" << lTime << " diff:" << (lTime - g_lTime));
//						}
//							break;
//						}
//					}
//					else
//					{
//						LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "not find [ :" << strContent.c_str());
//					}
//				}
//				else
//				{//点击事件
//					switch (nType)
//					{
//					case 1:
//						{
//							//long l1 = GetTickCount();
//							mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
//							//long l2 = GetTickCount();
//							SYSTEMTIME timeSys;
//							GetLocalTime(&timeSys);
//							g_lTime = timeSys.wMilliseconds + timeSys.wSecond * 1000 + timeSys.wMinute * 60000;
//							CMsgQueue::getInstance().pushSendMsgToQueue("test send msg:server2client!");
//						/*	long l3 = GetTickCount();
//							printf("\n2-1:%d,3-2:%d,3-1:%d\n", l2 - l1, l3 - l2, l3 - l1);*/
//						}
//						break;
//					case 2:
//						mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
//						break;
//					case 3:
//						mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
//						break;
//					case 4:
//						mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
//						//test send msg:
//						//CMsgQueue::getInstance().pushSendMsgToQueue("test send msg:server2client!");
//						break;
//					}
//				}
//			}
//			else
//			{
//				LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "not find type\\ :" << strContent.c_str());
//			}
//		}
//		else
//		{
//			nPos = -1;
//			LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "not find } :" << strContent.c_str());
//		}
//	}
//}

void NetHeartBeatThread(void* pParam)
{
	PSOCKET_OBJ pSocket = (PSOCKET_OBJ)pParam;
	
	while (true)
	{
		if (pSocket==NULL)
		{
			break;
		}
		long lCurTime = ::GetTickCount();
		//2s超时清理
		long lTimeSpace = lCurTime - pSocket->pHeartInfo->lLastTime;
		if (lTimeSpace > 1000)
		{
			RemoveSocketObj((PTHREAD_OBJ)pSocket->pHeartInfo->pThread, pSocket);
			FreeSocketObj(pSocket);
			LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "Client:"<< inet_ntoa(pSocket->addrRemote.sin_addr) << " 心跳超时:" << lTimeSpace<<"ms,断开链接。");
			break;
		}
//		LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "Client:" << inet_ntoa(pSocket->addrRemote.sin_addr) << " 心跳中:" << lTimeSpace<<" ms。");
		Sleep(500);
	}
}

void NetEventDealThread(void* pParam)
{
	while (true)
	{
		string strMsg = CMsgQueue::getInstance().getRecvMsgFromQueue();
		if (!strMsg.empty())
		{
			int nNetType = DealMouseAndKeyboard(strMsg);//huqb
			if (nNetType == 100 || nNetType == 101 || nNetType == 2101)
			{
				if (g_IoStatusCallback != NULL)
				{
					g_IoStatusCallback(nNetType, NULL);
				}
			}
		}
		else
		{
			Sleep(5);
		}
	}
}


BOOL HandleIO(PTHREAD_OBJ pThread, PSOCKET_OBJ pSocket)
{
	// 获取具体发生的网络事件
	WSANETWORKEVENTS event;
	::WSAEnumNetworkEvents(pSocket->s, pSocket->event, &event);
	do
	{
		if (event.lNetworkEvents & FD_READ)			// 套节字可读
		{
			if (event.iErrorCode[FD_READ_BIT] == 0)
			{
				char szHead[4];
				char szText[256];
				memset(szText, 0, 256);
				int nRecv = ::recv(pSocket->s, szHead, 4, 0);
				if (nRecv == 4)
				{
					int nBodyLen = (int)szHead[3];
					nRecv = ::recv(pSocket->s, szText, nBodyLen, 0);
					if (nRecv > 0)
					{
						//huqb
						string strContent = szText;
						CMsgQueue::getInstance().pushRecvMsgToQueue(strContent);
						

						//send(pSocket->s, szText, 4, 0);


						//test send msg:
						//CMsgQueue::getInstance().pushSendMsgToQueue("test send msg:server2client!");
					}
				}
				//记录心跳 所有消息都视为保活心跳（业务消息+心跳消息)
				if (pSocket->pHeartInfo!=NULL)
				{
					pSocket->pHeartInfo->lLastTime = ::GetTickCount();
				}
			}
			else
			{
				break;
			}
			//huqb 20180522
			if (!pSocket->bBeginHeatbeat)
			{
				pSocket->pHeartInfo = new NETHEARTBEATINFO;
				pSocket->pHeartInfo->pThread = pThread;
				pSocket->pHeartInfo->lLastTime = ::GetTickCount();
				_beginthread(NetHeartBeatThread, 0, (void*)pSocket);
				pSocket->bBeginHeatbeat = true;
			}
		}
		else if (event.lNetworkEvents & FD_CLOSE)	// 套节字关闭
		{
			break;
		}
		else if (event.lNetworkEvents & FD_WRITE)	// 套节字可写
		{
			if (event.iErrorCode[FD_WRITE_BIT] == 0)
			{
				//可以连续发送大量字节
				pSocket->bSendTag = true;
			}
			else
			{
				break;
			}
		}
		//send msg to client
		if (pSocket->bSendTag)
		{
			PMsgInfo pSendMsg = CMsgQueue::getInstance().getSendMsgFromQueue();
			if (pSendMsg!=NULL)
			{
				::send(pSocket->s, pSendMsg->szBuffer,pSendMsg->nBodyLen, 0);//huqb
			}
			delete pSendMsg;
			pSendMsg = NULL;
		}
		return TRUE;
	} while (FALSE);

	// 套节字关闭，或者有错误发生，程序都会转到这里来执行
	//RemoveSocketObj(pThread, pSocket);
	//FreeSocketObj(pSocket);

	return FALSE;
}

PSOCKET_OBJ FindSocketObj(PTHREAD_OBJ pThread, int nIndex) // nIndex从1开始
{
	// 在套节字列表中查找
	PSOCKET_OBJ pSocket = pThread->pSockHeader;
	while (--nIndex)
	{
		if (pSocket == NULL)
			return NULL;
		pSocket = pSocket->pNext;
	}
	return pSocket;
}

DWORD WINAPI ServerThread(LPVOID lpParam)
{
	// 取得本线程对象的指针
	PTHREAD_OBJ pThread = (PTHREAD_OBJ)lpParam;
	while (TRUE)
	{
		//	等待网络事件
		int nIndex = ::WSAWaitForMultipleEvents(
			pThread->nSocketCount + 1, pThread->events, FALSE, WSA_INFINITE, FALSE);
		nIndex = nIndex - WSA_WAIT_EVENT_0;
		// 查看受信的事件对象
		for (int i = nIndex; i<pThread->nSocketCount + 1; i++)
		{
			nIndex = ::WSAWaitForMultipleEvents(1, &pThread->events[i], TRUE, 1000, FALSE);
			if (nIndex == WSA_WAIT_FAILED || nIndex == WSA_WAIT_TIMEOUT)
			{
				continue;
			}
			else
			{
				if (i == 0)				// events[0]受信，重建数组
				{
					RebuildArray(pThread);
					// 如果没有客户I/O要处理了，则本线程退出
					if (pThread->nSocketCount == 0)
					{
						FreeThreadObj(pThread);
						return 0;
					}
					::WSAResetEvent(pThread->events[0]);
				}
				else					// 处理网络事件
				{
					// 查找对应的套节字对象指针，调用HandleIO处理网络事件
					PSOCKET_OBJ pSocket = (PSOCKET_OBJ)FindSocketObj(pThread, i);
					if (pSocket != NULL)
					{
						if (!HandleIO(pThread, pSocket))
							RebuildArray(pThread);
					}
					else
						printf(" Unable to find socket object \n ");
				}
			}
		}
	}
	return 0;
}

void SendClientThread(void* p)
{
	//int nX = 300;
	//int nY = 500;
	//while (true)
	//{
	//	mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, nX * 65535 / nWidth, nY * 65535 / nHeight, 0, 0);
	//	nX+=5;
	//	if (nX >= 1000)
	//	{
	//		nX = 300;
	//	}
	//	Sleep(5);
	//}
}

int IoDomain(OnEventUserIOStatus pStatusCb)
{
	//启动发送线程
	_beginthread(SendClientThread, 0, NULL);
	//启动业务接收处理线程
	_beginthread(NetEventDealThread, 0, NULL);
	USHORT nPort = 8627;	// 此服务器监听的端口号
	g_IoStatusCallback = pStatusCb;
	// 创建监听套节字
	SOCKET sListen = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);	
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(nPort);
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	if(::bind(sListen, (sockaddr*)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		printf(" Failed bind() \n");
		return -1;
	}
	::listen(sListen, 200);

	// 创建事件对象，并关联到监听的套节字
	WSAEVENT event = ::WSACreateEvent();
	::WSAEventSelect(sListen, event, FD_ACCEPT|FD_CLOSE);

	::InitializeCriticalSection(&g_cs);

	//init
	//nWidth = GetSystemMetrics(SM_CXSCREEN);
	//nHeight = GetSystemMetrics(SM_CYSCREEN);

	// 处理客户连接请求，打印状态信息
	while(TRUE)
	{
		int nRet = ::WaitForSingleObject(event, 5*1000);
		if(nRet == WAIT_FAILED)
		{
			printf(" Failed WaitForSingleObject() \n");
			break;
		}
		else if(nRet == WSA_WAIT_TIMEOUT)	// 定时显式状态信息
		{
			printf(" \n");
			printf("   TatolConnections: %d \n", g_nTatolConnections);
			printf(" CurrentConnections: %d \n", g_nCurrentConnections);
			continue;
		}
		else								// 有新的连接未决
		{
			::ResetEvent(event);
			// 循环处理所有未决的连接请求
			while(TRUE)
			{
				sockaddr_in si;
				int nLen = sizeof(si);
				SOCKET sNew = ::accept(sListen, (sockaddr*)&si, &nLen);
				if(sNew == SOCKET_ERROR)
					break;
				PSOCKET_OBJ pSocket = GetSocketObj(sNew);
				pSocket->addrRemote = si;
				::WSAEventSelect(pSocket->s, pSocket->event, FD_READ|FD_CLOSE|FD_WRITE);
				AssignToFreeThread(pSocket);
			}
		}
	}
	::DeleteCriticalSection(&g_cs);
	return 0;
}

