#include "stdafx.h"
#include "MsgQueue.h"

CMsgQueue* CMsgQueue::s_pMsgQue = NULL;

CMsgQueue& CMsgQueue::getInstance()
{
	if (s_pMsgQue == NULL)
		s_pMsgQue = new CMsgQueue();
	return *s_pMsgQue;
}

CMsgQueue::CMsgQueue()
{
}

CMsgQueue::~CMsgQueue()
{
}

void CMsgQueue::pushRecvMsgToQueue(string strMsg)
{
	m_muteRecv.Lock();
	m_queRecv.push(strMsg);
	m_muteRecv.Unlock();
}

string CMsgQueue::getRecvMsgFromQueue()
{
	string strMsg = "";
	if (m_queRecv.size() > 0)
	{
		m_muteRecv.Lock();
		strMsg = m_queRecv.front();
		m_queRecv.pop();
		m_muteRecv.Unlock();
	}
	return strMsg;
}

void CMsgQueue::pushSendMsgToQueue(string strMsg)
{
	if (strMsg.length() >= 8188)
		return;
	PMsgInfo pMsg = new MsgInfo();
	pMsg->nMsgType = 0;
	pMsg->nBodyLen = strMsg.length() + 4;
	memcpy(pMsg->szBuffer, &(pMsg->nBodyLen), 4);
	pMsg->nBodyLen += 4;
	memcpy(pMsg->szBuffer + 4, &(pMsg->nMsgType), 4);
	memcpy(pMsg->szBuffer + 8, strMsg.c_str(), strMsg.length());

	m_muteSend.Lock();
	m_queSend.push(pMsg);
	m_muteSend.Unlock();
}

void CMsgQueue::pushSendMsgToQueue(char* szBody, int nBodyLen, int nMsgType)
{
	if (nBodyLen >= 8188)
		return;
	PMsgInfo pMsg = new MsgInfo();
	pMsg->nMsgType = nMsgType;
	pMsg->nBodyLen = nBodyLen + 4;
	memcpy(pMsg->szBuffer, &(pMsg->nBodyLen), 4);
	pMsg->nBodyLen += 4;
	memcpy(pMsg->szBuffer + 4, &(pMsg->nMsgType), 4);
	memcpy(pMsg->szBuffer + 8, szBody, nBodyLen);
	
	m_muteSend.Lock();
	m_queSend.push(pMsg);
	m_muteSend.Unlock();
}

PMsgInfo CMsgQueue::getSendMsgFromQueue()
{
	PMsgInfo pMsg = NULL;
	if (m_queSend.size() > 0)
	{
		m_muteSend.Lock();
		pMsg = m_queSend.front();
		m_queSend.pop();
		m_muteSend.Unlock();
	}
	return pMsg;
}