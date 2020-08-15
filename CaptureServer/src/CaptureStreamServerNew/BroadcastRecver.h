#pragma once

typedef void(*OnBroadcastEvent)(int nEventType);//0:查询机器占用状态 1:查询机器运行状态

class CBroadcastRecver
{
public:

	static CBroadcastRecver& getInstance();
	
	~CBroadcastRecver();

	int startBroadcastRecv(OnBroadcastEvent cbEvent);
	void setMatchineInfo(int nStatus, int nType = 0);//nStatus:0空闲 1占用
	int stopBroadcastRecv();

	OnBroadcastEvent m_cbBroadcastEvent;
	bool m_bExitThread;
	int  m_nStatus;
	int  m_nMacType;

protected:
	static CBroadcastRecver* s_pBcRecv;
	CBroadcastRecver();

};

