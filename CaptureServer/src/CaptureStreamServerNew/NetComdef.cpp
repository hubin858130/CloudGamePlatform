#include "stdafx.h"
#include "NetComdef.h"

#include <stdio.h>
#include <windows.h>

#include "EventSelectServer.h"
#include "MsgQueue.h"
#include "Util.h"

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

#define TYPE_BUINSESS_REBOOTMEDIA  2002//重启RTSP服务
#define TYPE_BUINSESS_RECONNECTMEDIA  2003//重现连接rtsp服务

// login logout
public static final int TYPE_BUINSESS_LOGIN = 2100;
public static final int TYPE_BUINSESS_LOGOUT = 2101;
public static final int TYPE_BUINSESS_LOGOFF = 2102;//[20180712]注销 关机 重启命令处理
public static final int TYPE_BUINSESS_SHUTDOWN = 2103;
public static final int TYPE_BUINSESS_REBOOT = 2104;
//test
public static final int TYPE_TEST_LOOP_BETWEEN_SERVER_AND_CLIENT = 2200
*/

void DoKeyEvent(char szVal,char szScan,long lFlag, int nKeyType)
{
	//记录键盘
	string strExePath = GetExeFileExistDir() + "/Server.ini";
	char *strConfigFilePath = (char*)strExePath.c_str();

	//test:
	char szPN[20];
	memset(szPN, 0, 20);
	sprintf(szPN, "%d", szVal);
	WritePrivateProfileString("info", "key", szPN, strConfigFilePath);
	memset(szPN, 0, 20);
	sprintf(szPN, "%d", nKeyType);
	WritePrivateProfileString("info", "keystu", szPN, strConfigFilePath);
	/*	if (szVal >= 0x41 && szVal <= 0x5A)
	{
	if (nKeyType == 6)
	{
	HWND wnd;//窗口句柄
	wnd = GetForegroundWindow();//获得当前激活的窗口句柄
	DWORD SelfThreadId = GetCurrentThreadId();//获取本身的线程ID
	DWORD ForeThreadId = GetWindowThreadProcessId(wnd, NULL);//根据窗口句柄获取线程ID
	AttachThreadInput(ForeThreadId, SelfThreadId, true);//附加线程
	wnd = GetFocus();//获取具有输入焦点的窗口句柄
	AttachThreadInput(ForeThreadId, SelfThreadId, false);//取消附加的线程
	PostMessage(wnd, WM_CHAR, WPARAM(szVal & 0xFF), 0);//发送一个字消息
	}
	}
	else*/
	{
		INPUT input[1];
		if (nKeyType == 6)
		{
			keybd_event(szVal, MapVirtualKey(szVal, MAPVK_VK_TO_VSC), 0, 0);
			/*input[0].ki.wVk = szVal;
			input[0].type = INPUT_KEYBOARD;
			SendInput(1, input, sizeof(INPUT));*/
			//LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "value:" << szVal << "scan:" << MapVirtualKey(szVal, 0) << " sscan:" << szScan);
		}
		if (nKeyType == 7)
		{
			keybd_event(szVal, MapVirtualKey(szVal, MAPVK_VK_TO_VSC), KEYEVENTF_KEYUP, 0);

			//LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "value:" << szVal << "scan:" << MapVirtualKey(szVal, 0) << " sscan:" << szScan);
			/*input[0].ki.wVk = szVal;
			input[0].type = INPUT_KEYBOARD;
			input[0].ki.dwFlags = KEYEVENTF_KEYUP;
			SendInput(1, input, sizeof(INPUT));*/
		}
	//	keybd_event(szVal, szScan, lFlag, 0);
	}
}

