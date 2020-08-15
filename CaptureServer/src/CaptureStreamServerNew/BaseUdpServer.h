#pragma once
class CBaseUdpServer
{
public:
	CBaseUdpServer();
	~CBaseUdpServer();
	int IoDomain(OnEventUserIOStatus pStatusCb);
	int CloseUdpServer();


	SOCKET		m_socUdp;
	bool		m_bRecvClient;
	sockaddr_in	m_addrUdp;
	long		m_lLastTime;
	char*		m_szGuestIp;
};

