#pragma once
#include "MutexImp_Win32.h"
#include <queue>
using std::queue;
using namespace CS;

#define _MAX_BUFFERLEN 8192
typedef struct _MsgInfo
{
	int   nBodyLen;
	int   nMsgType;
	char  szBuffer[_MAX_BUFFERLEN];
	_MsgInfo()
	{
		nBodyLen = 0;
		nMsgType = 0;
	}
} MsgInfo,*PMsgInfo;

//send protol :   4 + 4 + bodybufferLen (数据长度 + 信息类型 + 数据)

class CMsgQueue
{
public:
	static CMsgQueue& getInstance();

	void pushRecvMsgToQueue(string strMsg);
	string getRecvMsgFromQueue();
	void pushSendMsgToQueue(string strMsg);
	void pushSendMsgToQueue(char* szBody,int nBodyLen,int nMsgType);//type:0 心跳信息 json串 1 鼠标图片信息
	PMsgInfo getSendMsgFromQueue();

protected:
	CMsgQueue();
	~CMsgQueue();

private:
	static CMsgQueue* s_pMsgQue;

	CMutexImp		  m_muteRecv;
	CMutexImp		  m_muteSend;

	queue<string>		m_queRecv;
	queue<PMsgInfo>     m_queSend;
};