long g_lTime = 0;
int g_nMouseModel = 0;
int nWidth = 1280;
int nHeight = 720;
int DealMouseAndKeyboard(string strContent)
{
	int nNetType = -1;
	int nPos = strContent.find("{");
	if (nPos<0)
	{
		LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "not find { :" << strContent.c_str());
	}
	string strExePath = GetExeFileExistDir() + "\\Server.ini";
	char *strConfigFilePath = (char*)strExePath.c_str();
	char szPN[20];
	memset(szPN, 0, 20);
	char szprocess[150];
	memset(szprocess, 0, 150);

	while (nPos > -1)
	{
		int nPosRight = strContent.find("}");
		if (nPosRight > 0)
		{
			string strMsg = strContent.substr(nPos, nPosRight - nPos);
			strContent = strContent.substr(nPosRight + 1, strContent.length() - nPosRight - 1);
			nPos = strContent.find("{");
			int nMsgPos = strMsg.find("type\":");
			if (nMsgPos > 0)
			{

				int nMsgPosRight = strMsg.find(",");
				string strType = strMsg.substr(nMsgPos + 6, nMsgPosRight - nMsgPos - 6);
				//				LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "type:" << strType.c_str() << " msg:" << strMsg.c_str());
				int nType = atoi(strType.c_str());
				nNetType = nType;
				if (nType == 100)
				{
					//if (g_IoStatusCallback != NULL)
					//{
					//	g_IoStatusCallback(nType, NULL);
					//}
					g_nMouseModel = 0;
					break;
				}
				if (nType == 101)
				{
					//if (g_IoStatusCallback != NULL)
					//{
					//	g_IoStatusCallback(nType, NULL);
					//}
					g_nMouseModel = 1;
					break;
				}
				if (nType == 0 || nType>4)
				{
					nMsgPos = strMsg.find("[");
					if (nMsgPos > 0)
					{
						nPosRight = strMsg.find("]");
						if (nPosRight < 0)
						{
							LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "not find ] :" << strContent.c_str());
							break;
						}
						strMsg = strMsg.substr(nMsgPos + 1, nPosRight - nMsgPos - 1);

						nMsgPos = strMsg.find(",");
						string strX = strMsg.substr(0, nMsgPos);
						strMsg = strMsg.substr(nMsgPos + 1, strMsg.length() - nMsgPos - 1);
						nMsgPos = strMsg.find(",");
						string strY = strMsg.substr(0, nMsgPos);
						string strExtern = strMsg.substr(nMsgPos + 1, strMsg.length() - nMsgPos - 1);
						int nX = atoi(strX.c_str());
						int nY = atoi(strY.c_str());
						int nExtern = atoi(strExtern.c_str());

						int nUserId = 0;
						int nToken = 0;
						//LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "Move x:" << nX << " y:"<<nY);

						//鼠标移动和键盘
						//						INPUT input[1];
						char szV = nX;
						char szScan = nY;
						static int nMoveTimes = 0;
						switch (nType)
						{
						case 0:
						{//SetCursorPos(nX, nY);
							//LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "time:" << nExtern << " Move x:" << nX << " y:" << nY << " times:" << nMoveTimes++);
							if (g_nMouseModel == 0)
							{
								mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, nX * 65535 / nWidth, nY * 65535 / nHeight, 0, 0);
							}
							else
							{
								//计算偏移量
								//float fFactor = 1.0f;
								//
								//if (nExtern != 0)
								//{
								// fFactor = (float)MOUSE_RATE_BASE / (float)nExtern;;
								// if (fFactor > 1)
								// {
								//  fFactor *= MOUSE_RATE;
								// }
								// if (fFactor < 1)
								// {
								// // fFactor /= MOUSE_RATE;
								// }
								//}

								mouse_event(MOUSEEVENTF_MOVE, nX, nY, 0, 0);

							}
						}
						break;
						case 5:
							//滚轮
							if (nX == 0)
							{
								mouse_event(MOUSEEVENTF_WHEEL, 0, 0, 0 - 100, 0);
							}
							else
							{
								mouse_event(MOUSEEVENTF_WHEEL, 0, 0, 100, 0);
							}
							break;
						case 6:
							DoKeyEvent(szV, szScan, nExtern, 6);
							//LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "keydown value:" << nX);
							/*memset(input, 0, sizeof(input));
							input[0].ki.wVk = szV;
							input[0].type = INPUT_KEYBOARD;
							SendInput(1, input, sizeof(INPUT));*/
							break;
						case 7:
							DoKeyEvent(szV, szScan, nExtern, 7);
							//LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "keyup value:" << nX);
							/*memset(input, 0, sizeof(input));
							input[0].ki.wVk = 0;
							input[0].type = INPUT_KEYBOARD;
							input[0].ki.dwFlags = KEYEVENTF_KEYUP;
							SendInput(1, input, sizeof(INPUT));*/
							break;
						case 8://心跳//huqb 20180522
							//CMsgQueue::getInstance().pushSendMsgToQueue("received hb!");
							break;
						case 9: //校验分辨率
						{
							LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "recv change resolution msg,resultion:" << nX);
							switch (nX)
							{
							case 0:
								nWidth = 1280;
								nHeight = 720;
								break;
							case 1:
								nWidth = 1920;
								nHeight = 1080;
								break;
							default:
								nWidth = 1280;
								nHeight = 720;
								break;
							}
							int currentWidth = GetSystemMetrics(SM_CXSCREEN);
							int currentHeight = GetSystemMetrics(SM_CYSCREEN);
							if (nWidth != currentWidth&&nHeight != currentHeight)
							{
								DEVMODE lpDevMode;
								lpDevMode.dmBitsPerPel = 32;
								lpDevMode.dmPelsWidth = nWidth;
								lpDevMode.dmPelsHeight = nHeight;
								lpDevMode.dmSize = sizeof(lpDevMode);
								lpDevMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;
								LONG result;
								result = ChangeDisplaySettings(&lpDevMode, 0);
								if (result == DISP_CHANGE_SUCCESSFUL)
								{
									ChangeDisplaySettings(&lpDevMode, CDS_UPDATEREGISTRY);
									LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "change resolution success:" << nX << "old wh:" << currentWidth << "," << currentHeight << ". new wh:" << nWidth << "," << nHeight << ".");
								}
								else
								{
									ChangeDisplaySettings(NULL, 0);
									LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "change resolution failed:" << nX << "old wh:" << currentWidth << "," << currentHeight << ". new wh:" << nWidth << "," << nHeight << ".");

								}
							}
						}
						break;
						case 1000://设置启动进程
							//int nProgress = nX;
							sprintf(szPN, "p_%d", nX);
							GetPrivateProfileString("info", szPN, NULL, szprocess, 150, strConfigFilePath);
							ShellExecute(NULL, "open", szprocess, NULL, NULL, SW_SHOWNORMAL);
							//switch (nX)//progress id
							//{
							//case 0:
							//	ShellExecute(NULL, "open", "C:\\Program Files\\腾讯游戏\\英雄联盟\\TCLS\\Client.exe", NULL, NULL, SW_SHOWNORMAL);
							//	break;
							//case 1:
							//	ShellExecute(NULL, "open", "C:\\Program Files (x86)\\Steam\\Steam.exe", NULL, NULL, SW_SHOWNORMAL);
							//	break;
							//case 2:
							//	//ShellExecute(NULL, "open", "C:\\Program Files (x86)\\Tencent\\QQ\\Bin\\QQScLauncher.exe", NULL, NULL, SW_SHOW);
							//	break;
							//}
							LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "Client request start progress:" << nX);
							break;
						case 2002://重启mediaserver
							LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "recv reboot mediaserver cmd.");
							break;
						case 1001://获取用户ID和Token

							/*g_cVideoEnginesIns.GetUseridAndToken(nUserId, nToken);
							char szBuffer[200];
							memset(szBuffer, 0, 200);                                                                                                                                              
							sprintf(szBuffer, "{\"type\":%d,\"value\":[\"id\":%d,\"token\":%d]}", 2001, nUserId, nToken);
							CMsgQueue::getInstance().pushSendMsgToQueue(szBuffer);
							LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "Client request id:" << szBuffer);*/
							break;
						case 2101:
							//if (g_IoStatusCallback != NULL)
							//{
							//	g_IoStatusCallback(3, 0);
							//}
							break;
						case 2102://logoff
						{
							LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "recv logoff cmd.");
