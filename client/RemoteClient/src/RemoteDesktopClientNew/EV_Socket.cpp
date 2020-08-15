#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include <list>
#include <windows.h>
#include <direct.h>
#include <winuser.h>
#include <Tlhelp32.h>
#include <process.h>


# define EINPROGRESS	WSAEINPROGRESS
# define EWOULDBLOCK	WSAEWOULDBLOCK
# define ETIMEDOUT	    WSAETIMEDOUT
#include <string>
#include "EV_Socket.h"

#include <Winsock2.h>
#include <WS2tcpip.h>
#define _WINDOWS

#if defined(_MSC_VER)
# define snprintf	    _snprintf
# define vsnprintf    _vsnprintf
# define strcasecmp	  _stricmp
# define strncasecmp	_strnicmp
#elif defined(__BORLANDC__)
# define strcasecmp stricmp
# define strncasecmp strnicmp
#endif


bool EV_NetInit()
{
#ifdef _WINDOWS

	WORD wVersionRequested;
	WSADATA wsaData;
	int err;	
	wVersionRequested = MAKEWORD( 2, 2 );

	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) {
		return false;
	}
#endif
	return true;
}

bool EV_SetNonBlocking( int fd )
{	
#if 0
#if defined(_WINDOWS)
	unsigned long flag = 1;
	return (ioctlsocket((SOCKET)fd, FIONBIO, &flag) == 0);
#else
	return (fcntl(fd, F_SETFL, O_NONBLOCK) == 0);
#endif // _WINDOWS
#endif
	return true;
}

int EV_GetError()
{
#if defined(_WINDOWS)
	return WSAGetLastError();
#else
	return errno;
#endif
}

static inline bool nonFatalError()
{
	int err = EV_GetError();

	return (err == EINPROGRESS /*|| err == EAGAIN*/ || err == EWOULDBLOCK /*|| err == EINTR*/);
}

/*
	正常关闭socket
	2011-12-02
*/
void EV_Close_Socket( int n_socket )
{
#ifdef _WINDOWS
	closesocket(n_socket);
#else
	close(n_socket);
#endif
}


bool EV_Connect(int sockClient,std::string strServerIP,int port)
{
	struct sockaddr_in serverSocket;
	memset(&serverSocket, 0, sizeof(serverSocket));
	//serverSocket.sin_addr.S_un.S_addr=inet_addr(strServerIP.c_str());
	//serverSocket.sin_addr.s_addr = inet_addr(strServerIP.c_str());
	serverSocket.sin_family=AF_INET;
	inet_pton(AF_INET, strServerIP.c_str(), (void*)&serverSocket.sin_addr);

	serverSocket.sin_port=htons(port);
	int result = connect(sockClient,(struct sockaddr*)&serverSocket,sizeof(struct sockaddr));
	return result == 0 || nonFatalError();
}

//数据发送
int EV_Send( int sock,char *pSendBuf,int nSendSize )
{
	struct timeval timeout;
	timeout.tv_sec = 20;
	timeout.tv_usec = 0;

	int nRet = 0;
	int nError = 0;
	int nCurrendSendNum = 0;
	int nSendNum = 0;
	int nRemaind = 0;
	int i = 0;
	if( sock < 0 )
	{
		return NOKEEPLIVE;
	}
	fd_set outFd,inFd,excFd;
	FD_ZERO(&inFd);
	FD_ZERO(&outFd);
	FD_ZERO(&excFd);

	FD_SET(sock, &outFd);
	int nEvents = select(sock+1, &inFd, &outFd, &excFd, &timeout);
	if (nEvents<0)
	{
		
		return NOKEEPLIVE;
	}
	if (nEvents == 0)
	{
		return WAITTIMEOUT;
	}
	//
	int nToWrite = nSendSize;
	char *sp = const_cast<char*>( pSendBuf );

	bool bWouldBlock = false;
	while ( nToWrite > 0 && !bWouldBlock ) 
	{
#if defined(_WINDOWS)
		int n = send( sock, sp, nToWrite, 0);
#else
		int n = write(sock, sp, nToWrite);
#endif
		if ( n > 0 ) 
		{
			sp += n;
			nToWrite -= n;
		} 
		/*else if (nonFatalError()) 
		{
			bWouldBlock = true;
		} */
		else 
		{
			int n=WSAGetLastError();
			return n;//SENDERROR;   // Error
		}
	}
	return SENDORRECVSUCESS;
}

