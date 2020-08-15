#include "stdafx.h"
#include "HttpUtils.h"
#include "EV_Socket.h"
#include "Log.h"

CHttpUtils::CHttpUtils()
{
	m_pPacket = new char[2 * 1024 * 1024];
}


CHttpUtils::~CHttpUtils()
{
	if (m_pPacket != NULL)
	{
		delete[] m_pPacket;
		m_pPacket = NULL;
	}
}

bool CHttpUtils::Ev_ConnectRecordServer(string strIp, int nPort)
{
	m_nSockClient = CDayeBasicSocket::socket();

	CDayeBasicSocket::setNonBlocking(m_nSockClient);

	m_bConnectServer = CDayeBasicSocket::connect(m_nSockClient, strIp, nPort);

	if (!m_bConnectServer)
	{
		CDayeBasicSocket::close(m_nSockClient);
		m_nSockClient = -1;
	}

	return m_bConnectServer;
}

bool CHttpUtils::Ev_Close()
{
	CDayeBasicSocket::close(m_nSockClient);
	m_nSockClient = -1;

	m_bConnectServer = false;

	return true;
}

bool CHttpUtils::SendData(int nAlarmSize, char* strContent, string &strResult)
{
	int nPos = 0;
	//	printf("nbWrite begin!\n");
	bool bSend = CDayeBasicSocket::nbWrite(m_nSockClient, (char*)strContent, nAlarmSize, &nPos);
	if (!bSend)
	{
		return false;
	}
	//	printf("nbWrite end!\n");
	//接收响应
	bool eof = false;
	int nError = 0;

	//	printf("nbRead begin!\n");
	bool bRecv = CDayeBasicSocket::nbRead(m_nSockClient, strResult, &eof, nError, 3);
	//	printf("nbRead end!\n");
	//		bRecv = CDayeBasicSocket::nbRead( m_nSockClient,strResult, &eof, nError, 2 );
	//解析反馈
	return true;
}

bool CHttpUtils::Ev_SendData(int nAlarmSize, string strContent, string &strResult)
{
	if (!m_bConnectServer || nAlarmSize <= 0)
	{
		return false;
	}
	//发送报警
	int nPos = 0;
//	printf("nbWrite begin!\n");
	bool bSend = CDayeBasicSocket::nbWrite(m_nSockClient, (char*)strContent.c_str(), nAlarmSize, &nPos);
	if (!bSend)
	{
		return false;
	}
//	printf("nbWrite end!\n");
	//接收响应
	bool eof = false;
	int nError = 0;

//	printf("nbRead begin!\n");
	bool bRecv = CDayeBasicSocket::nbRead(m_nSockClient, strResult, &eof, nError, 3);
//	printf("nbRead end!\n");
	//		bRecv = CDayeBasicSocket::nbRead( m_nSockClient,strResult, &eof, nError, 2 );
	//解析反馈
	return true;
}

int	CHttpUtils::PostHttp(string strUrl, string strContent, string& strResult, int nBodyLen, int nType)
{
	int nResult = -1;
	string strIp = "";
	int nPort = 0;
	string strAddr = "";
	if (!strUrl.empty())
	{
		string str = strUrl;
		int nLen = str.length();
		int nPos = str.find("//");
		string str1 = str.substr(0, nPos);
		string str2 = str.substr(nPos + 2, nLen);

		nPos = str2.find("/");
		str1 = str2.substr(0, nPos);
		strAddr = str2.substr(nPos, str2.length());
		nPos = str1.find(":");

		strIp = str1.substr(0, nPos);
		nPort = atoi(str1.substr(nPos + 1, nLen).c_str());

		bool bSucc = Ev_ConnectRecordServer(strIp, nPort);
		if (!bSucc)
		{
			char szLog[50];
			sprintf_s(szLog, "connect %s:%d failed!", strIp, nPort);
			//				OutPutDebugLog(szLog) ;
			LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "Ev_ConnectRecordServer:" << szLog);
			return nResult;
		}

		memset(m_pPacket, 0, 2 * 1024 * 1024);
		//test:
		// 			char* szTest = new char[1024*1024] ;
		// 			memset(szTest,64,1024*1024) ;
		// 			szTest[1024*1024-2] = 'Z' ;
		// 			szTest[1024*1024-1] = 'Z' ;
		char* szType = "POST";
		if (nType==1)
			szType = "PUT";

		sprintf(m_pPacket, "%s %s HTTP/1.1\r\nAccept: */*\r\nHOST: %s:%d\r\nContent-Length: %d \r\nContent-Type:application/json;charset=UTF-8\r\n\r\n%s",
			szType, strAddr.c_str(), strIp.c_str(), nPort,/*1024*1024,szTest*/nBodyLen , strContent.c_str());
		string strPacket = m_pPacket;	
//		LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "Send begin!");
		clock_t t1 = clock();
		int nLen1 = strPacket.length();
		bSucc = Ev_SendData(nLen1, strPacket, strResult);
		if (!bSucc)
		{
			// 				OutPutDebugLog("Post Failed:\n") ;
			// 				OutPutDebugLog(m_pPacket) ;
			LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "Post Failed:" << m_pPacket);
		}
		else
		{
//			LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "Post succ:" << (char*)strResult.c_str());
			if (strResult.find("200")>0)
			{
				nResult = 0;
			}
		}
		Ev_Close();
		clock_t t2 = clock();
//		LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "Recv End! used time:" << t2 - t1 << "ms");
	}

	return nResult;
}