//							ReSetWindows(EWX_REBOOT, TRUE);//EWX_LOGOFF
						}
						break;
						case 2103://shutdown
						{
							LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "recv shutdown cmd.");
							//						ReSetWindows(EWX_SHUTDOWN, TRUE);
						}
						break;
						case 2104://reboot
						{
							LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "recv reboot cmd.");
							string strExePath = GetExeFileExistDir() + "/Server.ini";
							char *strConfigFilePath = (char*)strExePath.c_str();

							WritePrivateProfileString("info", "runstatus", "2", strConfigFilePath);
							ReSetWindows(EWX_REBOOT, TRUE);
						}
						break;
						case 2200://test 链路
						{
							SYSTEMTIME timeSys;
							GetLocalTime(&timeSys);
							long lTime = timeSys.wMilliseconds + timeSys.wSecond * 1000 + timeSys.wMinute * 60000;
							g_lTime = nX;

							int nT = lTime - g_lTime;
							if (nT < 0)
							{
								nT = lTime - (g_lTime / 100);
							}
							LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "recv cycle msg: send time:" << g_lTime << " current time:" << lTime << " diff:" << (nT));
						}
						break;
						}
					}
					else
					{
						LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "not find [ :" << strContent.c_str());
					}
				}
				else
				{//点击事件
					switch (nType)
					{
					case 1:
					{
						//long l1 = GetTickCount();
						mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
						//long l2 = GetTickCount();
						SYSTEMTIME timeSys;
						GetLocalTime(&timeSys);
						g_lTime = timeSys.wMilliseconds + timeSys.wSecond * 1000 + timeSys.wMinute * 60000;
	//					CMsgQueue::getInstance().pushSendMsgToQueue("test send msg:server2client!");
						/*	long l3 = GetTickCount();
						printf("\n2-1:%d,3-2:%d,3-1:%d\n", l2 - l1, l3 - l2, l3 - l1);*/
					}
					break;
					case 2:
						mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
						break;
					case 3:
						mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
						break;
					case 4:
						mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
						//test send msg:
						//CMsgQueue::getInstance().pushSendMsgToQueue("test send msg:server2client!");
						break;
					}
				}
			}
			else
			{
				LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "not find type\\ :" << strContent.c_str());
			}
		}
		else
		{
			nPos = -1;
			LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "not find } :" << strContent.c_str());
		}
	}
	return nNetType;
}