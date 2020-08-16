/****************************************************** 
		文件名:		StaticData.h 声明文件

		编辑工具:	Microsoft Visual Studio 2010

		作者:		UESTC-PRMI

		创建时间:	2014-10-18

		修改者:		
		
		修改时间:

		主要内容:	声明一些全局不变并常用的结构体,常
					量,枚举等
******************************************************/ 
#pragma once

/** 打印输出每一帧数据到log.pref，如果不需要，注释下面一行 */
//#define DEBUG_PRINT_EACH_RECEIVED_FRAME 1

/** 保存接收到的H264视频数据到Recieved.264，如果不需要，注释下面一行 */
//#define SAVE_THE_STREAM_INTO_FILE 1

// 自定义windows消息
#define	WM_SOCKET			(WM_USER + 30)
#define WM_PLAYER			(WM_USER + 31)
#define WM_CONTROL			(WM_USER + 32)
#define WM_RTSP				(WM_USER + 33)
#define WM_RECT				(WM_USER + 34)		// 发送给RTSP进程,参数为播放区域高宽	

const int WPARAM_RECT		= 0;	// RTSP进程接收到长宽
const int WPARAM_START		= 1;	// 启动
const int WPARAM_CLOSE		= 2;	// 关闭
const int WPARAM_STOP		= 3;	// 播放器停止播放 或 播放器退出 发出该参数,仅播放器发出

const int WPARAM_PLAYING	= 4;	// RtspPlayer发送来的消息,表示开始播放
const int WPARAM_PAUSE		= 5;	// 暂停参数

// 常量定义
const int BUFFER_SIZE		= 128;			// url地址最大长度
const int CONTROL_PORT		= 8088;			// 回传命令时的端口
const int UDP_PORT			= 8087;			// 局域网内Android手机通信端口
const int COMMAND_SIZE		= 1;			// 发送给远程手机指令(头)的大小
const int START_EVENT_LOOP	= 0;			// 0,env->taskScheduler().doEventLoop(&eventLoopWatchVariable)函数一直循环下去
const int STOP_EVENT_LOOP	= 1;			// 非零,env->taskScheduler().doEventLoop(&eventLoopWatchVariable)函数退出循环
const int START_CODE_SIZE	= 4;			// {0x00, 0x00, 0x00, 0x01}		4位起始码
const int HAVE_ACCESSED_POSITION = 1;		// 已经获得各个控件的初始位置
const int RTSP_CLIENT_VERBOSITY_LEVEL = 1;	// by default, print verbose output from each "RTSPClient"
const int NALU_BUFFER_SIZE	= 1024 * 1024;

const char PLAYER_NAME[]	= "Smart Player";
const char CONTROL_NAME[]	= "Smart Control";

const char LOGFILE[]		= _T(".\\DATA\\log.pref");
const char URLFILE[]		= _T(".\\DATA\\url.pref");
const char VIDEOFILE[]		= _T(".\\DATA\\Recieved.264");

const char FOLDERPATH[]		= _T(".\\DATA");
#ifdef DEBUG
const char SMARTCTRLPATH[]	= _T("..\\Debug\\SmartControl.exe");
#endif

#ifndef DEBUG
const char SMARTCTRLPATH[]	= _T("SmartControl.exe");
#endif


// 静态变量定义
static bool fHaveWrittenFirstFrame = false;		// 接收到第一帧时,需要对视频数据的SPS,PPS进行补偿.false,表示还未进行补偿;true,表示已经进行了补偿

typedef struct PacketQueue
{
    AVPacketList *first_pkt, *last_pkt;
    int nb_packets;
    int size;
    SDL_mutex *mutex;
    SDL_cond *cond;
} PacketQueue;
