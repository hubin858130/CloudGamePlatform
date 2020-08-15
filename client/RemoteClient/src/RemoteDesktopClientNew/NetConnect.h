#pragma once
typedef void(*OnRecvDataCallback)(char* szBuffer,int nSize);
class CNetConnect
{
public:
	CNetConnect();
	~CNetConnect();

	bool StartNet(CString strServIP, OnRecvDataCallback onDataRecv);
	int StopNet();
	int SendBuffer(CString strBuffer);

	int		m_nSocket;
	bool	m_bConnected;
	OnRecvDataCallback m_RecvCallback;
};