int CHttpUtils::VerificationLicense(string strUrl, char* szContent, int nContent, string& strResult)
{
	int nResult = -1;
	string strIp = "";
	int nPort = 0;
	string strAddr = "";
	if (!strUrl.empty())
	{
		string str = strUrl;
		int nLen = str.length();
		int nPos = str.find("//");
		string str1 = str.substr(0, nPos);
		string str2 = str.substr(nPos + 2, nLen);

		nPos = str2.find("/");
		str1 = str2.substr(0, nPos);
		strAddr = str2.substr(nPos, str2.length());
		nPos = str1.find(":");

		strIp = str1.substr(0, nPos);
		nPort = atoi(str1.substr(nPos + 1, nLen).c_str());

		bool bSucc = Ev_ConnectRecordServer(strIp, nPort);
		if (!bSucc)
		{
			char szLog[50];
			sprintf_s(szLog, "connect %s:%d failed!", strIp, nPort);
			//				OutPutDebugLog(szLog) ;
			LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "Ev_ConnectRecordServer:" << szLog);
			return nResult;
		}

		memset(m_pPacket, 0, 2 * 1024 * 1024);
		//test:
		// 			char* szTest = new char[1024*1024] ;
		// 			memset(szTest,64,1024*1024) ;
		// 			szTest[1024*1024-2] = 'Z' ;
		// 			szTest[1024*1024-1] = 'Z' ;
		char* szType = "POST";

		sprintf(m_pPacket, "%s %s HTTP/1.1\r\nAccept: application/json, text/javascript, */*; q=0.01\r\nHOST: %s:%d\r\nContent-Length: %d \r\nContent-Type:application/x-www-form-urlencoded; charset=UTF-8\r\n\r\ncrypto=%s",
			szType, strAddr.c_str(), strIp.c_str(), nPort,/*1024*1024,szTest*/nContent+7, szContent);
		string strPacket = m_pPacket;
		//		LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "Send begin!");
		bSucc = SendData(strlen(m_pPacket), m_pPacket, strResult);
		if (!bSucc)
		{
			// 				OutPutDebugLog("Post Failed:\n") ;
			// 				OutPutDebugLog(m_pPacket) ;
			LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "Post Failed:" << m_pPacket);
		}
		else
		{
			//			LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "Post succ:" << (char*)strResult.c_str());
			int nPos = strResult.find("{gameover}");
			if (nPos>0)
			{
				nResult = 0;
			}
			else
			{
				nResult = 1;
			}
		}
		Ev_Close();
		clock_t t2 = clock();
		//		LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "Recv End! used time:" << t2 - t1 << "ms");
	}

	return nResult;
}

//int CHttpUtils::VerificationLicense(string strUrl, char* szContent, int nContentLen, string&strResult)
//{
//	int nResult = -1;
//	string strIp = "";
//	int nPort = 0;
//	string strAddr = "";
//	if (!strUrl.empty())
//	{
//		string str = strUrl;
//		int nLen = str.length();
//		int nPos = str.find("//");
//		string str1 = str.substr(0, nPos);
//		string str2 = str.substr(nPos + 2, nLen);
//
//		nPos = str2.find("/");
//		str1 = str2.substr(0, nPos);
//		strAddr = str2.substr(nPos, str2.length());
//		nPos = str1.find(":");
//
//		strIp = str1.substr(0, nPos);
//		nPort = atoi(str1.substr(nPos + 1, nLen).c_str());
//
//		bool bSucc = Ev_ConnectRecordServer(strIp, nPort);
//		if (!bSucc)
//		{
//			char szLog[50];
//			sprintf_s(szLog, "connect %s:%d failed!", strIp, nPort);
//			//				OutPutDebugLog(szLog) ;
//			LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "Ev_ConnectRecordServer:" << szLog);
//			return nResult;
//		}
//
//		memset(m_pPacket, 0, 2 * 1024 * 1024);
//
//		char* szType = "POST";
//
//		string strHead = "------WebKitFormBoundaryjCXfzP6ofWfVkUVE";
//		string strHead2 = "Content-Disposition: form-data; name=\"license\"; filename=\"lic.dat\"";
//		string strHead3 = "Content-Type: application/octet-stream";
//		string strTail = "------WebKitFormBoundaryjCXfzP6ofWfVkUVE--";
//
//		int nBodyLen = strHead.length() + strHead2.length() + strHead3.length()+ nContentLen + strTail.length();
//
//		sprintf(m_pPacket, "%s %s HTTP/1.1\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\nHOST: %s:%d\r\nContent-Length: %d \r\nContent-Type:multipart/form-data; boundary=----WebKitFormBoundaryjCXfzP6ofWfVkUVE\r\n\r\n%s\r\n%s\r\n%s\r\n\r\n%s\r\n%s",
//			szType, strAddr.c_str(), strIp.c_str(), nPort,/*1024*1024,szTest*/nBodyLen, strHead.c_str(), strHead2.c_str(), strHead3.c_str(), szContent, strTail.c_str());
////		string strPacket = m_pPacket;
//		//		LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "Send begin!");
//		clock_t t1 = clock();
//
//		bSucc = SendData(strlen(m_pPacket), m_pPacket, strResult);
//		if (!bSucc)
//		{
//			// 				OutPutDebugLog("Post Failed:\n") ;
//			// 				OutPutDebugLog(m_pPacket) ;
//			LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "Post Failed:" << m_pPacket);
//		}
//		else
//		{
//			//			LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "Post succ:" << (char*)strResult.c_str());
//			if (strResult.find("200")>0)
//			{
//				nResult = 0;
//			}
//		}
//		Ev_Close();
//		clock_t t2 = clock();
//		//		LOG4CPLUS_INFO(Logger::getInstance(ALARM_SERVER_LOG), "Recv End! used time:" << t2 - t1 << "ms");
//	}
//	return nResult;
//}