//接收数据
int EV_Recv( int sock,char *pRecvBuf,int &nRecvSize )
{
	bool bWouldBlock = false;
	bool bEof = false;		

	struct timeval timeout;
	timeout.tv_sec = 20;
	timeout.tv_usec = 0;

	fd_set outFd,inFd,excFd;
	FD_ZERO(&inFd);
	FD_ZERO(&outFd);
	FD_ZERO(&excFd);

	nRecvSize = 0;

	
	FD_SET(sock, &inFd);

#if defined(_WINDOWS)
		int nRet = recv( sock,  pRecvBuf + nRecvSize, RECV_BUFFER - 1 , 0 );	
#else
		int nRet = read( sock,  pRecvBuf + nRecvSize, RECV_BUFFER - 1 );
#endif
		if ( nRet > 0 )
		{
			nRecvSize = nRet;
			return SENDORRECVSUCESS;
		}
		else
		{
			return RECVERROR;
		}

//	while( !bWouldBlock && !bEof )
//	{
//#if defined(_WINDOWS)
//		int nRet = recv( sock,  pRecvBuf + nRecvSize, RECV_BUFFER , 0 );	
//#else
//		int nRet = read( sock,  pRecvBuf + nRecvSize, RECV_BUFFER );
//#endif
//		if ( nRet > 0 )
//		{
//			nRecvSize += nRet;
//		}
//		else if ( nRet == 0 )
//		{
//			bEof = true;
//		}
//		else if ( nonFatalError() )
//		{
//			bWouldBlock = true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//	if ( bEof && nRecvSize == 0 )
//	{//链路断开
//		return false;
//	}
//	return true;
}

//数据发送
int EV_SendData(int sock,char *pSendBuf,int nSendSize)
{
	int nRet = 0;
	int nError = 0;
	int nCurrendSendNum = 0;
	int nSendNum = 0;

	int nRemaind = 0;
	int i = 0;
	if( sock < 0 )
	{
		return 0;
	}
	if(nSendSize <= SEND_BUFFER)
	{
		nRet = send(sock, pSendBuf, nSendSize, 0);
		if(nRet <= 0)
		{
			//nError = GetLastError();
		}		
		return nRet;
	}
	else
	{
		nSendNum = nSendSize/SEND_BUFFER;
		nRemaind = nSendSize - nSendNum*SEND_BUFFER;
		for(i = 0;i< nSendNum;i++)
		{
			nRet = send(sock, pSendBuf + i*SEND_BUFFER, SEND_BUFFER, 0);
			if(nRet <= 0)
			{
				//nError = GetLastError();
				return nCurrendSendNum;
			}
			nCurrendSendNum += nRet;
		}
		nRet = send(sock, pSendBuf + nSendNum*SEND_BUFFER, nRemaind, 0);
		if(nRet <= 0)
		{
			//nError = GetLastError();
			return nCurrendSendNum;
		}
		nCurrendSendNum += nRet;
	}	
	return nCurrendSendNum;
}

//接收数据
int EV_RecvData(int sock,char *pRecvBuf,int nRecvSize)
{
	int nRecvTotalSize = 0;
	int nRet = 0;
	int nCurrentRecvSize = 0;
	int nOneTimeRecvSize = 0;
	int nRemainSize = nRecvSize;
	int nErr = 0;
	if( sock < 0 )
	{
		return 0;
	}
	do
	{
		if( nRemainSize <= RECV_BUFFER )
		{
			nOneTimeRecvSize = nRemainSize;
		}	
		else
		{
			nOneTimeRecvSize = RECV_BUFFER;
		}
		nRet = recv(sock,  pRecvBuf + nCurrentRecvSize, nOneTimeRecvSize , 0 );	
		if( nRet <=0 )
		{//链路错误
			//nErr = GetLastError();
			return nRet;
		}
		nCurrentRecvSize += nRet;
		nRemainSize = nRecvSize - nCurrentRecvSize;
		if(nCurrentRecvSize == nRecvSize)
		{
			return nCurrentRecvSize;
		}	

	}while(1);

}

/*	
返回值:
0:  成功
>0: 错误码
2013-02-28
*/
int UserAuthentication( int sockClient, string strUsername, string strPassword, int nUserType, int nContentType, int nCacheAlarmDataDay )
{
	int nRet = -1;


	return nRet;
}