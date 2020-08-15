#ifndef _EV_SOCKET1_H
#define _EV_SOCKET1_H

#define SEND_BUFFER 8*1024	//接收大小
#define RECV_BUFFER 8*1024	//发送大小

#include <string>
using std::string;

enum EventType 
{
	ReadableEvent = 1,    //!< data available to read
	WritableEvent = 2,    //!< connected/data can be written without blocking
	Exception     = 4     //!< uh oh
};

enum NetWorkStatus 
{
	SENDORRECVSUCESS = 0,
	NOKEEPLIVE       = 1,
	SENDERROR        = 2, 
	RECVERROR        = 3,
	WAITTIMEOUT      = 4
};

bool EV_NetInit();

bool EV_SetNonBlocking( int fd );

void EV_Close_Socket( int n_socket );


bool EV_Connect(int sockClient,std::string strServerIP,int port);

int EV_Send(int sock,char *pSendBuf,int nSendSize);
int EV_Recv(int sock,char *pRecvBuf,int &nRecvSize);

int EV_RecvData(int sock,char *pRecvBuf,int nRecvSize);
int EV_SendData(int sock,char *pSendBuf,int nSendSize);

int UserAuthentication( int sockClient, string strUsername, string strPassword, int nUserType, int nContentType, int nCacheAlarmDataDay );

int EV_GetError();
#endif