#include "stdafx.h"
#include "NetConnect.h"
//#include "EV_Socket.h"
#include <process.h>
#include <string>
#include "./common/initsock.h"
#include <WS2tcpip.h>
#include <stdio.h>
CInitSock initSock;		// 初始化Winsock库

using std::string;

bool g_bExit = false;

sockaddr_in g_addr;


void OnRecvThread(void* pParam)
{
	CNetConnect* pThis = (CNetConnect*)pParam;
	string strRecvBuf = "";
	char chRecvBuf[4096];
	int nLen = sizeof(g_addr);
	while (!g_bExit)
	{
		int nRecvSize = 0;
		memset(chRecvBuf, 0, sizeof(chRecvBuf));

		int nRecv = ::recvfrom(pThis->m_nSocket, chRecvBuf, 4096, 0, (sockaddr*)&g_addr, &nLen);
		if (nRecv > 0)
		{
			if (pThis->m_RecvCallback != NULL)
			{
				pThis->m_RecvCallback(chRecvBuf, nRecvSize);
			}
		}
		else
		{
			//pThis->m_bConnected = false;
			//break;
			LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "recv failed:"<<nRecv);
			Sleep(1000);
		}
	}
}

CNetConnect::CNetConnect()
: m_nSocket(-1)
, m_bConnected(false)
, m_RecvCallback(NULL)
{
}


CNetConnect::~CNetConnect()
{
}

bool CNetConnect::StartNet(CString strServIP, OnRecvDataCallback onDataRecv)
{
	m_RecvCallback = onDataRecv;
	m_bConnected = false;

	m_nSocket = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (m_nSocket == INVALID_SOCKET)
	{
		printf("Failed socket() %d \n", ::WSAGetLastError());
		return m_bConnected;
	}

	// 也可以在这里调用bind函数绑定一个本地地址
	// 否则系统将会自动安排

	// 填写远程地址信息
//	sockaddr_in addr;
	g_addr.sin_family = AF_INET;
	inet_pton(AF_INET, strServIP.GetBuffer(0), (void*)&g_addr.sin_addr);
	g_addr.sin_port = htons(4567);

	_beginthread(OnRecvThread, 0, this);

	m_bConnected = true;

	return m_bConnected;
}

int CNetConnect::StopNet()
{
	int nRet = 0;
	g_bExit = true;
	Sleep(200);

	::closesocket(m_nSocket);
	m_nSocket = -1;
	m_bConnected = false;

	return nRet;
}

int CNetConnect::SendBuffer(CString strBuffer)
{ 
	//protal: len + body
	int nRet = -1;
	if (m_bConnected)
	{
		int nBodyLen = strBuffer.GetLength();
		char* szContent = new char[nBodyLen + 4];
		for (int i = 0; i < 4; i++) {
			szContent[i] = (byte)(nBodyLen >> (24 - i * 8));
		}
		memcpy(szContent + 4, strBuffer.GetBuffer(0), nBodyLen);

		nRet = ::sendto(m_nSocket, szContent, nBodyLen + 4, 0, (sockaddr*)&g_addr, sizeof(g_addr));//EV_Send(m_nSocket, szContent, nBodyLen+4);

		delete[] szContent;
		szContent = NULL;
	}
	return nRet;
}