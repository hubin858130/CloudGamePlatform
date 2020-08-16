// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  从 Windows 头文件中排除极少使用的信息
// Windows 头文件:
#include <windows.h>

// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: 在此处引用程序需要的其他头文件

#ifdef __cplusplus

#include <stdio.h>
#include <tchar.h>
#include <string.h>

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"

#include "sdl/sdl.h"
#include "sdl/sdl_thread.h"
}
#endif
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "avutil.lib")
#pragma comment(lib, "swresample.lib")
#pragma comment(lib, "swscale.lib")
#pragma comment(lib, "sdl.lib")

//日志
#include "log4cplus\logger.h"
#include "log4cplus\fileappender.h"
#include "log4cplus\layout.h"
using namespace log4cplus;
#pragma comment(lib,"log4cplusSD.lib")

#include "RtspClientLib.h"

#include "Log.h"
string GetExePath();
