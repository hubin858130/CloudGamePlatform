#include "stdafx.h"
#include "BaseUdpServer.h"
#include "./common/InitSock.h"
#include <stdio.h>
#include "MsgQueue.h"
#include <process.h>


CInitSock initSockUdp;		// 初始化Winsock库
OnEventUserIOStatus g_IoStatusCallbackudp = NULL;

void SendClientThreadudp(void* p)
{
	CBaseUdpServer* pThis = (CBaseUdpServer*)p;
	if (pThis == NULL)
	{
		return;
	}
	while (pThis->m_socUdp>0)
	{
		PMsgInfo pSendMsg = CMsgQueue::getInstance().getSendMsgFromQueue();
		if (pSendMsg != NULL)
		{
			if (pThis->m_bRecvClient)
			{
				::sendto(pThis->m_socUdp, pSendMsg->szBuffer, pSendMsg->nBodyLen, 0, (sockaddr*)&(pThis->m_addrUdp), sizeof(pThis->m_addrUdp));
				int nType = -1;
				memcpy(&nType, pSendMsg->szBuffer + 4, 4);
//				LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "send msg,type:" << nType);
			}
		}
		else
		{
			Sleep(3); 
			continue;
		}
		delete pSendMsg;
		pSendMsg = NULL;
	}

}

void NetEventDealThreadudp(void* pParam)
{
	CBaseUdpServer* pThis = (CBaseUdpServer*)pParam;
	if (pThis == NULL)
	{
		return;
	}
	while (pThis->m_socUdp>0)
	{
		string strMsg = CMsgQueue::getInstance().getRecvMsgFromQueue();
		if (!strMsg.empty())
		{
			int nNetType = DealMouseAndKeyboard(strMsg);//huqb
			if (nNetType == 100 || nNetType == 101 || nNetType==2002||nNetType == 2101)
			{
				if (g_IoStatusCallbackudp != NULL)
				{
					g_IoStatusCallbackudp(nNetType, NULL);
				}
				if (nNetType == 2002)
				{
					CMsgQueue::getInstance().pushSendMsgToQueue("reconnect", 9, 2003);
					LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "[huqb]post reconnect mediaserver cmd.");
				}
			}
			if (nNetType == 8)
			{//心跳 回复
				CMsgQueue::getInstance().pushSendMsgToQueue("good", 4, 0);
			}
			pThis->m_lLastTime = ::GetTickCount();//所有消息都作为心跳记录
		}
		else
		{
			Sleep(3);
		}
	}
}

void NetHeartBeatThreadudp(void* pParam)
{
	CBaseUdpServer* pThis = (CBaseUdpServer*)pParam;
	if (pThis == NULL)
	{
		return;
	}
	while (pThis->m_socUdp>0)
	{
		Sleep(500);
		long lCurTime = ::GetTickCount();
		//2s超时清理
		if (pThis->m_bRecvClient)
		{ 
			long lTimeSpace = lCurTime - pThis->m_lLastTime;
			if (lTimeSpace > 10000)//10s心跳断开
			{
				if (g_IoStatusCallbackudp != NULL)
				{
					g_IoStatusCallbackudp(1, NULL);
				}
				LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "Client:" << pThis->m_szGuestIp << " heartbeat outime:" << lTimeSpace << "ms,disconnected.");
	//			break;
				pThis->m_bRecvClient = false;
			}
		}
		
	}
}

CBaseUdpServer::CBaseUdpServer()
	: m_socUdp(0)
	, m_bRecvClient(false)
	, m_szGuestIp(NULL)
{
}


CBaseUdpServer::~CBaseUdpServer()
{
}

int CBaseUdpServer::IoDomain(OnEventUserIOStatus pStatusCb)
{
	g_IoStatusCallbackudp = pStatusCb;
	// 创建套节字
	m_socUdp = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (m_socUdp == INVALID_SOCKET)
	{
		printf("Failed socket() \n");
		return 0;
	}

	// 填充sockaddr_in结构
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(4567);
	sin.sin_addr.S_un.S_addr = INADDR_ANY;

	// 绑定这个套节字到一个本地地址
	if (::bind(m_socUdp, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		printf("Failed bind() \n");
		return 0;
	}

	//启动发送线程
	_beginthread(SendClientThreadudp, 0, this);
	//启动业务接收处理线程
	_beginthread(NetEventDealThreadudp, 0, this);
	//心跳检测
	_beginthread(NetHeartBeatThreadudp, 0, this);

	// 接收数据
	char bufheader[4];
	char buff[4096];
	//sockaddr_in addr;
	int nLen = sizeof(m_addrUdp);
	int nCount = 0;
	while (m_socUdp>0)
	{
		memset(buff, 0, 4096);
		int nRecv = ::recvfrom(m_socUdp, buff, 4096, 0, (sockaddr*)&m_addrUdp, &nLen);
		if (nRecv > 4&&nRecv < 4095)
		{
			if (!m_bRecvClient)
			{
				if (g_IoStatusCallbackudp != NULL)
				{
					g_IoStatusCallbackudp(0, NULL);
				}
			}
			m_bRecvClient = true;
			int nBodyLen = (int)buff[3];
			string strContent = buff+4;
			m_szGuestIp = ::inet_ntoa(m_addrUdp.sin_addr);
			//huqb test
//			printf(" 接收到数据（%s）,size:%d,count:%d\n", ::inet_ntoa(m_addrUdp.sin_addr), buff+4, nRecv, ++nCount);

			CMsgQueue::getInstance().pushRecvMsgToQueue(strContent);
		}
		else
		{
			printf(" @@@@ recvfrom failed.\n");
		}
	}
	

	return 0;
}

int CBaseUdpServer::CloseUdpServer()
{
	if (m_socUdp>0)
	{
		::closesocket(m_socUdp);
		m_socUdp = 0;
	}
	
	return 0;
}