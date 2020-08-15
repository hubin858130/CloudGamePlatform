// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")


#include "MediaServerLib.h"
#ifdef _DEBUG
	#pragma comment(lib,"..\\..\\lib\\debug\\MediaServerLibD.lib")
#else 
	#pragma comment(lib,"..\\..\\lib\\release\\MediaServerLib.lib")
#endif


//日志
#include "log4cplus\logger.h"
#include "log4cplus\fileappender.h"
#include "log4cplus\layout.h"
using namespace log4cplus;
#ifdef _DEBUG
#pragma comment(lib,"..\\..\\lib\\log4app\\win32\\debug\\log4cplusSD.lib")
#else 
#pragma comment(lib,"..\\..\\lib\\log4app\\win32\\release\\log4cplusS.lib")
#endif

//capture
#include "WincaptureLib.h"
#ifdef _DEBUG
#pragma comment(lib,"..\\..\\lib\\debug\\WinCaptureAndEncodeLib.lib")
#else 
#pragma comment(lib,"..\\..\\lib\\release\\WinCaptureAndEncodeLib.lib")
#endif

//base64
#include "Base64CodecApi.h"
#ifdef _DEBUG
#pragma comment(lib,"..\\..\\lib\\base64\\debug\\Base64Codec.lib")
#else 
#pragma comment(lib,"..\\..\\lib\\base64\\release\\Base64Codec.lib")
#endif

//crptolib
//#ifdef _debug
//	#pragma comment(lib,"..\\..\\lib\\debug\\cryptolib.lib")
//#else 
//	#pragma comment(lib,"..\\..\\lib\\release\\cryptolib.lib")
//#endif

#include "Log.h"
#include "NetComdef.h"
string GetExePath();


