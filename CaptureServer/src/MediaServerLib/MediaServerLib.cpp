// MediaServerLib.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "MediaServerLib.h"
#include "comdef.h"
#include <process.h>
#include "RtspServer.h"
#include "H264Source.h"
#include "AACSource.h"
#include "xop.h"
#include <thread>
#include <memory>
#include <iostream>
#include <string>
#include <queue>
#include "MutexImp_Win32.h"

#if defined(WIN32) || defined(_WIN32) 
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib,"Iphlpapi.lib")
#endif 

using namespace std;
using namespace xop;
using namespace CS;
using std::queue;
long  audio_pts = 0;

queue<SMediaBufferInfo>    g_MediaBufferQueue;
CMutexImp				   g_MutexMediaBuffer;
OnUserStatusCallBack	   userCb = NULL;

UINT32    g_uLastTime = 0;

void sendFrame(RtspServer* rtspServer, MediaSessionId sessionId, int& clients)
{
	while (1)
	{
		if (clients > 0) // MediaSession有客户端在线, 发送音视频数据
		{
			//获取一帧 H264, 打包
			xop::AVFrame videoFrame = { 0 };

			if (g_MediaBufferQueue.size() > 0)
			{
				g_MutexMediaBuffer.Lock();

				SMediaBufferInfo sMedia = g_MediaBufferQueue.front();
				g_MediaBufferQueue.pop();

				g_MutexMediaBuffer.Unlock();

				videoFrame.size = sMedia.nBufferSize;  // 
				videoFrame.buffer.reset(new char[videoFrame.size + 1000]);
				memcpy(videoFrame.buffer.get(), sMedia.szBuffer, videoFrame.size);

				if (sMedia.nMediatype == 0)
				{
					//SYSTEMTIME time;
					//GetLocalTime(&time);
					//time.wMilliseconds + time.wSecond * 1000 + time.wMinute * 60000;
					videoFrame.timestamp = sMedia.lTimeS;//H264Source::getTimeStamp(); //
					bool b = rtspServer->pushFrame(sessionId, channel_0, videoFrame);
					//printf("send size:%d,result:%d,queue size:%d\n", videoFrame.size,b, g_MediaBufferQueue.size());
				}
				if (sMedia.nMediatype == 1)
				{
					videoFrame.timestamp = audio_pts;
					//audio_pts += 48 * 22.32;//(audio_pts++)*(4096*1000/48000);
					//printf("send size:%d,queue size:%d\n"videoFrame, videoFrame.size, g_MediaBufferQueue.size());
					audio_pts += 1024;

					rtspServer->pushFrame(sessionId, channel_1, videoFrame);
					
				}
				delete[]sMedia.szBuffer;
				sMedia.szBuffer = NULL;
			}
			else
			{
				Sleep(10);
			}
		}
		else
		{
			Timer::sleep(100);
		}
	}
}

void RunMediaServerThread(void* pParam)
{
	XOP_Init();
	userCb = (OnUserStatusCallBack)pParam;
	// 记录当前客户端数量
	int clients = 0;
	std::string ip = "0.0.0.0";//NetInterface::getLocalIPAddress();
	std::shared_ptr<EventLoop> eventLoop(new EventLoop());
	RtspServer server(eventLoop.get(), ip, 554);

	MediaSession *session = MediaSession::createNew("live"); // rtsp://ip/live
															 // 同时传输音视频, track0:h264, track1:aac
	session->addMediaSource(xop::channel_0, H264Source::createNew());
	session->addMediaSource(xop::channel_1, AACSource::createNew(44100, 2));

	//  开启组播(ip,端口随机生成), 默认使用 RTP_OVER_UDP, RTP_OVER_RTSP
	// session->startMulticast();

	// 设置通知回调函数。 在当前会话, 客户端连接或断开会发起通知
	session->setNotifyCallback([&clients](MediaSessionId sessionId, uint32_t numClients)
	{
		clients = numClients; //获取当前MediaSession客户端数量
		cout << "MediaSession" << "(" << sessionId << ") "
			<< "clients: " << clients << endl;
		if (userCb!=NULL)
		{
			userCb(clients, 1);
		}
	});

	cout << "rtsp://" << ip << "/" << session->getRtspUrlSuffix() << endl;

	// 添加session到RtspServer后, session会失效
	MediaSessionId sessionId = server.addMeidaSession(session); // 接口线程安全

	thread t(sendFrame, &server, sessionId, ref(clients));// 音视频数据转发线程
	t.detach();

	// 运行 RtspServer 
	eventLoop->loop();
}
//start  server
int StartMediaServer(OnUserStatusCallBack onUsercb)
{
	_beginthread(RunMediaServerThread, 0, (void*)onUsercb);
	return 0;
}
//stop   server
int StopMediaServer()
{
//	eventLoop->quit();
	return 0;
}
//send   video buffer
int SendVideoBuffer(char* szBuffer, int nSize,long lTimeS)
{
	SMediaBufferInfo  sInfo;
	if (g_MediaBufferQueue.size() > 50)
	{
		return 1;
	}
	sInfo.szBuffer = new char[nSize];
	memcpy(sInfo.szBuffer, szBuffer, nSize);
	sInfo.nBufferSize = nSize;
	sInfo.nMediatype = 0;
	sInfo.lTimeS = lTimeS;
	g_MutexMediaBuffer.Lock();
	g_MediaBufferQueue.push(sInfo);
	g_MutexMediaBuffer.Unlock();
	return 0;
}
//send   audio buffer
int SendAudioBuffer(char* szBuffer, int nSize)
{
	SMediaBufferInfo  sInfo;
	if (g_MediaBufferQueue.size() > 50)
	{
		return 1;
	}
	sInfo.szBuffer = new char[nSize];
	memcpy(sInfo.szBuffer, szBuffer, nSize);
	sInfo.nBufferSize = nSize;
	sInfo.nMediatype = 1;
	g_MutexMediaBuffer.Lock();
	g_MediaBufferQueue.push(sInfo);
	g_MutexMediaBuffer.Unlock();
	return 0;
}

