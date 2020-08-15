#include "stdafx.h"
#include "BroadcastRecver.h"
#include "./common/initsock.h"
#include "stdio.h"
#include <windows.h>
#include <process.h>

CInitSock theSock1;
SOCKET s = 0;

CBroadcastRecver* CBroadcastRecver::s_pBcRecv = NULL;

CBroadcastRecver& CBroadcastRecver::getInstance()
{
	if (s_pBcRecv == NULL)
		s_pBcRecv = new CBroadcastRecver();
	return *s_pBcRecv;
}


void RecvBCThread(void* pParam)
{
	CBroadcastRecver* pThis = (CBroadcastRecver*)pParam;

	s = ::socket(AF_INET, SOCK_DGRAM, 0);

	// 首先要绑定一个本地地址，指明广播端口号
	SOCKADDR_IN sin;
	sin.sin_family = AF_INET;
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	sin.sin_port = ::ntohs(4567);
	if (::bind(s, (sockaddr*)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		printf(" bind() failed \n");
		return;
	}

	// 接收广播
	printf(" 开始接收广播数据... \n\n");
	SOCKADDR_IN addrRemote;
	int nLen = sizeof(addrRemote);
	int nTep = 100;
	char sz[256];
	while (!pThis->m_bExitThread)
	{
		int nRet = ::recvfrom(s, sz, 256, 0, (sockaddr*)&addrRemote, &nLen);
		if (nRet > 0)
		{
			sz[nRet] = '\0';
			printf(sz);
			if (pThis->m_cbBroadcastEvent != NULL)
			{
				pThis->m_cbBroadcastEvent(0);
			}

			//send back
			char szBack[100];
			memset(szBack, 0, 100);
			int nLen1 = 8;
			int nStatus = pThis->m_nStatus;
			
			int nMatchineType = pThis->m_nMacType;
			memcpy(szBack, &nLen1, 4);
			memcpy(szBack + 4, &nStatus, 4);
			memcpy(szBack + 8, &nMatchineType, 4);

			::sendto(s, szBack, 12, 0, (sockaddr*)&addrRemote, sizeof(addrRemote));
		}
	}
}

CBroadcastRecver::CBroadcastRecver()
: m_bExitThread(false)
, m_nStatus(0)
, m_nMacType(0)
{
}


CBroadcastRecver::~CBroadcastRecver()
{
}

int CBroadcastRecver::startBroadcastRecv(OnBroadcastEvent cbEvent)
{
	m_cbBroadcastEvent = cbEvent;
	_beginthread(RecvBCThread, 0, this);
	return 0;
}

void CBroadcastRecver::setMatchineInfo(int nStatus, int nType)
{
	m_nStatus = nStatus; 
	m_nMacType = nType; 
	printf(" set machine status:%d \n", m_nStatus);
}

int CBroadcastRecver::stopBroadcastRecv()
{
	m_bExitThread = true;
	closesocket(s);
	s = 0;
	return 0;
}