/****************************************************** 
		文件名:		ourRTSPClient.h : 头文件

		编辑工具:	Microsoft Visual Studio 2010

		作者:		UESTC-PRMI

		创建时间:	2014-10-18

		修改者:		
		
		修改时间:

		主要内容:	1.	ourRTSPClient类完成对RTSPClient
						类的继承,实现RTSP客户端

					2.	MyUsageEnvironment类完成对
						BasicUsageEnvironment的继承,重载
 						输出函数,使log能够输出到文本文档
						中
******************************************************/ 

#pragma once
#include "stdafx.h"
#include "liveMedia.hh"
#include "BasicUsageEnvironment.hh"
#include "GroupsockHelper.hh"

#pragma comment (lib, "Ws2_32.lib")  
#pragma comment (lib, "BasicUsageEnvironment.lib")
#pragma comment (lib, "groupsock.lib")
#pragma comment (lib, "liveMedia.lib")
#pragma comment (lib, "UsageEnvironment.lib")

// ourRTSPClient的成员类
class StreamClientState
{
public:
  StreamClientState();
  virtual ~StreamClientState();

public:
  MediaSubsessionIterator* iter;
  MediaSession* session;
  MediaSubsession* subsession;
  TaskToken streamTimerTask;
  double duration;
};

// 
class ourRTSPClient: public RTSPClient 
{
public:
  static ourRTSPClient* createNew(UsageEnvironment& env, char const* rtspURL,
				  int verbosityLevel = 0,
				  char const* applicationName = NULL,
				  portNumBits tunnelOverHTTPPortNum = 0);
  virtual ~ourRTSPClient();

protected:
  ourRTSPClient(UsageEnvironment& env, char const* rtspURL,
		int verbosityLevel, char const* applicationName, portNumBits tunnelOverHTTPPortNum);
    // called only by createNew();
  

public:
	StreamClientState scs;
};

// 对BasicUsageEnvironment类的继承，主要完成操作符的重载

// 如果不需要保存输出LOG的话，注释下面几行：
//#define SAVE_LOG_TO_CSTRING (1)
//#define MAX_LOG_LEN (1024 * 10)
//static CString DisInfo = "\0";

//static CString *Log = &DisInfo;
//char* Log = new char[MAX_LOG_LEN];

class MyUsageEnvironment: public BasicUsageEnvironment {
public:
  static MyUsageEnvironment* createNew(TaskScheduler& taskScheduler);

  // redefined virtual functions:
  virtual int getErrno() const;

  virtual UsageEnvironment& operator<<(char const* str);
  virtual UsageEnvironment& operator<<(int i);
  virtual UsageEnvironment& operator<<(unsigned u);
  virtual UsageEnvironment& operator<<(double d);
  virtual UsageEnvironment& operator<<(void* p);


//protected:
  MyUsageEnvironment(TaskScheduler& taskScheduler);
      // called only by "createNew()" (or subclass constructors)
  virtual ~MyUsageEnvironment();
private:
	FILE* fp;
	bool isOpenfp();
};