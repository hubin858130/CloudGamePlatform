#pragma once
#include <string>
using std::string;

class CHttpUtils
{
public:
	CHttpUtils();
	~CHttpUtils();

	int	PostHttp(string strUrl, string strContent, string& strResult, int nBodyLen,int nType=0);//nType 0 post 1 put
//	int PostHttp(string strUrl, char* szContent, int nContent, string& strResult);
	int VerificationLicense(string strUrl, char* szContent, int nContentLen, string&strResult);

protected:
	bool Ev_ConnectRecordServer(string strIp, int nPort);
	bool Ev_Close();
	bool Ev_SendData(int nAlarmSize, string strContent, string &strResult);
	bool SendData(int nAlarmSize, char* strContent, string &strResult);

private:
	int		m_nSockClient;
	bool	m_bConnectServer;
	char*	m_pPacket;
};

