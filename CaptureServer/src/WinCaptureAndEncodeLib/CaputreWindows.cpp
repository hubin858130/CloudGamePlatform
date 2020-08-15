// TestCaputreWindows.cpp : 定义控制台应用程序的入口点。
//

#include <stdlib.h>
#include <stdio.h>
#include "screencapture/ScreenCapture.h"
#include "Timer.h"
#include "../NEncoderLib/NEncoderLib.h"
#include <process.h>
#include "MutexImp_Win32.h"
#include "WincaptureLib.h"

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")
#ifdef _DEBUG
	#pragma comment(lib,"../../lib/Debug/NEncoderLib.lib")
#else
	#pragma comment(lib,"../../lib/Release/NEncoderLib.lib")
#endif

static void frame_callback(sc::PixelBuffer& buf);
static void mouseRgbaCb(uint8_t* szBuf, int nSize);

CS::CCritSecImp     g_mutexFrame;
char*			  g_szFrameBuf = NULL;
int				  g_nBufferSize = 0;
int				  g_nWidth = 1280;
int				  g_nHeight = 720;
int				  g_nBps = 8000 * 1024;
int				  g_nFps = 30;

bool bExitCapture = false;
OnH264CallBack  g_cbH264 = NULL;
OnMouseCallBack g_cvMouse = NULL;
void caputureThread(void* p);
bool g_bShowCursor = false;


void MediaStatusCB(int nStatus, void * pUserData)
{
	printf(" Recv cb:%d\n", nStatus);
	if (nStatus == 2)
	{
	}
}

void EncodeStatusCallback(int nStatus)
{
	;
}

void EncodeFrameThread(void* pParam)
{
	//int n = 0;
	//while (TRUE)
	//{
	//	g_mutexFrame.Lock();
	//	PutFrameBuffer((char*)g_szFrameBuf, g_nBufferSize);

	//	if (n++ % 33 == 0)
	//	{
	//		SYSTEMTIME time;
	//		GetLocalTime(&time);
	//		char sz[150];
	//		sprintf_s(sz, (".\\pic\\1280_720_%02d_%02d_%02d_%03d.rgb"), time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
	//		FILE* pFile = NULL;
	//		fopen_s(&pFile, sz, "wb");
	//		fwrite(g_szFrameBuf, g_nBufferSize, 1, pFile);
	//		fclose(pFile);
	//	}

	//	g_mutexFrame.Unlock();
	//	
	//	Sleep(30);
	//}
}

void H264Callback(char* szBuffer, int nSize, int nWidth, int nHeight, int nFrameType, void * pUserData)
{
	//static FILE* pFile = NULL;
	//if (pFile == NULL)
	//{
	//	fopen_s(&pFile, "test.h264", "ab+");
	//}
	//fwrite(szBuffer, nSize, 1, pFile);
	unsigned char szTag = szBuffer[4];
	if (szTag == 0x67)//spspps+i frame
	{
		char szSPSPPS[34];
		memcpy(szSPSPPS, szBuffer, 34);
		nFrameType = 100;
		if (g_cbH264 != NULL)
		{
			g_cbH264(szSPSPPS, 34, g_nWidth, g_nHeight, nFrameType, pUserData);

			nFrameType = 0x03;
			g_cbH264(szBuffer + 34, nSize-34, g_nWidth, g_nHeight, nFrameType, pUserData);
		}
	}
	else if (szTag == 0x65)//i frame
	{
		if (g_cbH264 != NULL)
		{
			nFrameType = 0x03;
			g_cbH264(szBuffer , nSize, g_nWidth, g_nHeight, nFrameType, pUserData);
		}
	}
	else//p frmae
	{
		if (g_cbH264 != NULL)
		{
			nFrameType = 0x02;
			g_cbH264(szBuffer, nSize, g_nWidth, g_nHeight, nFrameType, pUserData);
		}
	}
}



FILE* pFIle = NULL;

