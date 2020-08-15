
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持



//message enmu
#define TYPE_MOUSE_MOVE  0
#define TYPE_MOUSE_LEFT_DOWN  1
#define TYPE_MOUSE_LEFT_UP  2
#define TYPE_MOUSE_RIGHT_DOWN  3
#define TYPE_MOUSE_RIGHT_UP  4
#define TYPE_MOUSE_WHEEL  5
#define TYPE_KEY_DOWN  6
#define TYPE_KEY_UP  7
#define TYPE_MSG_HB 8//心跳
#define TYPE_MSG_FBL 9 //resolution
#define TYPE_MODEL_NOMAL  100
#define TYPE_MODEL_GAME  101
#define TYPE_BUINSESS_SERVERTYPE  1000//启动指定进程
#define TYPE_BUINSESS_GETTOKEN  1001//请求获取userid和token
#define TYPE_BUINSESS_GETTOKEN_Rsps  2001//反馈userid和token
#define TYPE_BUINSESS_REBOOTMEDIA  2002//重启RTSP服务
#define TYPE_BUINSESS_RECONNECTMEDIA  2003//重现连接rtsp服务
#define TYPE_BUINSESS_LOGOFF  2102   //[20180712]注销 关机 重启命令处理
#define TYPE_BUINSESS_SHUTDOWN  2103
#define TYPE_BUINSESS_REBOOT  2104
#define TYPE_TEST_LOOP_BETWEEN_SERVER_AND_CLIENT  2200 //test cycle time


//status enmu
#define  TYPE_STATUS_RUN_OK				0
#define  TYPE_STATUS_NET_OK				1
#define  TYPE_STATUS_NET_LOST			2
#define  TYPE_STATUS_PLAY_OK			3
#define  TYPE_STATUS_PLAY_CONNECTING	4 //正在连接
#define  TYPE_STATUS_PLAY_ERROR			5
#define  TYPE_STATUS_PLAY_CLOSE			6


//browser
#define WM_URL_CHANGED				(WM_APP+1)
#define WM_LOAD_CHANGED				(WM_URL_CHANGED+1)
#define WM_TITLE_CHANGED			(WM_LOAD_CHANGED+1)
#define WM_CREATE_NEW_PAGE			(WM_USER+1)
#define WM_START_REMOTE				(WM_USER+2)
#define WM_CLOSE_REMOTE				(WM_USER+3)

//键盘消息执行
#define WM_KEYBOARD_MSG				(WM_USER+100)

#include "./rtspplayer/RtspClientLib.h"
#ifdef _DEBUG 
	#pragma comment(lib,".\\rtspplayerD\\RtspPlayerlib.lib")
#else 
	#pragma comment(lib,".\\rtspplayer\\RtspPlayerlib.lib")
#endif

//日志
#include "log4cplus\logger.h"
#include "log4cplus\fileappender.h"
#include "log4cplus\layout.h"
using namespace log4cplus;
#ifdef _DEBUG
	#pragma comment(lib,".\\rtspplayerD\\lib\\log4cplusSD.lib")
#else 
	#pragma comment(lib,".\\rtspplayer\\lib\\log4cplusS.lib")
#endif


#pragma comment(lib, "libcef.lib")

#ifdef _DEBUG
	#pragma comment(lib,".\\rtspplayerD\\libcef_dll_wrapper.lib")
#else 
	#pragma comment(lib,".\\rtspplayer\\libcef_dll_wrapper.lib")
#endif

using namespace std;
#pragma comment( lib, "ws2_32.lib" )

#include "WndsManger.h"
#include "Log.h"
string GetExePath();






#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