int CaptureMain() 
{
	fopen_s(&pFIle, "./log/enc.log", "a+");
	int nWidth = g_nWidth;
	int nHeight = g_nHeight;
	InitEncoder(nWidth, nHeight,g_nBps,EncodeStatusCallback, H264Callback, NULL);
	if (g_szFrameBuf == NULL)
	{
		g_szFrameBuf = new char[nWidth*nHeight * 4];
	}

	OutputDebugString("Capture starting...");
	printf("Capture starting...");
	sc::ScreenCapture capture(frame_callback, mouseRgbaCb);
	std::vector<sc::Display*> displays;
	sc::Settings settings;

	if (0 != capture.init()) {
		exit(EXIT_FAILURE);
	}

	if (0 != capture.listDisplays()) {
		exit(EXIT_FAILURE);
	}

	if (0 != capture.getDisplays(displays)) {
		exit(EXIT_FAILURE);
	}

	if (0 != capture.listPixelFormats()) {
		exit(EXIT_FAILURE);
	}

	settings.pixel_format = SC_BGRA;
	settings.display = 0;
	settings.output_width = nWidth;
	settings.output_height = nHeight;

	if (0 != capture.configure(settings)) {
		exit(EXIT_FAILURE);
	}

	if (0 != capture.start()) {
		exit(EXIT_FAILURE);
	}
	//create getframe thread
//	_beginthread(EncodeFrameThread, 0, &capture);
	char sz[100];
	while (!bExitCapture) 
	{
		long lRet = capture.update(g_bShowCursor);
		if (lRet == S_OK)//grab a new frame
		{
			Sleep(2);
		}
		else if (lRet == 0x01)//no new frame
		{
			Sleep(1);
		}
		else// error
		{
			memset(sz, 0, 100);
			sprintf_s(sz, "update status : % 0x!\n", lRet);
			OutputDebugString(sz);
			printf(sz);
			//capture.shutdown();
			if (0 != capture.configure(settings)) {
				exit(EXIT_FAILURE);
			}
			else
			{
				OutputDebugString("configure success!\n");
				printf("configure success!\n");
			}
		}
//		printf("m:%d\n", g_bShowCursor);
	}

	capture.shutdown();
	releaseEncoder();
	OutputDebugString("Capture End...");
	printf("Capture End...");
	return 0;
}

long lLast = 0;
int n = 0;
int nSpaceTime = 0;
int nCount = 0;

Timer t;

static void frame_callback(sc::PixelBuffer& buf) //回调改主动获取
{
	int nBufferSize = buf.nbytes[0];

	if (n == 0)
	{
		t.reset();
		PutFrameBuffer((char*)buf.plane[0], buf.nbytes[0]);
		lLast = ::GetTickCount();
		printf("Capture suc and put encoder begin...\n");
	}


	if (nSpaceTime > 14)//14
	{
		t.reset();
		PutFrameBuffer((char*)buf.plane[0], nBufferSize);
		if (n % 500 == 0)
		{
			printf("Capture suc and put encoder...\n");
		}

		//if (lLast++ % 5 == 0)
		//{
		//	printf("time:%d,size:%d\n", nSpaceTime, nBufferSize);
		//	SYSTEMTIME time;
		//	GetLocalTime(&time);
		//	char sz[150];
		//	sprintf_s(sz, ("E:\\pic\\1280_720_%02d_%02d_%02d_%03d.rgb"), time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
		//	FILE* pFile = NULL;
		//	fopen_s(&pFile, sz, "wb");
		//	fwrite(buf.plane[0], buf.nbytes[0], 1, pFile);
		//	fclose(pFile);
		//}

		//SYSTEMTIME time;
		//GetLocalTime(&time);
		//char sz[50];
		//sprintf_s(sz, ("%02d:%02d:%02d:%03d"), time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
		//long nEncTime = t.now();
		//char szLog[100];
		//memset(szLog, 0, 100);
		//sprintf_s(szLog, "time:%s,enc time:%ld\n\t", sz,nEncTime);
		//if (pFIle)
		//{
		//	fwrite(szLog, 1,strlen(szLog), pFIle);
		//}

		//if (nCount % 2000 == 0 && nCount>0)
		//{
		//	long lCur = ::GetTickCount();
		//	int nFrameTime = (lCur - lLast) / nCount;
		//	int nFps = 1000 / nFrameTime;
		//	printf("time:%d ms,fps:%d\n", nFrameTime, nFps);
		//}
		//nCount++;

		
	}
	nSpaceTime = t.now();

	
//	Sleep(5);
	
	/*g_mutexFrame.Lock();
	memcpy(g_szFrameBuf, buf.plane[0], buf.nbytes[0]);
	g_nBufferSize = buf.nbytes[0];
	g_mutexFrame.Unlock();

	long l = t.now();
	if (n%5==0)
	{
		printf("copy time:%d.\n",  l);
	}
	nSpaceTime += l;
	return;*/
	n++;
}

static void mouseRgbaCb(uint8_t* szBuf, int nSize)
{
	if (g_cvMouse != NULL&&!g_bShowCursor)
	{
		g_cvMouse((char*)szBuf, nSize);
	}
}

void StartCapture(int nWidth, int nHeight, int nBps, int nFps)
{
	g_nWidth = nWidth;
	g_nHeight = nHeight;
	g_nBps = nBps;
	g_nFps = nFps;
	bExitCapture = false;
	_beginthread(caputureThread, 0, NULL);
}

void SetBufferCallback(OnH264CallBack cbH264Data, OnMouseCallBack cbMouseCallback)
{
	g_cbH264 = cbH264Data;
	g_cvMouse = cbMouseCallback;
}

void SetCursorStatus(bool bShow)
{
	g_bShowCursor = bShow;
	printf("$$$$$$$mouse status:%d\n", bShow);
}

void EndCapture()
{
	bExitCapture = true;
	Sleep(1000);
}

void caputureThread(void* p)
{
	CaptureMain();
	//	LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "Error:Capture thread run out.");
}